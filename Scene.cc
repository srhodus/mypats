// vim: tabstop=4 shiftwidth=4 noexpandtab
#include <QtWidgets>
#include <algorithm>
#include <limits>
#include "State.h"
#include "Scene.h"
#include "Globals.h"
#include "Rules.h"

extern State st;
extern History hs;

constexpr int CASC_Y_START = 148;
constexpr int CASC_X_SPACING = 92;
constexpr int CASC_Y_SPACING = 36;

enum {
	BackgroundZValue = 0,
	ForegroundZValue,
	MovingZValue = 128
};

enum {
	RegionInvalid,
	RegionFreeCell,
	RegionHomeCell,
	RegionCascade,
	RegionEmptyCascade
};

qreal cxpos[MAX_CASCADES] = {0};
qreal cypos[MAX_CASCADES][MAX_STACK_LEN] = {0};

Scene::Scene(QObject *parent, int width, int height)
	: QGraphicsScene(parent)
	, width(width)
	, height(height)
	, cardImageWidth(0)
	, mouseCurPos()
	, cprops()
	, itemsUnderCursor()
	, animationQueue() {
	setSceneRect(-width/2, -height/2, width, height);
	setItemIndexMethod(QGraphicsScene::NoIndex);
	// Calculate x,y positions for cascades
	for (int i = 0; i < MAX_CASCADES; i++) {
		int xpos = i*CASC_X_SPACING;
		qreal xx = -(width/2)+xpos;
		cxpos[i] = xx;
		int ypos = CASC_Y_START;
		qreal yy;
		for (int j = 0; j < MAX_STACK_LEN; j++) {
			yy = -(height/2)+ypos;
			cypos[i][j] = yy;
			ypos += CASC_Y_SPACING;
		}
	}
	addLabels();
	initPixmaps();
}

void Scene::addLabels() {
	// Add labels for the reserves
	for (int i = 0; i < Reserves.size(); i++) {
		auto item = new QGraphicsSimpleTextItem(Reserves[i]);
		const qreal xx = -(width/2)+(i*CASC_X_SPACING)+32;
		const qreal yy = -height/2;
		item->setPos(xx, yy);
		item->setEnabled(false);
		item->show();
		addItem(item);
	}
	// Add labels for the cascades
	for (int i = 0; i < MAX_CASCADES; i++) {
		QString k(QString::number(i+1));
		auto item = new QGraphicsSimpleTextItem(k);
		item->setPos(cxpos[i]+32, cypos[i][0]-16);
		item->setEnabled(false);
		item->show();
		addItem(item);
	}
}

void Scene::mouseLeft() {
	itemsUnderCursor.clear();
}

void Scene::initPixmaps() {
	cprops.clear();
    const QPixmap sheet(":/pixmaps/kde-standard-cards-GPL.xpm");
	constexpr int ImagesPerRow = 13;
	constexpr int ImagesNoColumns = 5;
	const int w = sheet.width()/ImagesPerRow;
	const int h = sheet.height()/ImagesNoColumns;
	cardImageWidth = w;
	// Add a pixmap for each card's string representation
	for (int i = 0; i < Suit.length(); i++) {
		for (int j = 0; j < Rank.length(); j++) {
			QString k;
			k.append(Rank[j]);
			k.append(Suit[i]);
			Q_ASSERT(k.size() == 2);
			if (!cprops.contains(k)) {
				cprops.insert(k, {new PixmapItem(sheet.copy(j*w, h*i, w, h))});
				cprops[k].pmi->setZValue(ForegroundZValue);
				cprops[k].pmi->hide();
				addItem(cprops[k].pmi);
			}
		}
	}
	constexpr int Row = 4;
	constexpr int RsCol = 4;
	// Add a pixmap for the reserve placeholder
	for (int i = 0; i < ReservePlaceholder.size(); i++) {
		cprops.insert(ReservePlaceholder[i],
				{new PixmapItem(sheet.copy(RsCol*w, h*Row, w, h))});
		addItem(cprops[ReservePlaceholder[i]].pmi);
		cprops[ReservePlaceholder[i]].pmi->setZValue(BackgroundZValue);
		cprops[ReservePlaceholder[i]].pmi->hide();
		cprops[ReservePlaceholder[i]].pmi->setAcceptHoverEvents(true);
	}
	// Add a pixmap for the foundations placeholders
	for (int i = 0; i < FoundationPlaceholders.size(); i++) {
		cprops.insert(FoundationPlaceholders[i],
				{new PixmapItem(sheet.copy(i*w, h*Row, w, h))});
		addItem(cprops[FoundationPlaceholders[i]].pmi);
		cprops[ReservePlaceholder[i]].pmi->setZValue(BackgroundZValue);
		cprops[FoundationPlaceholders[i]].pmi->hide();
	}
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
	itemsUnderCursor.clear();
	mouseCurPos = event->scenePos();
	for (const auto& i : items(mouseCurPos, Qt::IntersectsItemShape,
				Qt::DescendingOrder)) {
		for (auto j = cprops.begin(); j != cprops.end(); j++) {
			Q_CHECK_PTR(j.value().pmi);
			if (j.value().pmi == i) {
				itemsUnderCursor.append(j.key());
				// TODO: For now, only allow one card under the cursor. This
				// may need to change when selecting a valid stack of cards.
				return;
			}
		}
	}
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
	const auto li = getMouseEventInfo(event);
	if (li.size() == 1) {
		const auto info = li.first();
		if (info.region == RegionFreeCell) {
			// Pick up a card from the reserves
			if (!st.reserves[info.idx].isEmpty()) {
				auto pmi = cprops[st.reserves[info.idx]].pmi;
				Q_CHECK_PTR(pmi);
				const qreal xdiff = event->scenePos().x() - pmi->pos().x();
				const qreal ydiff = event->scenePos().y() - pmi->pos().y();
				st.selected.offset = QPointF(xdiff, ydiff);
				st.selected.stack.append(st.reserves[info.idx]);
				st.reserves[info.idx] = "";
				st.selected.origin = {OriginFreeCell, info.idx};
				mouseCurPos = event->scenePos();
				showSelected();
			}
		} else if (info.region == RegionCascade) {
			Q_ASSERT(st.cascades.size() > info.idx);
			Q_ASSERT(st.cascades[info.idx].size() > info.sidx);
			if (info.sidx == st.cascades[info.idx].size() - 1) {
				// Select the last card of the cascade
				auto pmi = cprops[st.cascades[info.idx][info.sidx]].pmi;
				Q_CHECK_PTR(pmi);
				const qreal xdiff = event->scenePos().x() - pmi->pos().x();
				const qreal ydiff = event->scenePos().y() - pmi->pos().y();
				st.selected.offset = QPointF(xdiff, ydiff);
				auto last = st.cascades[info.idx].takeLast();
				st.selected.stack.append(last);
				st.selected.origin = {OriginCascade, info.idx};
				mouseCurPos = event->scenePos();
				showSelected();
			} else {
				// Select a stack of cards from the cascade
				Q_ASSERT(st.selected.stack.size() == 0);
				if (!isValidSingleStacking(st.cascades[info.idx], info.sidx)) {
					// Not a valid stack
					return;
				}
				auto pmi = cprops[st.cascades[info.idx][info.sidx]].pmi;
				Q_CHECK_PTR(pmi);
				const qreal xdiff = event->scenePos().x() - pmi->pos().x();
				const qreal ydiff = event->scenePos().y() - pmi->pos().y();
				st.selected.offset = QPointF(xdiff, ydiff);
				st.selected.stack = st.cascades[info.idx].sliced(info.sidx);
				st.cascades[info.idx].resize(
						st.cascades[info.idx].size()-st.selected.stack.size());
				st.selected.origin = {OriginCascade, info.idx};
				mouseCurPos = event->scenePos();
				showSelected();
			}
		}
	}
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
	bool reset = true;
	const auto li = getMouseEventInfo(event);
	if (li.size() == 1) {
		QString last;
		if (st.selected.stack.size() > 0) {
			last = st.selected.stack[st.selected.stack.size()-1];
		}
		const auto info = li.first();
		if (info.region == RegionFreeCell) {
			if (st.selected.stack.size() == 1) {
				if (canMoveToReserve(last, st.reserves[info.idx])) {
					st.reserves[info.idx] = st.selected.stack.takeLast();
					if (!st.foundations[info.idx].isEmpty()) {
						auto pmi = cprops[st.foundations[info.idx]].pmi;
						Q_CHECK_PTR(pmi);
						pmi->setZValue(ForegroundZValue);
					}
					st.selected.origin = {OriginNull, -1};
					hs.stack.push(st.toJson());
					reset = false;
				}
			}
		} else if (info.region == RegionHomeCell) {
			if (st.selected.stack.size() == 1) {
				if (canMoveToFoundation(last, st.foundations[info.idx]) &&
						info.idx == suit(last)) {
					if (!st.foundations[info.idx].isEmpty()) {
						// Hide cards beneath the top card of the home cell
						auto pmi = cprops[st.foundations[info.idx]].pmi;
						Q_CHECK_PTR(pmi);
						pmi->setZValue(BackgroundZValue);
						pmi->hide();
					}
					st.foundations[info.idx] = st.selected.stack.takeLast();
					if (!st.foundations[info.idx].isEmpty()) {
						auto pmi = cprops[st.foundations[info.idx]].pmi;
						Q_CHECK_PTR(pmi);
						pmi->setZValue(ForegroundZValue);
					}
					st.selected.origin = {OriginNull, -1};
					hs.stack.push(st.toJson());
					reset = false;
				}
			}
		} else if (info.region == RegionCascade || info.region ==
				RegionEmptyCascade) {
			if (canMoveToCascade(st.cascades[info.idx], st.selected.stack)) {
				if (st.selected.stack.size() == 1) {
					auto last = st.selected.stack.takeLast();
					if (!last.isEmpty()) {
						auto pmi = cprops[last].pmi;
						Q_CHECK_PTR(pmi);
						pmi->setZValue(ForegroundZValue);
						st.cascades[info.idx].append(last);
						st.selected.origin = {OriginNull, -1};
						hs.stack.push(st.toJson());
						reset = false;
					}
				} else if (st.selected.stack.size() > 1) {
					int max = getMaxMovableSize(info.idx, st.reserves,
							st.cascades);
					if (max >= st.selected.stack.size()) {
						for (int i = 0; i < st.selected.stack.size(); i++) {
							auto pmi = cprops[st.selected.stack[i]].pmi;
							Q_CHECK_PTR(pmi);
							pmi->setZValue(ForegroundZValue);
						}
						st.cascades[info.idx].append(st.selected.stack);
						st.selected.origin = {OriginNull, -1};
						st.selected.stack.clear();
						hs.stack.push(st.toJson());
						reset = false;
					}
				}
			}
		}
	}
	if (reset) {
		if (st.selected.origin.type == OriginFreeCell) {
			const auto last = st.selected.stack.takeLast();
			st.reserves[st.selected.origin.idx] = last;
			auto pmi = cprops[last].pmi;
			Q_CHECK_PTR(pmi);
			itemsUnderCursor.clear();
			const qreal xx = -(width/2)+(st.selected.origin.idx*CASC_X_SPACING);
			const qreal yy = -height/2+16;
			st.selected.origin = {OriginNull, -1};
			// Animate the card moving back to its original position
			auto anim = new QPropertyAnimation(pmi, "pos", this);
			anim->setStartValue(QPointF(pmi->x(), pmi->y()));
			anim->setEndValue(QPointF(xx, yy));
			cprops[last].anim = true;
			anim->start(QAbstractAnimation::DeleteWhenStopped);
			connect(anim, &QAction::destroyed, this, [=]() {
				cprops[last].anim = false;
				cprops[last].pmi->setZValue(ForegroundZValue);
			});
		} else if (st.selected.origin.type == OriginCascade) {
			const int idx = st.selected.origin.idx;
			const int sz = st.cascades[idx].size();
			for (int i = 0; i < st.selected.stack.size(); i++) {
				const auto cstr = st.selected.stack[i];
				auto pmi = cprops[cstr].pmi;
				Q_CHECK_PTR(pmi);
				itemsUnderCursor.clear();
				const qreal xx = cxpos[idx];
				const qreal yy = cypos[idx][sz+i];
				// Animate the card(s) moving back to original position
				auto anim = new QPropertyAnimation(pmi, "pos", this);
				anim->setStartValue(QPointF(pmi->x(), pmi->y()));
				anim->setEndValue(QPointF(xx, yy));
				cprops[cstr].anim = true;
				anim->start(QAbstractAnimation::DeleteWhenStopped);
				connect(anim, &QAction::destroyed, this, [=]() {
					cprops[cstr].anim = false;
					cprops[cstr].pmi->setZValue(ForegroundZValue);
				});
			}
			st.cascades[idx].append(st.selected.stack);
			st.selected.stack.clear();
			st.selected.origin = {OriginNull, -1};
		}
	} else {
		QString error;
		Q_ASSERT(validate(st.reserves, st.foundations, st.cascades, error));
		st.lastWasUndo = false;
	}
	// Show the no. of available moves
	auto m = getAvailMoves(st.reserves, st.foundations, st.cascades, true);
	emit showStatusMessage(QStringLiteral("%1 avail. move(s)").arg(m.size()));
}

QList<MouseEventInfo> Scene::getMouseEventInfo(QGraphicsSceneMouseEvent *event) {
	QList<MouseEventInfo> rv;
	if (event->button() == Qt::LeftButton) {
		for (int i = 0; i < items(event->scenePos()).size(); i++) {
			const QGraphicsItem *j = items(event->scenePos())[i];
			if (!j->isEnabled()) {
				// Ignore disabled items
				continue;
			}
			const PixmapItem *item = dynamic_cast<const PixmapItem*>(j);
			for (int i = 0; i < st.reserves.size(); i++) {
				const PixmapItem *pmi[2];
				pmi[0] = cprops[ReservePlaceholder[i]].pmi;
				Q_CHECK_PTR(pmi[0]);
				if (st.reserves[i].isEmpty()) {
					pmi[1] = nullptr;
				} else {
					pmi[1] = cprops[st.reserves[i]].pmi;
					Q_CHECK_PTR(pmi[1]);
				}
				if ((st.reserves[i].isEmpty() && pmi[0] == item)
						|| pmi[1] == item) {
					MouseEventInfo info{};
					info.region = RegionFreeCell;
					info.idx = i;
					info.pos = event->scenePos();
					rv.append(info);
					break;
				}
			}
			for (int i = 0; i < st.foundations.size(); i++) {
				Q_ASSERT(FoundationPlaceholders.size() > i);
				const PixmapItem *pmi[2] = {nullptr};
				if (cprops.contains(FoundationPlaceholders[i])) {
					pmi[0] = cprops[FoundationPlaceholders[i]].pmi;
					Q_CHECK_PTR(pmi[0]);
				}
				if (!st.foundations[i].isEmpty()) {
					pmi[1] = cprops[st.foundations[i]].pmi;
					Q_CHECK_PTR(pmi[1]);
				}
				if (pmi[0] == item || pmi[1] == item) {
					MouseEventInfo info{};
					info.region = RegionHomeCell;
					info.idx = i;
					info.pos = event->scenePos();
					rv.append(info);
					break;
				}
			}
			for (int i = 0; i < st.cascades.size(); i++) {
				for (int j = 0; j < st.cascades[i].size(); j++) {
					if (st.cascades[i][j].isEmpty()) {
						continue;
					}
					auto pmi = cprops[st.cascades[i][j]].pmi;
					Q_CHECK_PTR(pmi);
					if (pmi == item) {
						MouseEventInfo info{};
						info.region = RegionCascade;
						info.idx = i;
						info.sidx = j;
						info.pos = event->scenePos();
						rv.append(info);
					}
				}
			}
		}
		if (rv.size() == 0) {
			int n = static_cast<int>(sizeof(cxpos)/sizeof(cxpos[0]));
			for (int i = 0; i < n; i++) {
				if (event->scenePos().x() >= cxpos[i] && event->scenePos().x()
					<= cxpos[i]+cardImageWidth) {
						MouseEventInfo info{};
						info.region = RegionEmptyCascade;
						info.idx = i;
						info.pos = event->scenePos();
						rv.append(info);
					break;
				}
			}
		}
	}
	if (rv.size() > 1) {
		std::sort(
			rv.begin(),
			rv.end(),
		    [](const MouseEventInfo& lhs, const MouseEventInfo& rhs) {
				return lhs.sidx > rhs.sidx;
			});
		QList<MouseEventInfo> rv2;
		rv2.append(rv.first());
		rv.clear();
		rv = rv2;
	}
	return rv;
}

void Scene::draw() {
	// FreeCells
	const qreal yy = -height/2+16;
	for (int i = 0; i < st.reserves.size(); i++) {
		const qreal xx = -(width/2)+(i*CASC_X_SPACING);
		if (st.reserves[i].isEmpty()) {
			auto pmi = cprops[ReservePlaceholder[i]].pmi;
			Q_CHECK_PTR(pmi);
			pmi->setPos(xx, yy);
			pmi->setZValue(BackgroundZValue);
			pmi->setGraphicsEffect(nullptr);
			pmi->show();
		} else {
			if (!cprops[st.reserves[i]].anim) {
				auto pmi = cprops[st.reserves[i]].pmi;
				Q_CHECK_PTR(pmi);
				pmi->setPos(xx, yy);
				pmi->setZValue(ForegroundZValue);
				pmi->setGraphicsEffect(nullptr);
				pmi->show();
			}
		}
	}
	// Foundations
	for (int i = 0; i < st.foundations.size(); i++) {
		const qreal xx = i*CASC_X_SPACING;
		if (st.foundations[i].isEmpty()) {
			auto pmi = cprops[FoundationPlaceholders[i]].pmi;
			Q_CHECK_PTR(pmi);
			pmi->setPos(xx, yy);
			pmi->setZValue(BackgroundZValue);
			pmi->setGraphicsEffect(nullptr);
			pmi->show();
		} else {
			if (!cprops[st.foundations[i]].anim) {
				auto pmi = cprops[st.foundations[i]].pmi;
				Q_CHECK_PTR(pmi);
				pmi->setPos(xx, yy);
				pmi->setZValue(ForegroundZValue+rank(st.foundations[i]));
				pmi->setGraphicsEffect(nullptr);
				pmi->show();
			}
		}
	}
	// Cascades
	for (int i = 0; i < st.cascades.size(); i++) {
		const int xpos = i*CASC_X_SPACING;
		const qreal xx = -(width/2)+xpos;
		cxpos[i] = xx;
		for (int j = 0; j < st.cascades[i].size(); j++) {
			if (cprops[st.cascades[i][j]].anim) {
				// Card being animated
				continue;
			}
			auto pmi = cprops[st.cascades[i][j]].pmi;
			Q_CHECK_PTR(pmi);
			pmi->setPos(xx, cypos[i][j]);
			pmi->setZValue(ForegroundZValue+j);
			pmi->setGraphicsEffect(nullptr);
			pmi->show();
		}
	}
	// Show the stack of selected card(s)
	showSelected();
	// Highlight item(s) under cursor
	highlightItems();
	if (!st.lastWasUndo && st.selected.stack.size() == 0) {
		// Process an automove if available
		auto am = getAutoMove(st.reserves, st.foundations, st.cascades);
		if (am.size() == 2) {
			emit move(am);
		}
	}
	if (!processAnimation()) {
		if (st.selected.stack.size() == 0 && isGameWon(st.foundations)) {
			emit gameWon();
		}
	}
}

void Scene::animateMove(const QString& cstr, QChar dest) {
	cprops[cstr].anim = true;
	animationQueue.enqueue({cstr, dest});
}

void Scene::processWinAnimation() {
	for (auto j = cprops.begin(); j != cprops.end(); j++) {
		Q_CHECK_PTR(j.value().pmi);
		if (j.key().startsWith("R") || j.key().startsWith("F")) {
			// Skip placeholder images
			continue;
		}
		// Animate the card moving to the bottom of the screen
		auto anim = new QPropertyAnimation(j.value().pmi, "pos");
		cprops[j.key()].anim = true;
		anim->setStartValue(QPointF(j.value().pmi->x(), j.value().pmi->y()));
		anim->setEndValue(QPointF(0, height));
		anim->setDuration(2500);
		anim->setEasingCurve(QEasingCurve::OutQuad);
		anim->start(QAbstractAnimation::DeleteWhenStopped);
		connect(anim, &QAction::destroyed, this, [=]() {
			cprops[j.key()].anim = false;
			j.value().pmi->hide();
		});
	}
}

bool Scene::processAnimation() {
	// Busy flag only allows one animation at a time
	static bool busy = false;
	if (busy) {
		return true;
	}
	if (animationQueue.isEmpty()) {
		return false;
	}
	busy = true;
	auto item = animationQueue.dequeue();
	cprops[item.cstr].anim = true;
	auto pmi = cprops[item.cstr].pmi;
	Q_CHECK_PTR(pmi);
	pmi->setZValue(MovingZValue+rank(item.cstr));
	pmi->setGraphicsEffect(nullptr);
	qreal xx = 0;
	qreal yy = -height/2+16;
	if (!item.dest.isDigit() && Foundations.indexOf(item.dest) != -1) {
		xx = Foundations.indexOf(item.dest)*CASC_X_SPACING;
	} else if (!item.dest.isDigit() && Reserves.indexOf(item.dest) != -1) {
		xx = -(width/2)+(Reserves.indexOf(item.dest)*CASC_X_SPACING);
	} else {
		int idx = item.dest.digitValue();
		xx = cxpos[idx];
		Q_ASSERT(st.cascades[idx].size() < MAX_STACK_LEN);
		yy = cypos[idx][st.cascades[idx].size()];
	}
	// Animate the card moving to its destination
	auto anim = new QPropertyAnimation(pmi, "pos");
	anim->setStartValue(QPointF(pmi->x(), pmi->y()));
	anim->setEndValue(QPointF(xx, yy));
	anim->start(QAbstractAnimation::DeleteWhenStopped);
	connect(anim, &QAction::destroyed, this, [=]() {
		cprops[item.cstr].anim = false;
		cprops[item.cstr].pmi->setZValue(ForegroundZValue+rank(item.cstr));
		busy = false;
	});
	return true;
}

void Scene::showSelected() {
	if (st.selected.stack.size() > 0) {
		for (int i = 0; i < st.selected.stack.size(); i++) {
			Q_ASSERT(st.selected.stack[i].size() == 2);
			auto pmi = cprops[st.selected.stack[i]].pmi;
			Q_CHECK_PTR(pmi);
			pmi->setPos(mouseCurPos.x() - st.selected.offset.x(),
					(mouseCurPos.y() - st.selected.offset.y()) + i*CASC_Y_SPACING);
			pmi->setZValue(MovingZValue+i);
			pmi->setGraphicsEffect(nullptr);
			pmi->show();
		}
	}
}

void Scene::highlightItems() {
	for (const auto& i : itemsUnderCursor) {
		auto pmi = cprops[i].pmi;
		Q_CHECK_PTR(pmi);
		auto effect = new QGraphicsColorizeEffect();
		if (i.startsWith("R") || i.startsWith("F")) {
			effect->setColor(Qt::magenta);
		} else {
			if (color(i) == Red) {
				effect->setColor(Qt::red);
			} else {
				effect->setColor(Qt::darkGray);
			}
		}
		pmi->setGraphicsEffect(effect);
	}
}
