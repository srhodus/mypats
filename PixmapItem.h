// vim: tabstop=4 shiftwidth=4 noexpandtab
#pragma once
#include <QObject>
#include <QPixmap>
#include <QGraphicsPixmapItem>

class PixmapItem : public QObject, public QGraphicsPixmapItem {
	Q_OBJECT
	Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
	PixmapItem(const QPixmap& pm)
		: QGraphicsPixmapItem(pm)
	{}
	virtual ~PixmapItem() {}
};
