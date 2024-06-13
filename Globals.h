// vim: tabstop=4 shiftwidth=4 noexpandtab
#pragma once
#include <QString>
#include <QStringList>

const QString Suit = "CDHS";
const QString Rank = "A23456789TJQK";
const QString Reserves = "ABCD";
const QString Foundations = "CDHS";
const QStringList ReservePlaceholder = {"RA", "RB", "RC", "RD"};
const QStringList FoundationPlaceholders = {"FC", "FD", "FH", "FS"};

constexpr int MAX_CASCADES = 8;
constexpr int MAX_STACK_LEN = 32;

enum SuitNo {
	Clubs = 0,
	Diamonds,
	Hearts,
	Spades
};

enum Color {
	Black = 0,
	Red
};

enum RankNo {
	Ace = 0,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten,
	Jack,
	Queen,
	King
};

enum OriginType {
	OriginNull,
	OriginFreeCell,
	OriginCascade
};

struct Origin {
	int type;
	int idx;
};
