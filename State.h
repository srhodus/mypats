// vim: tabstop=4 shiftwidth=4 noexpandtab
#pragma once
#include <QString>
#include <QList>
#include <QPointF>
#include <QStringList>
#include <QStack>
#include <QByteArray>
#include "PixmapItem.h"
#include "Globals.h"

class Selected final {
public:
    Selected() : stack(), origin({OriginNull, 0}), offset() {}
	QStringList stack;
    Origin origin;
    QPointF offset;
};

class State final {
public:
	State();
	State(const QList<QStringList>& );
	QByteArray toJson();
	bool fromJson(const QByteArray& );
	QString toString() const;
	QStringList reserves;
	QStringList foundations;
	QList<QStringList> cascades;
	Selected selected;
	bool lastWasUndo;
};

class History final {
public:
	QStack<QByteArray> stack;
};
