// vim: tabstop=4 shiftwidth=4 noexpandtab
#include <QStringList>
#include <QString>
#include <QSet>
#include "Globals.h"

SuitNo suit(const QString& );
RankNo rank(const QString& );
Color color(const QString& );
bool isGameWon(const QStringList& );
bool isValidSingleStacking(const QStringList&, int );
bool canMoveToReserve(const QString&, const QString& );
bool canMoveToFoundation(const QString&, const QString& );
bool canMoveToCascade(const QStringList&, const QStringList& );
QString getAutoMove(const QStringList&, const QStringList&,
		const QList<QStringList>& );
QSet<QString> getAvailMoves(const QStringList&, const QStringList&,
		const QList<QStringList>&, bool all = false);
int getMovableStackSize(int, int, const QStringList&, const QList<QStringList>& );
int getMaxMovableSize(int to, const QStringList&, const QList<QStringList>& );
bool validate(const QStringList&, const QStringList&, const QList<QStringList>&,
		QString& );
