// vim: tabstop=4 shiftwidth=4 noexpandtab
#include <QDebug>
#include <QString>
#include <QList>
#include <gtest/gtest.h>
#include "../Rules.h"

TEST(isValidSingleStacking, IsValidSingleStackWholeStack1) {
	const QStringList sl = {
		"KD",
		"QC",
		"JH",
		"TC",
		"9D",
		"8C",
		"7H",
		"6S",
		"5H",
		"4C",
		"3H",
		"2S",
		"AH" };
	EXPECT_EQ(true, isValidSingleStacking(sl, 0));
}

TEST(isValidSingleStacking, IsValidSingleStackWholeStack2) {
	const QStringList sl = {
		"KS",
		"QH",
		"JS",
		"TH",
		"9S",
		"8H",
		"7S",
		"6H",
		"5S",
		"4H",
		"3S",
		"2H",
		"AS" };
	EXPECT_EQ(true, isValidSingleStacking(sl, 0));
}

TEST(isValidSingleStacking, IsValidSingleStackWholeStack3) {
	const QStringList sl = {
		"KS",
		"QH",
		"JS",
		"TH",
		"9S",
		"8H",
		"7S",
		"6H",
		"5S",
		"4H",
		"3S",
		"2H",
		"4S" };
	EXPECT_EQ(false, isValidSingleStacking(sl, 0));
}

TEST(isValidSingleStacking, IsValidSingleStackWholeStack4) {
	const QStringList sl = {
		"KS",
		"QH",
		"JS",
		"TH",
		"9S",
		"8H",
		"7S",
		"6H",
		"5S",
		"4H",
		"3S",
		"2H",
		"4H" };
	EXPECT_EQ(false, isValidSingleStacking(sl, 0));
}

TEST(isValidSingleStacking, IsValidSingleStackWholeStack5) {
	const QStringList sl = {
		"KS",
		"QH",
		"JS",
		"TH",
		"9S",
		"8H",
		"7S",
		"6H",
		"5S",
		"4H",
		"3S",
		"2H",
		"AH" };
	EXPECT_EQ(false, isValidSingleStacking(sl, 0));
}

TEST(isValidSingleStacking, IsValidSingleStackWholeStack6) {
	const QStringList sl = {
		"KS",
		"QH",
		"JS",
		"TH",
		"9S",
		"8H",
		"7S",
		"6H",
		"5S",
		"4H",
		"3S",
		"2H",
		"KS" };
	EXPECT_EQ(false, isValidSingleStacking(sl, 0));
}

TEST(isValidSingleStacking, IsValidSingleStackTwoCards1) {
	const QStringList sl = {
		"2H",
		"AS"
	};
	EXPECT_EQ(true, isValidSingleStacking(sl, 0));
}

TEST(isValidSingleStacking, IsValidSingleStackTwoCards2) {
	const QStringList sl = {
		"KH",
		"QS"
	};
	EXPECT_EQ(true, isValidSingleStacking(sl, 0));
}

TEST(isValidSingleStacking, IsValidSingleStackTwoCards3) {
	const QStringList sl = {
		"KH",
		"JS"
	};
	EXPECT_EQ(false, isValidSingleStacking(sl, 0));
}

TEST(isValidSingleStacking, IsValidSingleStackTwoCards4) {
	const QStringList sl = {
		"KH",
		"QH"
	};
	EXPECT_EQ(false, isValidSingleStacking(sl, 0));
}

TEST(isValidSingleStacking, IsValidSingleStackOneCard1) {
	const QStringList sl = {
		"AS"
	};
	EXPECT_EQ(true, isValidSingleStacking(sl, 0));
}

TEST(isValidSingleStacking, IsValidSingleStackOneCard2) {
	const QStringList sl = {
		"KC"
	};
	EXPECT_EQ(true, isValidSingleStacking(sl, 0));
}

TEST(isValidSingleStacking, IsValidSingleStackNoCards) {
	const QStringList sl;
	EXPECT_EQ(false, isValidSingleStacking(sl, 0));
}

TEST(isValidSingleStacking, IsValidSingleStackWithIndex1) {
	const QStringList sl = {
		"9H",
		"7S",
		"6D"
	};
	EXPECT_EQ(true, isValidSingleStacking(sl, 1));
}

TEST(isValidSingleStacking, IsValidSingleStackWithIndex2) {
	const QStringList sl = {
		"9H",
		"7S",
		"6C"
	};
	EXPECT_EQ(true, isValidSingleStacking(sl, 2));
}

TEST(isValidSingleStacking, IsValidSingleStackWithIndex3) {
	const QStringList sl = {
		"9H",
		"7S",
		"6C"
	};
	EXPECT_EQ(false, isValidSingleStacking(sl, static_cast<int>(sl.size())));
}

TEST(canMoveToReserve, canMoveToReserve1) {
	const QString s("AH");
	const QString r;
	EXPECT_EQ(true, canMoveToReserve(s, r));
}

TEST(canMoveToReserve, canMoveToReserve2) {
	const QString s("KC");
	const QString r;
	EXPECT_EQ(true, canMoveToReserve(s, r));
}

TEST(canMoveToReserve, canMoveToReserve3) {
	const QString s("KC");
	const QString r("AD");
	EXPECT_EQ(false, canMoveToReserve(s, r));
}

TEST(canMoveToReserve, canMoveToReserve4) {
	const QString s("QS");
	const QString r;
	EXPECT_EQ(true, canMoveToReserve(s, r));
}

TEST(canMoveToReserve, canMoveToReserve5) {
	const QString s("QS");
	const QString r("8D");
	EXPECT_EQ(false, canMoveToReserve(s, r));
}

TEST(canMoveToReserve, canMoveToReserve6) {
	const QString s("2D");
	const QString r("2D");
	EXPECT_EQ(false, canMoveToReserve(s, r));
}

TEST(canMoveToReserve, canMoveToReserve7) {
	const QString s;
	const QString r;
	EXPECT_EQ(false, canMoveToReserve(s, r));
}

TEST(canMoveToFoundation, canMoveToFoundation1) {
	const QString s("AD");
	const QString r;
	EXPECT_EQ(true, canMoveToFoundation(s, r));
}

TEST(canMoveToFoundation, canMoveToFoundation2) {
	const QString s("KD");
	const QString r("QD");
	EXPECT_EQ(true, canMoveToFoundation(s, r));
}

TEST(canMoveToFoundation, canMoveToFoundation3) {
	const QString s("2D");
	const QString r;
	EXPECT_EQ(false, canMoveToFoundation(s, r));
}

TEST(canMoveToFoundation, canMoveToFoundation4) {
	const QString s("2D");
	const QString r("3S");
	EXPECT_EQ(false, canMoveToFoundation(s, r));
}

TEST(canMoveToFoundation, canMoveToFoundation5) {
	const QString s("KS");
	const QString r("KS");
	EXPECT_EQ(false, canMoveToFoundation(s, r));
}

TEST(canMoveToFoundation, canMoveToFoundation6) {
	const QString s;
	const QString r;
	EXPECT_EQ(false, canMoveToFoundation(s, r));
}

TEST(canMoveToCascade, canMoveToCascade1) {
	const QStringList sl1;
	const QStringList sl2 = {
		"8C"
	};
	EXPECT_EQ(true, canMoveToCascade(sl1, sl2));
}

TEST(canMoveToCascade, canMoveToCascade2) {
	const QStringList sl1 = {
		"9H"
	};
	const QStringList sl2 = {
		"8C"
	};
	EXPECT_EQ(true, canMoveToCascade(sl1, sl2));
}

TEST(canMoveToCascade, canMoveToCascade3) {
	const QStringList sl1 = {
		"TS",
		"9H"
	};
	const QStringList sl2 = {
		"8C"
	};
	EXPECT_EQ(true, canMoveToCascade(sl1, sl2));
}

TEST(canMoveToCascade, canMoveToCascade4) {
	const QStringList sl1 = {
		"KH",
		"QC",
		"JD",
		"TS",
		"9H"
	};
	const QStringList sl2 = {
		"8C"
	};
	EXPECT_EQ(true, canMoveToCascade(sl1, sl2));
}

TEST(canMoveToCascade, canMoveToCascade5) {
	const QStringList sl1 = {
		"KH",
		"QC",
		"JD",
		"TS",
		"9H"
	};
	const QStringList sl2 = {
		"8C",
		"7H"
	};
	EXPECT_EQ(true, canMoveToCascade(sl1, sl2));
}

TEST(canMoveToCascade, canMoveToCascade6) {
	const QStringList sl1 = {
		"KH",
		"QC",
		"JD",
		"TS",
		"9H"
	};
	const QStringList sl2 = {
		"8C",
		"7H",
		"6S",
		"5D",
		"4C",
		"3D",
		"2S"
	};
	EXPECT_EQ(true, canMoveToCascade(sl1, sl2));
}

TEST(canMoveToCascade, canMoveToCascade7) {
	const QStringList sl1 = {
		"KH",
		"QC",
		"JD",
		"TS",
		"9H"
	};
	const QStringList sl2 = {
		"8C",
		"7H",
		"6S",
		"5D",
		"4C",
		"3D",
		"2S",
		"AH"
	};
	EXPECT_EQ(true, canMoveToCascade(sl1, sl2));
}

TEST(canMoveToCascade, canMoveToCascade8) {
	const QStringList sl1 = {
		"KH"
	};
	const QStringList sl2 = {
		"QC",
		"JD",
		"TS",
		"9H",
		"8C",
		"7H",
		"6S",
		"5D",
		"4C",
		"3D",
		"2S",
		"AH"
	};
	EXPECT_EQ(true, canMoveToCascade(sl1, sl2));
}

TEST(canMoveToCascade, canMoveToCascade9) {
	const QStringList sl1;
	const QStringList sl2 = {
		"KD",
		"QC",
		"JD",
		"TS",
		"9H",
		"8C",
		"7H",
		"6S",
		"5D",
		"4C",
		"3D",
		"2S",
		"AH"
	};
	EXPECT_EQ(true, canMoveToCascade(sl1, sl2));
}

TEST(canMoveToCascade, canMoveToCascade10) {
	const QStringList sl1;
	const QStringList sl2 = {
		"AH"
	};
	EXPECT_EQ(true, canMoveToCascade(sl1, sl2));
}

TEST(canMoveToCascade, canMoveToCascade11) {
	const QStringList sl1;
	const QStringList sl2 = {
		"2H"
	};
	EXPECT_EQ(true, canMoveToCascade(sl1, sl2));
}

TEST(canMoveToCascade, canMoveToCascade12) {
	const QStringList sl1;
	const QStringList sl2;
	EXPECT_EQ(false, canMoveToCascade(sl1, sl2));
}

TEST(canMoveToCascade, canMoveToCascade13) {
	const QStringList sl1 = {
		"3S"
	};
	const QStringList sl2;
	EXPECT_EQ(false, canMoveToCascade(sl1, sl2));
}

TEST(canMoveToCascade, canMoveToCascade14) {
	const QStringList sl1 = {
		"3S"
	};
	const QStringList sl2 = {
		"3S"
	};
	EXPECT_EQ(false, canMoveToCascade(sl1, sl2));
}

TEST(canMoveToCascade, canMoveToCascade15) {
	const QStringList sl1 = {
		"3S"
	};
	const QStringList sl2 = {
		"2C"
	};
	EXPECT_EQ(false, canMoveToCascade(sl1, sl2));
}

TEST(canMoveToCascade, canMoveToCascade16) {
	const QStringList sl1 = {
		"3S"
	};
	const QStringList sl2 = {
		"4D"
	};
	EXPECT_EQ(false, canMoveToCascade(sl1, sl2));
}

TEST(canMoveToCascade, canMoveToCascade17) {
	const QStringList sl1 = {
		"2C", "6D", "4S", "4H", "TS"
	};
	const QStringList sl2 = {
		"9H"
	};
	EXPECT_EQ(true, canMoveToCascade(sl1, sl2));
}

TEST(canMoveToCascade, canMoveToCascade18) {
	const QStringList sl1 = {
		"2C", "6D", "4S", "4H", "TS"
	};
	const QStringList sl2 = {
		"9S"
	};
	EXPECT_EQ(false, canMoveToCascade(sl1, sl2));
}

TEST(getAutoMove, getAutoMove1) {
	const QStringList reserves = {
		"AC"
	};
	const QStringList foundations;
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{}
	};
	EXPECT_EQ("AH", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove2) {
	const QStringList reserves = {
		"", "AD"
	};
	const QStringList foundations;
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{}
	};
	EXPECT_EQ("BH", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove3) {
	const QStringList reserves = {
		"3D", "2H", "AS", "8H"
	};
	const QStringList foundations = {
		"", "", "", ""
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{}
	};
	EXPECT_EQ("CH", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove4) {
	const QStringList reserves = {
		"3D", "2H", "8S", "AH"
	};
	const QStringList foundations = {
		"", "", "", ""
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{}
	};
	EXPECT_EQ("DH", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove5) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations;
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{}
	};
	EXPECT_EQ("", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove6) {
	const QStringList reserves = {
		"2C", "", "", ""
	};
	const QStringList foundations = {
		"AC", "", "", ""
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{}
	};
	EXPECT_EQ("AH", getAutoMove(reserves, foundations, cascades));
}


TEST(getAutoMove, getAutoMove7) {
	const QStringList reserves = {
		"2C", "", "", ""
	};
	const QStringList foundations = {
		"", "", "", ""
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{}
	};
	EXPECT_EQ("", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove8) {
	const QStringList reserves = {
		"", "2D", "", ""
	};
	const QStringList foundations = {
		"", "AD", "", ""
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{}
	};
	EXPECT_EQ("BH", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove9) {
	const QStringList reserves = {
		"", "", "2H", ""
	};
	const QStringList foundations = {
		"", "", "AH", ""
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{}
	};
	EXPECT_EQ("CH", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove10) {
	const QStringList reserves = {
		"", "", "", "2S"
	};
	const QStringList foundations = {
		"", "", "", "AS"
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{}
	};
	EXPECT_EQ("DH", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove11) {
	const QStringList reserves = {
		"", "", "", "2S"
	};
	const QStringList foundations = {
		"", "", "", ""
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{}
	};
	EXPECT_EQ("", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove12) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"", "", "", ""
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{}
	};
	EXPECT_EQ("", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove13) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"", "", "", ""
	};
	const QList<QStringList> cascades = {
		{"AS"},
		{},
		{},
		{},
		{},
		{},
		{},
		{}
	};
	EXPECT_EQ("0H", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove14) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"", "", "", ""
	};
	const QList<QStringList> cascades = {
		{"5C", "6S", "AD"},
		{},
		{},
		{},
		{},
		{},
		{},
		{}
	};
	EXPECT_EQ("0H", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove15) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"", "", "", ""
	};
	const QList<QStringList> cascades = {
		{"5C", "6S", "8C"},
		{"8D"},
		{},
		{},
		{},
		{},
		{},
		{"AC"}
	};
	EXPECT_EQ("7H", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove16) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"", "", "", ""
	};
	const QList<QStringList> cascades = {
		{"5C", "6S", "8C"},
		{"8D"},
		{"2S", "6D"},
		{"2D", "7D", "3S", "4S", "5D"},
		{},
		{},
		{"8C", "4H", "7H", "2D", "TH", "JH", "QD", "KH", "AC"},
		{"2C"}
	};
	EXPECT_EQ("6H", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove17) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"AC", "", "", ""
	};
	const QList<QStringList> cascades = {
		{"5C", "6S", "8C"},
		{"8D"},
		{"2S", "6D"},
		{"2D", "7D", "3S", "4S", "5D"},
		{},
		{},
		{"8C", "4H", "7H", "2D", "TH", "JH", "QD", "KH"},
		{"2C"}
	};
	EXPECT_EQ("7H", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove18) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"", "", "", ""
	};
	const QList<QStringList> cascades = {
		{"5C", "6S", "8C"},
		{"8D"},
		{"2S", "6D"},
		{"2D", "7D", "3S", "4S", "5D"},
		{},
		{},
		{"8C", "4H", "7H", "2D", "TH", "JH", "QD", "KH", "3H"},
		{"2C"}
	};
	EXPECT_EQ("", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove19) {
	const QStringList reserves = {
		"JD", "3S", "8S", "9H"
	};
	const QStringList foundations = {
		"", "2D", "AH", ""
	};
	const QList<QStringList> cascades = {
		{"AC", "KC", "KS", "7D", "KH", "3D", "3C"},
		{"5H", "JH", "JS", "4D", "6D", "5C"},
		{"TH", "7C", "9S", "4S", "6S", "2C"},
		{"TS"},
		{"AS", "8H", "9C", "9D", "8C", "7H", "6C", "5D", "4C"},
		{"QC", "JC", "KD", "3H"},
		{"8D", "7S", "QS", "6H", "QH", "QD"},
		{"2S", "TC", "5S", "TD", "4H", "2H"}
	};
	EXPECT_EQ("7H", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove20) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"", "2D", "2H", "2S"
	};
	const QList<QStringList> cascades = {
		{},
		{"3S"},
		{},
		{},
		{},
		{},
		{},
		{}
	};
	EXPECT_EQ("1H", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove21) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"", "3D", "3H", "2S"
	};
	const QList<QStringList> cascades = {
		{},
		{"3S"},
		{},
		{},
		{},
		{},
		{},
		{}
	};
	EXPECT_EQ("1H", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove22) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"", "AD", "AH", "2S"
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{"3S"}
	};
	EXPECT_EQ("", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove23) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"", "", "", "2S"
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{"3S"},
		{},
		{},
		{},
		{}
	};
	EXPECT_EQ("", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove24) {
	const QStringList reserves = {
		"", "", "3S", ""
	};
	const QStringList foundations = {
		"", "", "", "2S"
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{}
	};
	EXPECT_EQ("", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove25) {
	const QStringList reserves = {
		"", "", "2S", ""
	};
	const QStringList foundations = {
		"", "", "", "AS"
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{}
	};
	EXPECT_EQ("CH", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove26) {
	const QStringList reserves = {
		"KC", "", "", ""
	};
	const QStringList foundations = {
		"QC", "KD", "KH", "KS"
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{}
	};
	EXPECT_EQ("AH", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove27) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"QC", "KD", "KH", "KS"
	};
	const QList<QStringList> cascades = {
		{"KC"},
		{},
		{},
		{},
		{},
		{},
		{},
		{}
	};
	EXPECT_EQ("0H", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove28) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"QC", "QD", "QH", "QS"
	};
	const QList<QStringList> cascades = {
		{"KC"},
		{"KD"},
		{"KH"},
		{"KS"},
		{},
		{},
		{},
		{}
	};
	EXPECT_EQ("0H", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove29) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"QC", "JD", "JH", "JS"
	};
	const QList<QStringList> cascades = {
		{"KC"},
		{"QD", "KD"},
		{"QH", "KH"},
		{"QS", "KS"},
		{},
		{},
		{},
		{}
	};
	EXPECT_EQ("", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove30) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"QC", "QD", "JH", "JS"
	};
	const QList<QStringList> cascades = {
		{"KC"},
		{"KD"},
		{"QH", "KH"},
		{"QS", "KS"},
		{},
		{},
		{},
		{}
	};
	EXPECT_EQ("", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove31) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"QC", "QD", "KH", "JS"
	};
	const QList<QStringList> cascades = {
		{"KC"},
		{"KD"},
		{},
		{"QS", "KS"},
		{},
		{},
		{},
		{}
	};
	EXPECT_EQ("0H", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove32) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"KC", "QD", "KH", "JS"
	};
	const QList<QStringList> cascades = {
		{},
		{"KD"},
		{},
		{"KS", "QS"},
		{},
		{},
		{},
		{}
	};
	EXPECT_EQ("3H", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove33) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"KC", "QD", "KH", "QS"
	};
	const QList<QStringList> cascades = {
		{},
		{"KD"},
		{},
		{"KS"},
		{},
		{},
		{},
		{}
	};
	EXPECT_EQ("1H", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove34) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"KC", "KD", "KH", "QS"
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{"KS"}
	};
	EXPECT_EQ("7H", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove35) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"KC", "KD", "KH", "4S"
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{"5S"}
	};
	EXPECT_EQ("7H", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove36) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"KC", "KD", "KH", "4S"
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{"2S"}
	};
	EXPECT_EQ("", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove37) {
	const QStringList reserves = {
		"3D", "KH", "", ""
	};
	const QStringList foundations = {
		"2C", "2D", "2H", "2S"
	};
	const QList<QStringList> cascades;
	EXPECT_EQ("AH", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove38) {
	const QStringList reserves = {
		"KS", "KH", "", ""
	};
	const QStringList foundations = {
		"KC", "QD", "QH", "QS"
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{"KD"},
		{}
	};
	EXPECT_EQ("AH", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove39) {
	const QStringList reserves = {
		"", "KH", "", ""
	};
	const QStringList foundations = {
		"KC", "QD", "QH", "KS"
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{"KD"},
		{}
	};
	EXPECT_EQ("BH", getAutoMove(reserves, foundations, cascades));
}

TEST(getAutoMove, getAutoMove40) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"KC", "QD", "KH", "KS"
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{"KD"},
		{}
	};
	EXPECT_EQ("6H", getAutoMove(reserves, foundations, cascades));
}

TEST(getMaxMovableSize, getMaxMovableSize1) {
	const QStringList reserves = {
		"AS", "AC", "AH", "AD"
	};
	const QList<QStringList> cascades = {
		{"2S"},
		{"2H"},
		{"2D"},
		{"2C"},
		{"3S"},
		{"3H"},
		{"3D"},
		{"3C"}
	};
	EXPECT_EQ(1, getMaxMovableSize(0, reserves, cascades));
}

TEST(getMaxMovableSize, getMaxMovableSize2) {
	const QStringList reserves = {
		"", "AC", "AH", "AD"
	};
	const QList<QStringList> cascades = {
		{"2S"},
		{"2H"},
		{"2D"},
		{"2C"},
		{"3S"},
		{"3H"},
		{"3D"},
		{"3C"}
	};
	EXPECT_EQ(2, getMaxMovableSize(0, reserves, cascades));
}

TEST(getMaxMovableSize, getMaxMovableSize3) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QList<QStringList> cascades = {
		{"2S"},
		{"2H"},
		{"2D"},
		{"2C"},
		{"3S"},
		{"3H"},
		{"3D"},
		{"3C"}
	};
	EXPECT_EQ(5, getMaxMovableSize(0, reserves, cascades));
}

TEST(getMaxMovableSize, getMaxMovableSize4) {
	const QStringList reserves = {
		"", "AC", "AH", "AD"
	};
	const QList<QStringList> cascades = {
		{"2S"},
		{"2H"},
		{"2D"},
		{"2C"},
		{"3S"},
		{"3H"},
		{"3D"},
		{}
	};
	EXPECT_EQ(4, getMaxMovableSize(0, reserves, cascades));
}

TEST(getMaxMovableSize, getMaxMovableSize5) {
	const QStringList reserves = {
		"", "AC", "AH", "AD"
	};
	const QList<QStringList> cascades = {
		{"2S"},
		{"2H"},
		{"2D"},
		{"2C"},
		{"3S"},
		{"3H"},
		{},
		{}
	};
	EXPECT_EQ(8, getMaxMovableSize(0, reserves, cascades));
}

TEST(getMaxMovableSize, getMaxMovableSize6) {
	const QStringList reserves = {
		"", "AC", "AH", "AD"
	};
	const QList<QStringList> cascades = {
		{"2S"},
		{"2H"},
		{"2D"},
		{"2C"},
		{"3S"},
		{},
		{},
		{}
	};
	EXPECT_EQ(16, getMaxMovableSize(0, reserves, cascades));
}

TEST(getMaxMovableSize, getMaxMovableSize7) {
	const QStringList reserves = {
		"", "AC", "AH", "AD"
	};
	const QList<QStringList> cascades = {
		{"2S"},
		{"2H"},
		{"2D"},
		{"2C"},
		{},
		{},
		{},
		{}
	};
	EXPECT_EQ(32, getMaxMovableSize(0, reserves, cascades));
}

TEST(getMaxMovableSize, getMaxMovableSize8) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QList<QStringList> cascades = {
		{"3H"},
		{"6S"},
		{"7S"},
		{"8S"},
		{"9S"},
		{"TS"},
		{},
		{}
	};
	EXPECT_EQ(20, getMaxMovableSize(0, reserves, cascades));
}

TEST(getMaxMovableSize, getMaxMovableSize9) {
	const QStringList reserves = {
		"9C", "KD", "", ""
	};
	const QList<QStringList> cascades = {
		{"3H", "6S", "5D", "8D", "5H", "5S", "TD", "9S", "8H", "7S", "6D", "5C", "4D"},
		{"KH", "QS"},
		{"KC", "QH", "JS"},
		{"4S", "3D"},
		{"QD", "7C", "KS", "4H", "3S", "2D"},
		{},
		{"3C", "AD", "TH", "6C", "JH", "TS", "9D", "8S", "7H"},
		{"4C", "JC", "6H", "QC", "JD", "TC", "9H", "8C", "7D"}
	};
	EXPECT_EQ(6, getMaxMovableSize(0, reserves, cascades));
}

TEST(getMaxMovableSize, getMaxMovableSize10) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QList<QStringList> cascades = {
		{"3H"},
		{"6S"},
		{"7S"},
		{"8S"},
		{"9S"},
		{"TS"},
		{"JS"},
		{}
	};
	EXPECT_EQ(10, getMaxMovableSize(0, reserves, cascades));
}

TEST(getMaxMovableSize, getMaxMovableSize11) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{"KH", "QS", "JD"},
		{}
	};
	EXPECT_EQ(320, getMaxMovableSize(0, reserves, cascades));
}

TEST(getMaxMovableSize, getMaxMovableSize12) {
	const QStringList reserves = {
		"2C", "AC", "3C", "4C"
	};
	const QList<QStringList> cascades = {
		{"2D"},
		{"3D"},
		{"4D"},
		{"5D"},
		{"6D"},
		{"7D"},
		{"8D"},
		{"9D"}
	};
	EXPECT_EQ(1, getMaxMovableSize(0, reserves, cascades));
}

TEST(getMaxMovableSize, getMaxMovableSize13) {
	const QStringList reserves = {
		"2C", "AC", "3C", ""
	};
	const QList<QStringList> cascades = {
		{"2D"},
		{"3D"},
		{"4D"},
		{"5D"},
		{"6D"},
		{"7D"},
		{"8D"},
		{"9D"}
	};
	EXPECT_EQ(2, getMaxMovableSize(0, reserves, cascades));
}

TEST(getMaxMovableSize, getMaxMovableSize14) {
	const QStringList reserves = {
		"2C", "AC", "", ""
	};
	const QList<QStringList> cascades = {
		{"2D"},
		{"3D"},
		{"4D"},
		{"5D"},
		{"6D"},
		{"7D"},
		{"8D"},
		{"9D"}
	};
	EXPECT_EQ(3, getMaxMovableSize(0, reserves, cascades));
}

TEST(getMaxMovableSize, getMaxMovableSize15) {
	const QStringList reserves = {
		"2C", "", "", ""
	};
	const QList<QStringList> cascades = {
		{"2D"},
		{"3D"},
		{"4D"},
		{"5D"},
		{"6D"},
		{"7D"},
		{"8D"},
		{"9D"}
	};
	EXPECT_EQ(4, getMaxMovableSize(0, reserves, cascades));
}

TEST(getMaxMovableSize, getMaxMovableSize16) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QList<QStringList> cascades = {
		{"2D"},
		{"3D"},
		{"4D"},
		{"5D"},
		{"6D"},
		{"7D"},
		{"8D"},
		{"9D"}
	};
	EXPECT_EQ(5, getMaxMovableSize(0, reserves, cascades));
}

TEST(getMaxMovableSize, getMaxMovableSize17) {
	const QStringList reserves = {
		"AC", "2C", "3C", "4C"
	};
	const QList<QStringList> cascades = {
		{},
		{"3D"},
		{"4D"},
		{"5D"},
		{"6D"},
		{"7D"},
		{"8D"},
		{"9D"}
	};
	EXPECT_EQ(2, getMaxMovableSize(7, reserves, cascades));
}

TEST(getMaxMovableSize, getMaxMovableSize18) {
	const QStringList reserves = {
		"AC", "2C", "3C", "4C"
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{"4D"},
		{"5D"},
		{"6D"},
		{"7D"},
		{"8D"},
		{"9D"}
	};
	EXPECT_EQ(4, getMaxMovableSize(7, reserves, cascades));
}

TEST(getMaxMovableSize, getMaxMovableSize19) {
	const QStringList reserves = {
		"AC", "2C", "3C", "4C"
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{"5D"},
		{"6D"},
		{"7D"},
		{"8D"},
		{"9D"}
	};
	EXPECT_EQ(8, getMaxMovableSize(7, reserves, cascades));
}

TEST(getMaxMovableSize, getMaxMovableSize20) {
	const QStringList reserves = {
		"AC", "2C", "3C", "4C"
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{"6D"},
		{"7D"},
		{"8D"},
		{"9D"}
	};
	EXPECT_EQ(16, getMaxMovableSize(7, reserves, cascades));
}

TEST(getMaxMovableSize, getMaxMovableSize21) {
	const QStringList reserves = {
		"AC", "2C", "3C", "4C"
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{"7D"},
		{"8D"},
		{"9D"}
	};
	EXPECT_EQ(32, getMaxMovableSize(7, reserves, cascades));
}

TEST(getMaxMovableSize, getMaxMovableSize22) {
	const QStringList reserves = {
		"AC", "2C", "3C", "4C"
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{"8D"},
		{"9D"}
	};
	EXPECT_EQ(64, getMaxMovableSize(7, reserves, cascades));
}

TEST(getMaxMovableSize, getMaxMovableSize23) {
	const QStringList reserves = {
		"AC", "2C", "3C", "4C"
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{"9D"}
	};
	EXPECT_EQ(128, getMaxMovableSize(7, reserves, cascades));
}

TEST(getMaxMovableSize, getMaxMovableSize24) {
	const QStringList reserves = {
		"AC", "2C", "3C", "4C"
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{}
	};
	EXPECT_EQ(128, getMaxMovableSize(2, reserves, cascades));
}

TEST(getMaxMovableSize, getMaxMovableSize25) {
	const QStringList reserves = {
		"AC", "2C", "3C", ""
	};
	const QList<QStringList> cascades = {
		{},
		{"AH"},
		{"2H"},
		{"3H"},
		{"4H"},
		{"5H"},
		{"6H"},
		{"7H"}
	};
	EXPECT_EQ(4, getMaxMovableSize(7, reserves, cascades));
}

TEST(getMaxMovableSize, getMaxMovableSize26) {
	const QStringList reserves = {
		"AC", "2C", "", ""
	};
	const QList<QStringList> cascades = {
		{},
		{"AH"},
		{"2H"},
		{"3H"},
		{"4H"},
		{"5H"},
		{"6H"},
		{"7H"}
	};
	EXPECT_EQ(6, getMaxMovableSize(7, reserves, cascades));
}

TEST(getMaxMovableSize, getMaxMovableSize27) {
	const QStringList reserves = {
		"AC", "", "", ""
	};
	const QList<QStringList> cascades = {
		{},
		{"AH"},
		{"2H"},
		{"3H"},
		{"4H"},
		{"5H"},
		{"6H"},
		{"7H"}
	};
	EXPECT_EQ(8, getMaxMovableSize(7, reserves, cascades));
}

TEST(getMaxMovableSize, getMaxMovableSize28) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QList<QStringList> cascades = {
		{},
		{"AH"},
		{"2H"},
		{"3H"},
		{"4H"},
		{"5H"},
		{"6H"},
		{"7H"}
	};
	EXPECT_EQ(10, getMaxMovableSize(7, reserves, cascades));
}

TEST(getMaxMovableSize, getMaxMovableSize29) {
	const QStringList reserves = {
		"AC", "2C", "", ""
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{"2H"},
		{"3H"},
		{"4H"},
		{"5H"},
		{"6H"},
		{"7H"}
	};
	EXPECT_EQ(12, getMaxMovableSize(7, reserves, cascades));
}

TEST(getMaxMovableSize, getMaxMovableSize30) {
	const QStringList reserves = {
		"AC", "", "", ""
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{"2H"},
		{"3H"},
		{"4H"},
		{"5H"},
		{"6H"},
		{"7H"}
	};
	EXPECT_EQ(16, getMaxMovableSize(7, reserves, cascades));
}

TEST(getMaxMovableSize, getMaxMovableSize31) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{"2H"},
		{"3H"},
		{"4H"},
		{"5H"},
		{"6H"},
		{"7H"}
	};
	EXPECT_EQ(20, getMaxMovableSize(7, reserves, cascades));
}

TEST(getMaxMovableSize, getMaxMovableSize32) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{"3H"},
		{"4H"},
		{"5H"},
		{"6H"},
		{"7H"}
	};
	EXPECT_EQ(40, getMaxMovableSize(7, reserves, cascades));
}

TEST(getMovableStackSize, getMovableStackSize1) {
	const QStringList reserves = {
		"3C", "KD", "5S", ""
	};
	const QStringList foundations = {
		"", "2D", "2H", "2S"
	};
	const QList<QStringList> cascades = {
		{"AC", "KC", "KS", "7D", "KH", "3D"},
		{"5H", "JH", "JS", "4D", "6D", "5C", "4H", "3S"},
		{"TH", "7C", "9S", "4S", "6S", "2C"},
		{"TS", "9H", "8S", "7H", "6C", "5D", "4C", "3H"},
		{"JD", "TC", "9D", "8C"},
		{"QC", "JC", "TD", "9C", "8H"},
		{"8D", "7S", "QS", "6H", "QH", "QD"},
		{}
	};
	EXPECT_EQ(1, getMovableStackSize(0, 7, reserves, cascades));
}

TEST(getMovableStackSize, getMovableStackSize2) {
	const QStringList reserves = {
		"3C", "KD", "5S", ""
	};
	const QStringList foundations = {
		"", "2D", "2H", "2S"
	};
	const QList<QStringList> cascades = {
		{"AC", "KC", "KS", "7D", "KH", "3D", "2C"},
		{"5H", "JH", "JS", "4D", "6D", "5C", "4H", "3S"},
		{"TH", "7C", "9S", "4S", "6S"},
		{"TS", "9H", "8S", "7H", "6C", "5D", "4C", "3H"},
		{"JD", "TC", "9D", "8C"},
		{"QC", "JC", "TD", "9C", "8H"},
		{"8D", "7S", "QS", "6H", "QH", "QD"},
		{}
	};
	EXPECT_EQ(2, getMovableStackSize(0, 7, reserves, cascades));
}

TEST(getMovableStackSize, getMovableStackSize3) {
	const QStringList reserves = {
		"3C", "KD", "5S", ""
	};
	const QStringList foundations = {
		"", "2D", "2H", "2S"
	};
	const QList<QStringList> cascades = {
		{"AC", "KC", "KS", "7D", "4C", "3D", "2C"},
		{"5H", "JH", "JS", "4D", "6D", "5C", "4H", "3S"},
		{"TH", "7C", "9S", "4S", "6S"},
		{"TS", "9H", "8S", "7H", "6C", "5D", "KH", "3H"},
		{"JD", "TC", "9D", "8C"},
		{"QC", "JC", "TD", "9C", "8H"},
		{"8D", "7S", "QS", "6H", "QH", "QD"},
		{}
	};
	EXPECT_EQ(2, getMovableStackSize(0, 7, reserves, cascades));
}

TEST(getMovableStackSize, getMovableStackSize4) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"", "2D", "2H", "2S"
	};
	const QList<QStringList> cascades = {
		{"AC", "KC", "KS", "7D", "4C", "3D", "2C"},
		{"5H", "JH", "JS", "4D", "6D", "5C", "4H", "3S"},
		{"TH", "7C", "9S", "4S", "6S"},
		{"TS", "9H", "8S", "7H", "6C", "5D", "KH", "3H"},
		{"JD", "TC", "9D", "8C"},
		{"QC", "JC", "TD", "9C", "8H"},
		{"8D", "7S", "QS", "6H", "QH", "QD"},
		{}
	};
	EXPECT_EQ(3, getMovableStackSize(0, 7, reserves, cascades));
}

TEST(getMovableStackSize, getMovableStackSize5) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"", "2D", "2H", "2S"
	};
	const QList<QStringList> cascades = {
		{"AC", "KC", "6C", "5H", "4C", "3D", "2C"},
		{"5H", "JH", "JS", "4D", "6D", "5C", "4H", "3S"},
		{"TH", "7C", "9S", "4S", "6S"},
		{"TS", "9H", "8S", "7H", "6C", "5D", "KH", "3H"},
		{"JD", "TC", "9D", "8C"},
		{"QC", "JC", "TD", "9C", "8H"},
		{"8D", "7S", "QS", "6H", "QH", "QD"},
		{}
	};
	EXPECT_EQ(5, getMovableStackSize(0, 7, reserves, cascades));
}

TEST(getMovableStackSize, getMovableStackSize6) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"", "2D", "2H", "2S"
	};
	const QList<QStringList> cascades = {
		{"8C", "7H", "6C", "5H", "4C", "3D", "2C"},
		{"5H", "JH", "JS", "4D", "6D", "5C", "4H", "3S"},
		{"TH", "7C", "9S", "4S", "6S"},
		{"TS", "9H", "8S", "7H", "6C", "5D", "KH", "3H"},
		{"JD", "TC", "9D", "8C"},
		{"QC", "JC", "TD", "9C", "8H"},
		{"8D", "7S", "QS", "6H", "QH", "QD"},
		{}
	};
	EXPECT_EQ(5, getMovableStackSize(0, 7, reserves, cascades));
}

TEST(getMovableStackSize, getMovableStackSize7) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"", "2D", "2H", "2S"
	};
	const QList<QStringList> cascades = {
		{"8C", "7H", "6C", "5H", "4C", "3D", "2C"},
		{"5H", "JH", "JS", "4D", "6D", "5C", "4H", "3S"},
		{"TH", "7C", "9S", "4S", "6S"},
		{"TS", "9H", "8S", "7H", "6C", "5D", "KH", "3H"},
		{"JD", "TC", "9D", "8C"},
		{"QC", "JC", "TD", "9C", "8H"},
		{},
		{}
	};
	EXPECT_EQ(7, getMovableStackSize(0, 7, reserves, cascades));
}

TEST(getMovableStackSize, getMovableStackSize8) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"", "", "", ""
	};
	const QList<QStringList> cascades = {
		{"AC", "KC", "KS", "KH", "QC", "JH"},
		{},
		{},
		{},
		{},
		{},
		{},
		{}
	};
	EXPECT_EQ(3, getMovableStackSize(0, 1, reserves, cascades));
}

TEST(getMovableStackSize, getMovableStackSize9) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"", "", "", ""
	};
	const QList<QStringList> cascades = {
		{"KH", "QC", "JH", "TC", "9H", "8C", "7H", "6C", "5H", "4C", "3H", "2C"},
		{},
		{},
		{},
		{"5H"},
		{},
		{},
		{}
	};
	EXPECT_EQ(3, getMovableStackSize(0, 4, reserves, cascades));
}

TEST(getMovableStackSize, getMovableStackSize10) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"", "", "", ""
	};
	const QList<QStringList> cascades = {
		{"KH", "QC", "JH", "TC", "9H", "8C", "7H", "6C", "5H", "4C", "3H", "2C"},
		{},
		{},
		{},
		{"KS"},
		{},
		{},
		{}
	};
	EXPECT_EQ(0, getMovableStackSize(0, 4, reserves, cascades));
}

TEST(getMovableStackSize, getMovableStackSize11) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"", "", "", ""
	};
	const QList<QStringList> cascades = {
		{"8C"},
		{},
		{},
		{},
		{},
		{},
		{},
		{}
	};
	EXPECT_EQ(1, getMovableStackSize(0, 1, reserves, cascades));
}

TEST(getMovableStackSize, getMovableStackSize12) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"", "", "", ""
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{}
	};
	EXPECT_EQ(0, getMovableStackSize(0, 1, reserves, cascades));
}

TEST(getMovableStackSize, getMovableStackSize13) {
	const QStringList reserves = {
		"3H", "QC", "", ""
	};
	const QStringList foundations = {
		"2C", "2D", "2S", ""
	};
	const QList<QStringList> cascades = {
		{"JC", "TS", "4S", "9C", "8H"},
		{"TH", "3C", "QD", "KH", "TD", "8S", "7D", "6C"},
		{},
		{"AH", "9S", "6H", "7H", "KS", "JD", "6D"},
		{"TC", "2H", "4H", "9D", "5H", "8D"},
		{"KC", "3D", "JS", "KD", "4C", "QS"},
		{"6S", "3S", "7C", "9H", "5C", "4D"},
		{"8C", "7S", "QH", "5D", "JH", "5S"}
	};
	EXPECT_EQ(2, getMovableStackSize(0, 2, reserves, cascades));
}

TEST(getMovableStackSize, getMovableStackSize14) {
	const QStringList reserves = {
		"3H", "QC", "", ""
	};
	const QStringList foundations = {
		"2C", "2D", "2S", ""
	};
	const QList<QStringList> cascades = {
		{"JC", "TS", "4S", "9C", "8H"},
		{"TH", "3C", "QD", "KH", "TD", "8S", "7D", "6C"},
		{},
		{"AH", "9S", "6H", "7H", "KS", "JD", "6D"},
		{"TC", "2H", "4H", "9D", "5H", "8D"},
		{"KC", "3D", "JS", "KD", "4C", "QS"},
		{"6S", "3S", "7C", "9H", "5C", "4D"},
		{"8C", "7S", "QH", "5D", "JH", "5S"}
	};
	EXPECT_EQ(1, getMovableStackSize(7, 2, reserves, cascades));
}

TEST(getMovableStackSize, getMovableStackSize15) {
	const QStringList reserves = {
		"3H", "QC", "JH", "5S"
	};
	const QStringList foundations = {
		"2C", "2D", "2S", ""
	};
	const QList<QStringList> cascades = {
		{"JC", "TS", "4S", "9C", "8H"},
		{"TH", "3C", "QD", "KH", "TD", "8S", "7D", "6C"},
		{},
		{"AH", "9S", "6H", "7H", "KS", "JD", "6D"},
		{"TC", "2H", "4H", "9D", "5H", "8D"},
		{"KC", "3D", "JS", "KD", "4C", "QS"},
		{"6S", "3S", "7C", "9H", "5C", "4D"},
		{"8C", "7S", "QH", "5D"}
	};
	EXPECT_EQ(1, getMovableStackSize(7, 2, reserves, cascades));
}

TEST(getMovableStackSize, getMovableStackSize16) {
	const QStringList reserves = {
		"3H", "QC", "JH", "5S"
	};
	const QStringList foundations = {
		"2C", "2D", "2S", ""
	};
	const QList<QStringList> cascades = {
		{"JC", "TS", "4S", "9C", "8H"},
		{"TH", "3C", "QD", "KH", "TD", "8S", "7D", "6C"},
		{},
		{"AH", "9S", "6H", "7H", "KS", "JD", "6D"},
		{"TC", "2H", "4H", "9D", "5H", "8D"},
		{"KC", "3D", "JS", "KD", "4C", "QS"},
		{"6S", "3S", "7C", "9H", "5C", "4D"},
		{"8C", "7S", "QH", "5D"}
	};
	EXPECT_EQ(1, getMovableStackSize(3, 2, reserves, cascades));
}

TEST(getMovableStackSize, getMovableStackSize17) {
	const QStringList reserves = {
		"3H", "QC", "", ""
	};
	const QStringList foundations = {
		"2C", "2D", "2S", ""
	};
	const QList<QStringList> cascades = {
		{"JC", "TS", "4S", "9C", "8H"},
		{"TH", "3C", "QD", "KH", "TD", "8S", "7D", "6C"},
		{},
		{"AH", "9S", "6H", "7H", "KS", "JD", "6D"},
		{"TC", "2H", "4H", "9D", "5H", "8D"},
		{"KC", "3D", "JS", "KD", "4C", "QS"},
		{"6S", "3S", "7C", "9H", "5C", "4D"},
		{"8C", "7S", "QH", "5D", "5S", "JH"}
	};
	EXPECT_EQ(3, getMovableStackSize(1, 2, reserves, cascades));
}

TEST(getMovableStackSize, getMovableStackSize18) {
	const QStringList reserves = {
		"3H", "QC", "JH", ""
	};
	const QStringList foundations = {
		"2C", "2D", "2S", ""
	};
	const QList<QStringList> cascades = {
		{"JC", "TS", "4S", "9C", "8H"},
		{"TH", "3C", "QD", "KH", "TD", "8S", "7D", "6C"},
		{},
		{"AH", "9S", "6H", "7H", "KS", "JD", "6D"},
		{"TC", "2H", "4H", "9D", "5H", "8D"},
		{"KC", "3D", "JS", "KD", "4C", "QS"},
		{"6S", "3S", "7C", "9H", "5C", "4D"},
		{"8C", "7S", "QH", "5D", "5S"}
	};
	EXPECT_EQ(2, getMovableStackSize(1, 2, reserves, cascades));
}

TEST(getMovableStackSize, getMovableStackSize19) {
	const QStringList reserves = {
		"3H", "QC", "JH", "5S"
	};
	const QStringList foundations = {
		"2C", "2D", "2S", ""
	};
	const QList<QStringList> cascades = {
		{"JC", "TS", "4S", "9C", "8H"},
		{"TH", "3C", "QD", "KH", "TD", "8S", "7D", "6C"},
		{},
		{},
		{"TC", "2H", "4H", "9D", "5H", "8D"},
		{"KC", "3D", "JS", "KD", "4C", "QS", "6S", "3S", "7C", "9H", "5C"},
		{},
		{"8C", "7S", "QH", "5D", "AH", "9S", "6H", "7H", "KS", "JD", "6D", "3H"}
	};
	EXPECT_EQ(3, getMovableStackSize(1, 2, reserves, cascades));
}

TEST(getMovableStackSize, getMovableStackSize20) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"", "", "", ""
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{}
	};
	EXPECT_EQ(0, getMovableStackSize(0, 7, reserves, cascades));
}

TEST(getMovableStackSize, getMovableStackSize21) {
	const QStringList reserves = {
		"8D", "", "", ""
	};
	const QStringList foundations = {
		"", "", "", "AS"
	};
	const QList<QStringList> cascades = {
		{"QD", "4D", "TD", "7S", "AH", "3H"},
		{"QC", "JD", "JC", "9D", "AD", "5S"},
		{"KC", "JS", "8C", "KS", "TC", "7H", "TH"},
		{"3C", "6H", "6C", "7C", "2S", "3D", "JH"},
		{"4C", "QS", "8S", "6S", "3S", "5H"},
		{"2C", "6D", "4S", "4H", "TS"},
		{"KD", "2D", "5D", "AC", "9H", "KH"},
		{"5C", "9C", "QH", "8H", "2H", "7D"}
	};
	EXPECT_EQ(1, getMovableStackSize(5, 3, reserves, cascades));
}

TEST(getAvailMoves, getAvailMoves1) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"", "", "", ""
	};
	const QList<QStringList> cascades = {
		{"AC", "KC", "KS", "7D", "KH", "3D", "3C", "2H"},
		{"5H", "JH", "JS", "4D", "6D", "5D", "7H"},
		{"TH", "7C", "9S", "4S", "6S", "2C", "2D"},
		{"TS", "AH", "9H", "5C", "8S", "3S", "4C"},
		{"AS", "8H", "9C", "9D", "JD", "6C"},
		{"QC", "JC", "KD", "3H", "AD", "8C"},
		{"8D", "7S", "QS", "6H", "QH", "QD"},
		{"2S", "TC", "5S", "TD", "4H"}
	};
	const auto moves = getAvailMoves(reserves, foundations, cascades);
	EXPECT_EQ(3, moves.size());
	EXPECT_EQ(true, moves.contains("07"));
	EXPECT_EQ(true, moves.contains("15"));
	EXPECT_EQ(true, moves.contains("41"));
}

TEST(getAvailMoves, getAvailMoves2) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"", "", "", ""
	};
	const QList<QStringList> cascades = {
		{"AC", "KC", "KS", "7D", "KH", "3D", "3C", "2H"},
		{"5H", "JH", "JS", "4D", "6D", "5D", "7H"},
		{"TH", "7C", "9S", "4S", "6S", "2C", "2D"},
		{"TS", "AH", "9H", "5C", "8S", "3S", "4C"},
		{"AS", "8H", "9C", "9D", "6C", "JD"},
		{"QC", "JC", "KD", "3H", "8C", "AD"},
		{"8D", "7S", "QS", "6H", "QH", "QD"},
		{"2S", "TC", "5S", "4H", "TD"}
	};
	const auto moves = getAvailMoves(reserves, foundations, cascades);
	EXPECT_EQ(0, moves.size());
}

TEST(getAvailMoves, getAvailMoves3) {
	const QStringList reserves = {
		"3H", "TD", "QD", "4H"
	};
	const QStringList foundations = {
		"", "", "AH", "AS"
	};
	const QList<QStringList> cascades = {
		{"8D", "7S"},
		{"QC", "JD", "JC", "9D", "9S", "AD", "5S", "4D"},
		{"KC", "JS", "8C", "KS", "TC", "7H", "TH"},
		{"3C", "6H", "6C", "7C", "2S", "3D", "JH", "TS"},
		{"4C", "QS", "8S", "6S", "3S", "5H", "4S"},
		{"2C", "6D"},
		{"KD", "2D", "5D", "AC", "9H", "KH"},
		{"5C", "9C", "QH", "8H", "2H", "7D"}
	};
	const auto moves = getAvailMoves(reserves, foundations, cascades);
	EXPECT_EQ(1, moves.size());
	EXPECT_EQ(true, moves.contains("50"));
}

TEST(getAvailMoves, getAvailMoves4) {
	const QStringList reserves = {
		"3H", "TD", "QD", ""
	};
	const QStringList foundations = {
		"", "", "AH", "AS"
	};
	const QList<QStringList> cascades = {
		{"8D", "7S"},
		{"QC", "JD", "JC", "9D", "9S", "AD", "5S", "4D"},
		{"KC", "JS", "8C", "KS", "TC", "7H", "TH"},
		{"3C", "6H", "6C", "7C", "2S", "3D", "JH", "TS"},
		{"4C", "QS", "8S", "6S", "3S", "5H", "4S"},
		{"2C", "6D"},
		{"KD", "2D", "5D", "AC", "9H", "KH"},
		{"5C", "9C", "QH", "8H", "2H", "7D"}
	};
	const auto moves = getAvailMoves(reserves, foundations, cascades);
	EXPECT_EQ(2, moves.size());
	EXPECT_EQ(true, moves.contains("50"));
	EXPECT_EQ(true, moves.contains("15"));
}

TEST(getAvailMoves, getAvailMoves5) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"", "", "", ""
	};
	const QList<QStringList> cascades = {
		{"KH"},
		{"QS"},
		{},
		{},
		{},
		{},
		{},
		{}
	};
	const auto moves = getAvailMoves(reserves, foundations, cascades);
	EXPECT_EQ(13, moves.size());
	EXPECT_EQ(true, moves.contains("12"));
	EXPECT_EQ(true, moves.contains("02"));
	EXPECT_EQ(true, moves.contains("16"));
	EXPECT_EQ(true, moves.contains("13"));
	EXPECT_EQ(true, moves.contains("03"));
	EXPECT_EQ(true, moves.contains("14"));
	EXPECT_EQ(true, moves.contains("15"));
	EXPECT_EQ(true, moves.contains("04"));
	EXPECT_EQ(true, moves.contains("10"));
	EXPECT_EQ(true, moves.contains("05"));
	EXPECT_EQ(true, moves.contains("07"));
	EXPECT_EQ(true, moves.contains("17"));
}


TEST(getAvailMoves, getAvailMoves6) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"", "", "", ""
	};
	const QList<QStringList> cascades = {
		{"KH"},
		{},
		{},
		{},
		{},
		{},
		{},
		{"QS"}
	};
	const auto moves = getAvailMoves(reserves, foundations, cascades);
	EXPECT_EQ(13, moves.size());
	EXPECT_EQ(true, moves.contains("72"));
	EXPECT_EQ(true, moves.contains("04"));
	EXPECT_EQ(true, moves.contains("73"));
	EXPECT_EQ(true, moves.contains("01"));
	EXPECT_EQ(true, moves.contains("06"));
	EXPECT_EQ(true, moves.contains("71"));
	EXPECT_EQ(true, moves.contains("74"));
	EXPECT_EQ(true, moves.contains("75"));
	EXPECT_EQ(true, moves.contains("76"));
	EXPECT_EQ(true, moves.contains("05"));
	EXPECT_EQ(true, moves.contains("03"));
	EXPECT_EQ(true, moves.contains("02"));
	EXPECT_EQ(true, moves.contains("70"));
}

TEST(getAvailMoves, getAvailMoves7) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"", "", "", ""
	};
	const QList<QStringList> cascades = {
		{"KH"},
		{"QS"},
		{"JD"},
		{"TS"},
		{"9H"},
		{"8S"},
		{"7D"},
		{"6S"}
	};
	const auto moves = getAvailMoves(reserves, foundations, cascades);
	EXPECT_EQ(7, moves.size());
	EXPECT_EQ(true, moves.contains("10"));
	EXPECT_EQ(true, moves.contains("21"));
	EXPECT_EQ(true, moves.contains("32"));
	EXPECT_EQ(true, moves.contains("43"));
	EXPECT_EQ(true, moves.contains("54"));
	EXPECT_EQ(true, moves.contains("65"));
	EXPECT_EQ(true, moves.contains("76"));
}

TEST(getAvailMoves, getAvailMoves8) {
	const QStringList reserves = {
		"KS", "7D", "", ""
	};
	const QStringList foundations = {
		"2S", "AH", "", ""
	};
	const QList<QStringList> cascades = {
		{"8S", "5D", "7H", "KD"},
		{"QS", "JD", "TS"},
		{"9H", "5C", "AS", "QC", "2H", "6S", "QH", "JS", "TD", "9S"},
		{"9D", "AD", "JC", "4D"},
		{"QD", "7C", "6D", "6C", "3D", "TH", "9C", "8D"},
		{"6H", "5S", "4H", "3C", "2D"},
		{"KC", "4C", "3S", "JH", "TC"},
		{"8C", "8H", "7S", "KH", "5H", "4S", "3H", "2S"}
	};
	const auto moves = getAvailMoves(reserves, foundations, cascades);
	EXPECT_EQ(3, moves.size());
	EXPECT_EQ(true, moves.contains("10"));
	EXPECT_EQ(true, moves.contains("53"));
	EXPECT_EQ(true, moves.contains("42"));
}

TEST(getAvailMoves, getAvailMoves9) {
	const QStringList reserves = {
		"KS", "7D", "", ""
	};
	const QStringList foundations = {
		"2S", "AH", "", ""
	};
	const QList<QStringList> cascades = {
		{"8S", "5D", "7H", "KD"},
		{"QS", "JD", "TS"},
		{"9H", "5C", "AS", "QC", "2H", "6S", "QH", "JS", "TD", "9S"},
		{"9D", "AD", "JC", "4D"},
		{"QD", "7C", "6D", "6C", "3D", "TH", "9C", "8D"},
		{"6H", "5S", "4H", "3C", "2D"},
		{"KC", "4C", "3S", "JH", "TC"},
		{"8C", "8H", "7S", "KH", "5H", "4S", "3H", "2S"}
	};
	const auto moves = getAvailMoves(reserves, foundations, cascades);
	EXPECT_EQ(3, moves.size());
	EXPECT_EQ(true, moves.contains("10"));
	EXPECT_EQ(true, moves.contains("53"));
	EXPECT_EQ(true, moves.contains("42"));
}

TEST(getAvailMoves, getAvailMoves10) {
	const QStringList reserves = {
		"KD", "KH", "KS", ""
	};
	const QStringList foundations = {
		"2S", "4H", "4C", "4D"
	};
	const QList<QStringList> cascades = {
		{"7D", "6C"},
		{"5H", "3S", "QS", "JS", "JD", "8S", "JC", "TD", "9S", "8H", "7C", "6D"},
		{},
		{"QC", "JH", "QH", "5C", "TH", "9C", "8D", "7S", "6H", "5S"},
		{},
		{"TS", "9D"},
		{"TC", "9H", "8C", "7H", "6S", "5D", "4S"},
		{"KC", "QD"}
	};
	const auto moves = getAvailMoves(reserves, foundations, cascades);
	EXPECT_EQ(16, moves.size());
	EXPECT_EQ(true, moves.contains("65"));
	EXPECT_EQ(true, moves.contains("60"));
	EXPECT_EQ(true, moves.contains("52"));
	EXPECT_EQ(true, moves.contains("64"));
	EXPECT_EQ(true, moves.contains("17"));
	EXPECT_EQ(true, moves.contains("54"));
	EXPECT_EQ(true, moves.contains("74"));
	EXPECT_EQ(true, moves.contains("02"));
	EXPECT_EQ(true, moves.contains("31"));
	EXPECT_EQ(true, moves.contains("04"));
	EXPECT_EQ(true, moves.contains("12"));
	EXPECT_EQ(true, moves.contains("72"));
	EXPECT_EQ(true, moves.contains("32"));
	EXPECT_EQ(true, moves.contains("34"));
	EXPECT_EQ(true, moves.contains("14"));
	EXPECT_EQ(true, moves.contains("62"));
}

TEST(getAvailMoves, getAvailMoves11) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"5C", "", "", ""
	};
	const QList<QStringList> cascades = {
		{"7D", "6C"},
		{"5H", "3S", "QS", "JS", "JD", "8S", "JC", "TD", "9S", "8H", "7C", "6D"},
		{},
		{"QC", "JH", "QH", "5C", "TH", "9C", "8D", "7S", "6H", "5S"},
		{},
		{"TS", "9D"},
		{"TC", "9H", "8C", "7H", "6S", "5D", "4S"},
		{"KC", "QD"}
	};
	const auto moves = getAvailMoves(reserves, foundations, cascades, true);
	EXPECT_EQ(23, moves.size());
	EXPECT_EQ(true, moves.contains("0H"));
	EXPECT_EQ(true, moves.contains("5A"));
	EXPECT_EQ(true, moves.contains("0A"));
	EXPECT_EQ(true, moves.contains("54"));
	EXPECT_EQ(true, moves.contains("17"));
	EXPECT_EQ(true, moves.contains("02"));
	EXPECT_EQ(true, moves.contains("60"));
	EXPECT_EQ(true, moves.contains("72"));
	EXPECT_EQ(true, moves.contains("31"));
	EXPECT_EQ(true, moves.contains("32"));
	EXPECT_EQ(true, moves.contains("62"));
	EXPECT_EQ(true, moves.contains("1A"));
	EXPECT_EQ(true, moves.contains("64"));
	EXPECT_EQ(true, moves.contains("7A"));
	EXPECT_EQ(true, moves.contains("3A"));
	EXPECT_EQ(true, moves.contains("6A"));
	EXPECT_EQ(true, moves.contains("12"));
	EXPECT_EQ(true, moves.contains("34"));
	EXPECT_EQ(true, moves.contains("04"));
	EXPECT_EQ(true, moves.contains("65"));
	EXPECT_EQ(true, moves.contains("74"));
	EXPECT_EQ(true, moves.contains("52"));
	EXPECT_EQ(true, moves.contains("14"));
}

TEST(getAvailMoves, getAvailMoves12) {
	const QStringList reserves = {
		"2C", "", "", ""
	};
	const QStringList foundations = {
		"AC", "", "", ""
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{}
	};
	const auto moves = getAvailMoves(reserves, foundations, cascades, true);
	EXPECT_EQ(1, moves.size());
	EXPECT_EQ(true, moves.contains("AH"));
}

TEST(getAvailMoves, getAvailMoves13) {
	const QStringList reserves = {
		"KC", "", "", ""
	};
	const QStringList foundations = {
		"QC", "", "", ""
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{}
	};
	const auto moves = getAvailMoves(reserves, foundations, cascades, true);
	EXPECT_EQ(1, moves.size());
	EXPECT_EQ(true, moves.contains("AH"));
}

TEST(getAvailMoves, getAvailMoves14) {
	const QStringList reserves = {
		"JC", "", "", ""
	};
	const QStringList foundations = {
		"QC", "", "", ""
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{}
	};
	const auto moves = getAvailMoves(reserves, foundations, cascades, true);
	EXPECT_EQ(0, moves.size());
}

TEST(getAvailMoves, getAvailMoves15) {
	const QStringList reserves = {
		"QC", "", "", ""
	};
	const QStringList foundations = {
		"QC", "", "", ""
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{}
	};
	const auto moves = getAvailMoves(reserves, foundations, cascades, true);
	EXPECT_EQ(0, moves.size());
}

TEST(getAvailMoves, getAvailMoves16) {
	const QStringList reserves = {
		"", "KD", "", ""
	};
	const QStringList foundations = {
		"", "QD", "", ""
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{}
	};
	const auto moves = getAvailMoves(reserves, foundations, cascades, true);
	EXPECT_EQ(1, moves.size());
	EXPECT_EQ(true, moves.contains("BH"));
}

TEST(getAvailMoves, getAvailMoves17) {
	const QStringList reserves = {
		"", "", "KH", ""
	};
	const QStringList foundations = {
		"", "", "QH", ""
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{}
	};
	const auto moves = getAvailMoves(reserves, foundations, cascades, true);
	EXPECT_EQ(1, moves.size());
	EXPECT_EQ(true, moves.contains("CH"));
}

TEST(getAvailMoves, getAvailMoves18) {
	const QStringList reserves = {
		"", "", "", "KS"
	};
	const QStringList foundations = {
		"", "", "", "QS"
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{}
	};
	const auto moves = getAvailMoves(reserves, foundations, cascades, true);
	EXPECT_EQ(1, moves.size());
	EXPECT_EQ(true, moves.contains("DH"));
}

TEST(getAvailMoves, getAvailMoves19) {
	const QStringList reserves = {
		"KC", "KD", "KH", "KS"
	};
	const QStringList foundations = {
		"QC", "QD", "QH", "QS"
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{}
	};
	const auto moves = getAvailMoves(reserves, foundations, cascades, true);
	EXPECT_EQ(4, moves.size());
	EXPECT_EQ(true, moves.contains("AH"));
	EXPECT_EQ(true, moves.contains("BH"));
	EXPECT_EQ(true, moves.contains("CH"));
	EXPECT_EQ(true, moves.contains("DH"));
}

TEST(getAvailMoves, getAvailMoves20) {
	const QStringList reserves = {
		"2C", "2D", "2H", "2S"
	};
	const QStringList foundations = {
		"AC", "AD", "AH", "AS"
	};
	const QList<QStringList> cascades = {
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{}
	};
	const auto moves = getAvailMoves(reserves, foundations, cascades, true);
	EXPECT_EQ(4, moves.size());
	EXPECT_EQ(true, moves.contains("AH"));
	EXPECT_EQ(true, moves.contains("BH"));
	EXPECT_EQ(true, moves.contains("CH"));
	EXPECT_EQ(true, moves.contains("DH"));
}

TEST(getAvailMoves, getAvailMoves21) {
	const QStringList reserves = {
		"4S", "5S", "6S", "7S"
	};
	const QStringList foundations = {
		"AC", "AD", "AH", "AS"
	};
	const QList<QStringList> cascades = {
		{"2S"},
		{"KH"},
		{"KD"},
		{"8C"},
		{"9C"},
		{"TC"},
		{"JC"},
		{"JS"}
	};
	const auto moves = getAvailMoves(reserves, foundations, cascades, true);
	EXPECT_EQ(1, moves.size());
	EXPECT_EQ(true, moves.contains("0H"));
}

TEST(getAvailMoves, getAvailMoves22) {
	const QStringList reserves = {
		"4S", "5S", "6S", "7S"
	};
	const QStringList foundations = {
		"AC", "AD", "AH", "AS"
	};
	const QList<QStringList> cascades = {
		{"3S", "2S"},
		{"KH"},
		{"KD"},
		{"8C"},
		{"9C"},
		{"TC"},
		{"JC"},
		{"JS"}
	};
	const auto moves = getAvailMoves(reserves, foundations, cascades, true);
	EXPECT_EQ(1, moves.size());
	EXPECT_EQ(true, moves.contains("0H"));
}

TEST(getAvailMoves, getAvailMoves23) {
	const QStringList reserves = {
		"4S", "5S", "6S", "7S"
	};
	const QStringList foundations = {
		"AC", "AD", "AH", "AS"
	};
	const QList<QStringList> cascades = {
		{"9S"},
		{"KH"},
		{"KD"},
		{"8C"},
		{"9C"},
		{"TC"},
		{"JC"},
		{"2S"}
	};
	const auto moves = getAvailMoves(reserves, foundations, cascades, true);
	EXPECT_EQ(1, moves.size());
	EXPECT_EQ(true, moves.contains("7H"));
}

TEST(getAvailMoves, getAvailMoves24) {
	const QStringList reserves = {
		"4S", "5S", "6S", "7S"
	};
	const QStringList foundations = {
		"AC", "AD", "AH", "AS"
	};
	const QList<QStringList> cascades = {
		{"9S"},
		{"KH"},
		{"KD"},
		{"8C"},
		{"9C"},
		{"TC"},
		{"JC"},
		{"2H"}
	};
	const auto moves = getAvailMoves(reserves, foundations, cascades, true);
	EXPECT_EQ(1, moves.size());
	EXPECT_EQ(true, moves.contains("7H"));
}

TEST(getAvailMoves, getAvailMoves25) {
	const QStringList reserves = {
		"4S", "5S", "6S", "7S"
	};
	const QStringList foundations = {
		"AC", "7D", "AH", "AS"
	};
	const QList<QStringList> cascades = {
		{"9S"},
		{"KH"},
		{"KD"},
		{"8C"},
		{"9C"},
		{"TC"},
		{"JC"},
		{"8D"}
	};
	const auto moves = getAvailMoves(reserves, foundations, cascades, true);
	EXPECT_EQ(3, moves.size());
	EXPECT_EQ(true, moves.contains("74"));
	EXPECT_EQ(true, moves.contains("70"));
	EXPECT_EQ(true, moves.contains("7H"));
}

TEST(isGameWon, isGameWon1) {
	const QStringList foundations = {
		"KC", "KD", "KH", "KS"
	};
	EXPECT_EQ(true, isGameWon(foundations));
}

TEST(isGameWon, isGameWon2) {
	const QStringList foundations = {
		"QC", "KD", "KH", "KS"
	};
	EXPECT_EQ(false, isGameWon(foundations));
}

TEST(isGameWon, isGameWon3) {
	const QStringList foundations = {
		"AC", "AD", "AH", "KS"
	};
	EXPECT_EQ(false, isGameWon(foundations));
}

TEST(isGameWon, isGameWon4) {
	const QStringList foundations = {
		"", "KD", "KH", "KS"
	};
	EXPECT_EQ(false, isGameWon(foundations));
}

TEST(isGameWon, isGameWon5) {
	const QStringList foundations = {
		"", "", "", ""
	};
	EXPECT_EQ(false, isGameWon(foundations));
}

TEST(isGameWon, isGameWon6) {
	const QStringList foundations;
	EXPECT_EQ(false, isGameWon(foundations));
}

TEST(validate, validate1) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"KC", "KD", "KH", "KS"
	};
	const QList<QStringList> cascades;
	QString error;
	bool rc = validate(reserves, foundations, cascades, error);
	EXPECT_EQ(true, rc);
}

TEST(validate, validate2) {
	const QStringList reserves = {
		"KS", "", "", ""
	};
	const QStringList foundations = {
		"KC", "KD", "KH", "QS"
	};
	const QList<QStringList> cascades;
	QString error;
	bool rc = validate(reserves, foundations, cascades, error);
	EXPECT_EQ(true, rc);
}

TEST(validate, validate3) {
	const QStringList reserves = {
		"KC", "KD", "KH", "KS"
	};
	const QStringList foundations = {
		"QC", "QD", "QH", "QS"
	};
	const QList<QStringList> cascades;
	QString error;
	bool rc = validate(reserves, foundations, cascades, error);
	EXPECT_EQ(true, rc);
}

TEST(validate, validate4) {
	const QStringList reserves = {
		"KS", "QS", "JS", "TS"
	};
	const QStringList foundations = {
		"KC", "KD", "KH", "9S"
	};
	const QList<QStringList> cascades;
	QString error;
	bool rc = validate(reserves, foundations, cascades, error);
	EXPECT_EQ(true, rc);
}

TEST(validate, validate5) {
	const QStringList reserves = {
		"KS", "QS", "JS", "TS"
	};
	const QStringList foundations = {
		"KC", "KD", "KH", "8S"
	};
	const QList<QStringList> cascades;
	QString error;
	bool rc = validate(reserves, foundations, cascades, error);
	EXPECT_EQ(false, rc);
	EXPECT_EQ("9S", error);
}

TEST(validate, validate6) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"KC", "KD", "KH", "8S"
	};
	const QList<QStringList> cascades;
	QString error;
	bool rc = validate(reserves, foundations, cascades, error);
	EXPECT_EQ(false, rc);
	EXPECT_EQ("9S JS KS QS TS", error);
}

TEST(validate, validate7) {
	const QStringList reserves = {
		"", "", "", ""
	};
	const QStringList foundations = {
		"", "", "", ""
	};
	const QList<QStringList> cascades = {
		{"AH", "8D", "3S", "2S", "6D", "7S", "5C"},
		{"KD", "9H", "KS", "5H", "TS", "JD", "QH"},
		{"8H", "4C", "TH", "7D", "9C", "8C", "QC"},
		{"7C", "3C", "3H", "JC", "JS", "QS", "TD"},
		{"9S", "6H", "AS", "AD", "4H", "6C"},
		{"2D", "2C", "3D", "KC", "QD", "KH"},
		{"4D", "AC", "4S", "JH", "2H", "TC"},
		{"5S", "7H", "6S", "5D", "8S", "9D"}
	};
	QString error;
	bool rc = validate(reserves, foundations, cascades, error);
	EXPECT_EQ("", error);
	EXPECT_EQ(true, rc);
}

int main(int argc, char *argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
