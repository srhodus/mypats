// vim: tabstop=4 shiftwidth=4 noexpandtab
#include <QtWidgets>
#include "Scene.h"
#include "Globals.h"
#include "MainWindow.h"
#include "Deal.h"
#include "State.h"
#include "Rules.h"

extern State st;
extern History hs;

constexpr int DEFAULT_WIDTH = 800;
constexpr int DEFAULT_HEIGHT = 600;
constexpr int DEFAULT_CASCADES = 8;
constexpr int FPS = 60;

MainWindow::MainWindow() {
	width = DEFAULT_WIDTH;
	height = DEFAULT_HEIGHT;
	setWindowTitle("MyPats");
	createActions();
	createMenus();
	scene = new Scene(this, width, height);
	view = new QGraphicsView(scene);
	view->setBackgroundBrush(Qt::darkGreen);
	view->setMinimumSize(QSize(width/2, height/2));
	view->setCacheMode(QGraphicsView::CacheBackground);
	view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
	view->setRenderHint(QPainter::Antialiasing);
	setCentralWidget(view);
	newRandomDeal();
	statusBar()->showMessage("Ready");
	timerId = startTimer(1000/FPS);
	connect(scene, &Scene::showStatusMessage, this, &MainWindow::showStatusMessage);
	connect(scene, &Scene::gameWon, this, &MainWindow::gameWon);
	connect(scene, &Scene::move, this, &MainWindow::move);
}

MainWindow::~MainWindow() {
	killTimer(timerId);
}

void MainWindow::createActions() {
	newRandomDealAction = new QAction("New &Random Deal", this);
	connect(newRandomDealAction, &QAction::triggered, this, &MainWindow::newRandomDeal);
	newNumberedDealAction = new QAction("New &Numbered Deal", this);
	connect(newNumberedDealAction, &QAction::triggered, this, &MainWindow::newNumberedDeal);
	exportAction = new QAction("&Export", this);
	connect(exportAction, &QAction::triggered, this, &MainWindow::exportState);
	importAction = new QAction("&Import", this);
	connect(importAction, &QAction::triggered, this, &MainWindow::importState);
	undoAction = new QAction("&Undo", this);
	connect(undoAction, &QAction::triggered, this, &MainWindow::undo);
#ifdef QT_DEBUG
	debugAction = new QAction("&Debug", this);
	connect(debugAction, &QAction::triggered, this, &MainWindow::debug);
#endif
}

void MainWindow::createMenus() {
	fileMenu = menuBar()->addMenu("&File");
	fileMenu->addAction(newRandomDealAction);
	fileMenu->addAction(newNumberedDealAction);
	fileMenu->addAction(exportAction);
	// TODO: Reenable this when it's fixed...
	// fileMenu->addAction(importAction);
	editMenu = menuBar()->addMenu("&Edit");
	editMenu->addAction(undoAction);
#ifdef QT_DEBUG
	editMenu->addAction(debugAction);
#endif
}

void MainWindow::newRandomDeal() {
	initDeal(QRandomGenerator::global()->bounded(0, INT32_MAX));
}

void MainWindow::newNumberedDeal() {
	bool ok;
	QString text = QInputDialog::getText(this, "Input Deal No.", "Deal No.:",
										 QLineEdit::Normal, "", &ok);
	if (ok && !text.isEmpty()) {
		int dealNo = text.toInt(&ok);
		if (ok) {
			initDeal(dealNo);
		}
	}
}

void MainWindow::undo() {
	if (hs.stack.size() < 2) {
		return;
	}
	hs.stack.pop();
	st.fromJson(hs.stack.pop());
	hs.stack.push(st.toJson());
	// Show the no. of available moves
	auto m = getAvailMoves(st.reserves, st.foundations, st.cascades, true);
	statusBar()->showMessage(QStringLiteral("%1 avail. move(s)").arg(m.size()));
	st.lastWasUndo = true;
}

#ifdef QT_DEBUG
void MainWindow::debug() {
	killTimer(timerId);
	scene->clear();
	scene->addLabels();
	scene->initPixmaps();
	hs.stack.clear();
	st = State();
	st.reserves = {
		"", "KH", "", ""
	};
	st.foundations = {
		"7C", "8D", "8H", "9S"
	};
	st.cascades = {
		{"QD"},
		{"QC", "JD", "JC", "9D"},
		{"KC", "JS", "8C", "KS"},
		{"TD"},
		{"QH"},
		{"TC"},
		{"KD", "QS", "JH", "TS", "9H"},
		{"TH", "9C"}
	};
	hs.stack.push(st.toJson());
	timerId = startTimer(1000/FPS);
}
#endif

void MainWindow::exportState() {
	bool ok;
	QString json(st.toJson().data());
	QInputDialog::getMultiLineText(this, "Export", "JSON:", json, &ok);
}

void MainWindow::importState() {
	bool ok;
	QString text = QInputDialog::getMultiLineText(this, "Import", "JSON:", "",
												  &ok);
	if (ok && !text.isEmpty()) {
		st.fromJson(QByteArray(text.trimmed().toLatin1()));
	}
	// TODO: Still shows cards that have been placed in foundations. Need to
	// remove or hide these cards
	statusBar()->showMessage("State imported");
}

void MainWindow::initDeal(int dealNo) {
	auto sl = getDeal(dealNo, MAX_CASCADES);
	const auto temp = QString::asprintf("Deal no. %d", dealNo);
	statusBar()->showMessage(temp);
	hs.stack.clear();
	st = State(sl);
	hs.stack.push(st.toJson());
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
	switch (event->key()) {
		case Qt::Key_Z:
			if (event->modifiers() == Qt::ControlModifier) {
				undo();
			}
			break;
		case Qt::Key_Backspace:
			if (keyMove.size() > 0) {
				keyMove.chop(1);
			}
			break;
		case Qt::Key_0:
		case Qt::Key_1:
		case Qt::Key_2:
		case Qt::Key_3:
		case Qt::Key_4:
		case Qt::Key_5:
		case Qt::Key_6:
		case Qt::Key_7:
		case Qt::Key_8:
		case Qt::Key_9:
		case Qt::Key_A:
		case Qt::Key_B:
		case Qt::Key_C:
		case Qt::Key_D:
		case Qt::Key_H: {
			keyMove.append(event->text().toUpper());
			QString str;
			if (keyMove.size() == 2) {
				for (auto i : keyMove) {
					if (i.isDigit()) {
						if (i.digitValue() == 0) {
							str.append(findEmptyReserve());
						} else {
							str.append(QString::number(
										qMax(0, i.digitValue()-1)));
						}
					} else {
						str.append(i);
					}
				}
				Q_ASSERT(str.size() == 2);
				statusBar()->showMessage(keyMove);
				move(str);
				keyMove.clear();
			}
		}
			break;
		case Qt::Key_W:
			if (event->modifiers() == Qt::ControlModifier) {
				gameWon();
			}
			break;
		default:
			event->ignore();
			break;
	}
}

void MainWindow::leaveEvent(QEvent *event) {
	Q_UNUSED(event);
	scene->mouseLeft();
}

void MainWindow::timerEvent(QTimerEvent *event) {
	Q_UNUSED(event);
	scene->draw();
}

void MainWindow::showStatusMessage(const QString& str) {
	statusBar()->showMessage(str);
}

void MainWindow::gameWon() {
	scene->processWinAnimation();
	killTimer(timerId);
	QMessageBox mb;
	mb.setText("Congratulations! You won!");
	mb.exec();
	newRandomDeal();
	timerId = startTimer(1000/FPS);
}

QChar MainWindow::findEmptyReserve() const {
	int idx = -1;
	for (int i = 0; i < st.reserves.size(); i++) {
		if (st.reserves[i].isEmpty()) {
			idx = i;
			break;
		}
	}
	if (idx != -1) {
		return Reserves[idx];
	}
	// If we can't find an empty reserve, just return the first one. We won't
	// be permitted to move to it later.
	return Reserves[0];
}

void MainWindow::move(const QString& str) {
	Q_ASSERT(str.size() == 2);
	QChar first, second;
	first = str[0];
	second = str[1];
	bool ok = false;
	if (second.isDigit()) {
		// Translate '8' to 'H'
		if (second == '8') {
			second = 'H';
		}
	}
	if (first.isDigit() && second.isDigit()) {
		// Move from cascade to cascade (e.g. "12")
		ok = moveCascadeToCascade(first.digitValue(), second.digitValue());
	} else if (first.isDigit() && !second.isDigit()) {
		if (second.toUpper() == 'H') {
			// Move from cascade to foundations (e.g., "3H")
			ok = moveCascadeToFoundations(first.digitValue());
		} else {
			// Move from cascade to reserves (e.g., "1A")
			ok = moveCascadeToReserves(first.digitValue(), second);
		}
	} else if (!first.isDigit() && second.isDigit()) {
		// Move from reserves to cascade (e.g., "A6")
		ok = moveReservesToCascade(first, second.digitValue());
	} else if (!first.isDigit() && !second.isDigit()) {
		// Move from reserves to foundations (e.g., "BH")
		ok = moveReservesToFoundations(first);
	}
	if (!ok) {
		statusBar()->showMessage("Invalid move!");
	} else {
		QString error;
		Q_ASSERT(validate(st.reserves, st.foundations, st.cascades, error));
		hs.stack.push(st.toJson());
		st.lastWasUndo = false;
	}
}

bool MainWindow::moveCascadeToCascade(int from, int to) {
	if (from < 0 || from >= st.cascades.size()) {
		return false;
	}
	if (to < 0 || to >= st.cascades.size()) {
		return false;
	}
	if (from == to) {
		return false;
	}
	if (st.cascades[from].size() == 0) {
		return false;
	}
	int n = getMovableStackSize(from, to, st.reserves, st.cascades);
	if (n == 0) {
		return false;
	}
	QStack<QString> temp;
	for (int i = 0; i < n; i++) {
		temp.push(st.cascades[from].takeLast());
	}
	while (!temp.isEmpty()) {
		st.cascades[to].append(temp.pop());
	}
	return true;
}

bool MainWindow::moveCascadeToFoundations(int from) {
	if (from < 0 || from >= st.cascades.size()) {
		return false;
	}
	if (st.cascades[from].size() == 0) {
		return false;
	}
	const auto last = st.cascades[from][st.cascades[from].size()-1];
	const auto idx = suit(last);
	if (!canMoveToFoundation(last, st.foundations[idx])) {
		return false;
	}
	st.foundations[idx] = st.cascades[from].takeLast();
	scene->animateMove(last, Foundations[idx]);
	return true;
}

bool MainWindow::moveCascadeToReserves(int from, QChar to) {
	if (from < 0 || from >= st.cascades.size()) {
		return false;
	}
	if (st.cascades[from].size() == 0) {
		return false;
	}
	const auto last = st.cascades[from][st.cascades[from].size()-1];
	const auto idx = Reserves.indexOf(to);
	if (idx == -1) {
		return false;
	}
	if (!canMoveToReserve(last, st.reserves[idx])) {
		return false;
	}
	st.reserves[idx] = st.cascades[from].takeLast();
	return true;
}

bool MainWindow::moveReservesToCascade(QChar from, int to) {
	if (to < 0 || to >= st.cascades.size()) {
		return false;
	}
	const auto idx = Reserves.indexOf(from);
	if (idx == -1) {
		return false;
	}
	QStringList sl;
	sl.append(st.reserves[idx]);
	if (!canMoveToCascade(st.cascades[to], sl)) {
		return false;
	}
	st.reserves[idx] = "";
	st.cascades[to].append(sl[0]);
	return true;
}

bool MainWindow::moveReservesToFoundations(QChar from) {
	const auto idx = Reserves.indexOf(from);
	if (idx == -1) {
		return false;
	}
	const auto cstr = st.reserves[idx];
	const auto idx2 = suit(cstr);
	if (!canMoveToFoundation(cstr, st.foundations[idx2])) {
		return false;
	}
	st.reserves[idx] = "";
	st.foundations[idx2] = cstr;
	scene->animateMove(cstr, Foundations[idx2]);
	return true;
}
