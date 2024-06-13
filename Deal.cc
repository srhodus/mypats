// vim: tabstop=4 shiftwidth=4 noexpandtab
#include <QList>
#include <QStringList>
#include "Globals.h"

#define RMAX32 ((1U << 31) - 1)

QList<QStringList> getDeal(int seed, int cascadeCount) {
	constexpr int NO_CARDS_IN_DECK = 52;
	int last = seed;
	auto rand = [&last]() {
		return (last = (last * 214013 + 2531011) & (int)RMAX32) >> 16;
    };
	int deck[NO_CARDS_IN_DECK] = {0};
	for (int i = 0; i < NO_CARDS_IN_DECK; i++) {
		deck[i] = (NO_CARDS_IN_DECK-1)-i;
	}
	for (int i = 0; i < (NO_CARDS_IN_DECK-1); i++) {
		int j = (NO_CARDS_IN_DECK-1)-rand()%(NO_CARDS_IN_DECK-i);
		seed = deck[i];
		deck[i] = deck[j];
		deck[j] = seed;
	}
	QList<QStringList> sl;
	for (int i = 0; i < cascadeCount; i++) {
		sl.push_back({});
	}
	int idx = 0;
	for (int i = 0; i < NO_CARDS_IN_DECK; i++) {
		QChar rank = Rank[static_cast<int>(deck[i]/4)];
		QChar suit = Suit[static_cast<int>(deck[i]%4)];
		auto temp = QString::asprintf("%c%c", rank.toLatin1(), suit.toLatin1());
		if (idx >= cascadeCount) {
			idx = 0;
		}
		sl[idx++].push_back(temp);
	}
	return sl;
}
