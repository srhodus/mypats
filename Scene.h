// vim: tabstop=4 shiftwidth=4 noexpandtab
#pragma once
#include <QtGlobal>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <QList>
#include <QHash>
#include <QQueue>
#include <QSharedPointer>
#include <QPropertyAnimation>
#include "Globals.h"
#include "PixmapItem.h"

struct MouseEventInfo {
	int region;
	int idx;
	int sidx;
	QPointF pos;
};

class CProps final {
public:
	CProps() : pmi(nullptr), anim(false) {}
	CProps(PixmapItem *pm) : pmi(pm), anim(false) {}
	PixmapItem *pmi;
	bool anim;
};

class AnimationItem final {
public:
	AnimationItem(const QString& str, QChar adest)
		: cstr(str)
		, dest(adest) {}
	QString cstr;
	QChar dest;
};

class Scene : public QGraphicsScene {
	Q_OBJECT
public:
	Scene(QObject *parent, int width, int height);
	virtual ~Scene() {}
	void draw();
	void animateMove(const QString&, QChar dest);
	void processWinAnimation();
	void initPixmaps();
	void addLabels();
	void mouseLeft();
signals:
	void showStatusMessage(const QString& str);
	void gameWon();
	void move(const QString& str);
protected:
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
private:
	void showSelected();
	void highlightItems();
	bool processAnimation();
private:
	QList<MouseEventInfo> getMouseEventInfo(QGraphicsSceneMouseEvent *event);
private:
	int width;
	int height;
	int cardImageWidth;
	QPointF mouseCurPos;
	QHash<QString, CProps> cprops;
	QStringList itemsUnderCursor;
	QQueue<AnimationItem> animationQueue;
};
