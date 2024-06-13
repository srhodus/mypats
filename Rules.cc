// vim: tabstop=4 shiftwidth=4 noexpandtab
#include <QtGlobal>
#include <QDebug>
#include <QtMath>
#include <QVarLengthArray>
#include <QMap>
#include "Rules.h"

SuitNo suit(const QString& str) {
	Q_ASSERT(str.size() == 2);
	const auto i = Suit.indexOf(str[1]);
	Q_ASSERT(i != -1);
	return static_cast<SuitNo>(i);
}

RankNo rank(const QString& str) {
	Q_ASSERT(str.size() == 2);
	const auto i = Rank.indexOf(str[0]);
	Q_ASSERT(i != -1);
	return static_cast<RankNo>(i);
}

Color color(const QString& str) {
	Q_ASSERT(str.size() == 2);
	return (suit(str) == Diamonds || suit(str) == Hearts) ? Red : Black;
}

bool isGameWon(const QStringList& s) {
	if (s.size() == 0) {
		return false;
	}
	for (int i = 0; i < s.size(); i++) {
		if (s[i].isEmpty()) {
			return false;
		}
		if (rank(s[i]) != King) {
			return false;
		}
	}
	return true;
}

bool isValidSingleStacking(const QStringList& s1, int i) {
	if (s1.size() == 0) {
		return false;
	}
	if (s1.size() == 1) {
		return true;
	}
	if (i < 0 || i >= s1.size()) {
		return false;
	}
	if ((i - s1.size()-1) == 0) {
		return true;
	}
	for (int j = i, k = j+1; j < s1.size()-1; j++, k++) {
		if (color(s1[j]) == color(s1[k])) {
			// Cards of same color stacked on top of each other
			return false;
		}
		if (rank(s1[j])-1 != rank(s1[k])) {
			// Cards stacked in wrong sequence
			return false;
		}
	}
	return true;
}

bool canMoveToReserve(const QString& s1, const QString& str) {
	if (s1.size() != 2) {
		return false;
	}
	if (str.isEmpty()) {
		return true;
	}
	return false;
}

bool canMoveToFoundation(const QString& s1, const QString& str) {
	if (s1.size() != 2) {
		return false;
	}
	if (str.isEmpty()) {
		if (rank(s1) == Ace) {
			return true;
		}
		return false;
	}
	if (str.size() != 2) {
		return false;
	}
	if (rank(str)+1 == rank(s1)) {
		if (suit(s1) == suit(str)) {
			return true;
		}
	}
	return false;
}

bool canMoveToCascade(const QStringList& s1, const QStringList& s2) {
	if (s2.size() == 0) {
		return false;
	}
	if (!isValidSingleStacking(s2, 0)) {
		return false;
	}
	if (s1.size() == 0) {
		return true;
	}
	if (color(s1[s1.size()-1]) != color(s2[0])) {
		if (rank(s1[s1.size()-1]) == rank(s2[0])+1) {
			// Last card of the left stack is a different color and a lower
			// rank than the first card of the right stack
			return true;
		}
	}
	return false;
}

QString getAutoMove(const QStringList& reserves, const QStringList&
		foundations, const QList<QStringList>& cascades) {
	auto eval = [&](const QString& str) {
		if (str.isEmpty() && str.size() != 2) {
			return false;
		}
		if (rank(str) == Ace) {
			// Always automove an ace to its foundation
			return true;
		} else if (rank(str) == Two) {
			const auto i = Foundations.indexOf(str[1]);
			Q_ASSERT(i != -1);
			if (i != -1) {
				if (foundations.size() > i && !foundations[i].isEmpty()) {
					if (rank(foundations[i]) == Ace) {
						// Automove a two if its corresponding suit's ace is
						// already in the foundation slot
						return true;
					}
				}
			}
		} else {
			const auto i = Foundations.indexOf(str[1]);
			Q_ASSERT(i != -1);
			const auto r1 = rank(str);
			if (foundations[i].isEmpty()) {
				return false;
			}
			auto r2 = rank(foundations[i]);
			if (r1-1 == r2) {
				int ops[] = {Diamonds, Hearts};
				if (color(str) == Red) {
					ops[0] = Clubs;
					ops[1] = Spades;
				}
				int n = 0;
				size_t nops = sizeof(ops)/sizeof(ops[0]);
				for (size_t j = 0; j < nops; j++) {
					if (foundations[ops[j]].isEmpty()) {
						continue;
					}
					r2 = rank(foundations[ops[j]]);
					if (r2 >= r1-1) {
						n++;
					}
				}
				if (n == static_cast<int>(nops)) {
					// If the opposite suits' foundations ranks are all gte
					// to this card's rank-1, then the card can be automoved
					return true;
				}
			}
		}
		return false;
	};
	QString ret;
	for (int i = 0; i < reserves.size(); i++) {
		if (eval(reserves[i])) {
			Q_ASSERT(Reserves.size() > i);
			ret.push_back(Reserves[i]);
			ret.push_back('H');
			break;
		}
	}
	if (!ret.isEmpty()) {
		return ret;
	}
	for (int j = 0; j < cascades.size(); j++) {
		if (cascades[j].size() == 0) {
			continue;
		}
		if (eval(cascades[j][cascades[j].size()-1])) {
			ret.push_back(QString::number(j));
			ret.push_back('H');
			break;
		}
	}
	return ret;
}

QSet<QString> getAvailMoves(const QStringList& reserves, const QStringList&
		foundations, const QList<QStringList>& cascades, bool all) {
	QSet<QString> ret;
	if (all) {
		// Include moves from reserves to foundations
		for (int i = 0; i < reserves.size(); i++) {
			Q_ASSERT(Reserves.size() > i);
			for (int j = 0; j < foundations.size(); j++) {
				Q_ASSERT(Foundations.size() > j);
				if (canMoveToFoundation(reserves[i], foundations[j])) {
					QString temp;
					temp.push_back(Reserves[i]);
					temp.push_back('H');
					ret.insert(temp);
				}
			}
		}
		// Include moves from cascades to foundations
		for (int i = 0; i < cascades.size(); i++) {
			if (cascades[i].size() == 0) {
				continue;
			}
			const QString s(cascades[i][cascades[i].size()-1]);
			if (!s.isEmpty()) {
				for (int j = 0; j < reserves.size(); j++) {
					if (reserves[j].isEmpty()) {
						QString temp;
						temp.push_back(QString::number(i));
						Q_ASSERT(Reserves.size() > j);
						temp.push_back(Reserves[j]);
						ret.insert(temp);
						break;
					}
				}
				for (int j = 0; j < foundations.size(); j++) {
					Q_ASSERT(Foundations.size() > j);
					if (canMoveToFoundation(s, foundations[j])) {
						QString temp;
						temp.push_back(QString::number(i));
						temp.push_back('H');
						ret.insert(temp);
					}
				}
			}
		}
	}
	// Cascade to cascade moves
	for (int i = 0; i < cascades.size(); i++) {
		for (int j = 0; j < cascades.size(); j++) {
			if (i == j) {
				// Don't compare a cascade to itself
				continue;
			}
			if (getMovableStackSize(i, j, reserves, cascades) > 0) {
				QString temp;
				temp.append(QString::number(i));
				temp.append(QString::number(j));
				ret.insert(temp);
			}
		}
	}
	return ret;
}

int getMovableStackSize(int from, int to, const QStringList& reserves,
		const QList<QStringList>& cascades) {
	const auto& rhs = cascades[from];
	const auto& lhs = cascades[to];
	QVarLengthArray<int> ar;
	for (int i = 0; i < rhs.size(); i++) {
		if (lhs.size() == 0) {
			if (isValidSingleStacking(rhs, i)) {
				ar.append(static_cast<int>(rhs.size())-i);
			}
			continue;
		}
		const auto last = lhs[lhs.size()-1];
		if (rank(last)-1 == rank(rhs[i]) && color(last) != color(rhs[i])) {
			if (isValidSingleStacking(rhs, i)) {
				ar.append(static_cast<int>(rhs.size())-i);
			}
		}
	}
	int max = getMaxMovableSize(to, reserves, cascades);
	// If there's not enough space left to move the entire stack, try any valid
	// smaller stacks on the same cascade
	for (const auto i : ar) {
		if (i <= max) {
			return i;
		}
	}
	return 0;
}

int getMaxMovableSize(int to, const QStringList& reserves,
		const QList<QStringList>& cascades) {
	// (1+n)*2^(m)
	// where m is the number of empty cascades (i.e., columns)
	// and n is the number of empty freecells (i.e., reservess)
	int m = 0;
	for (int i = 0; i < cascades.size(); i++) {
		if (i == to) {
			// Don't include destination cascade in max movable stack size
			continue;
		}
		if (cascades[i].size() == 0) {
			m++;
		}
	}
	int n = 1;
	for (int i = 0; i < reserves.size(); i++) {
		if (reserves[i].isEmpty()) {
			n++;
		}
	}
	return n *= static_cast<int>(qPow(2, m));
}

bool validate(const QStringList& reserves, const QStringList& foundations,
		const QList<QStringList>& cascades, QString& error) {
	QStringList pile;
	// Put the reserves cards in a pile
	for (const auto& i : reserves) {
		if (i.isEmpty()) {
			continue;
		}
		pile.append(i);
	}
	// Add the foundations cards to the pile
	for (const auto& i : foundations) {
		if (i.isEmpty()) {
			continue;
		}
		pile.append(i);
	}
	// Add each cascade's cards to the pile
	for (const auto& i : cascades) {
		if (i.isEmpty()) {
			continue;
		}
		pile.append(i);
	}
	// Backfill any cards missing from the foundations (i.e., any cards of a
	// lesser rank than the top card).
	for (int i = 0; i < foundations.size(); i++) {
		if (foundations[i].isEmpty()) {
			continue;
		}
		int r = rank(foundations[i]);
		for (int j = 0; j < r; j++) {
			Q_ASSERT(foundations[i].size() == 2);
			pile.append(QString::asprintf("%c%c", Rank[j].toLatin1(),
						foundations[i][1].toLatin1()));
		}
	}
	QMap<QString, bool> deck;
	for (const auto& i : Suit) {
		for (const auto& j : Rank) {
			deck.insert(QString::asprintf("%c%c", j.toLatin1(), i.toLatin1()),
					false);
		}
	}
	for (const auto& i : pile) {
		Q_ASSERT(i.size() == 2);
		if (deck.contains(i)) {
			deck[i] = true;
		}
	}
	for (const auto& k : deck.keys()) {
		if (!deck.value(k)) {
			error.append(k);
			error.append(" ");
		}
	}
	error = error.trimmed();
	return error.isEmpty() ? true : false;
}
