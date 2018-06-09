// include
#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Main.h"

// 順位データ
using rankData = std::pair<uint64, String>;

// ランキング
class Ranking :public MyApp::Scene
{
private:
	std::vector<rankData>rankingData;
	HighlightingShape<Rect>choice1Rect, choice2Rect, choice3Rect, choice4Rect;
	HighlightingShape<Triangle>goUpTrig, goDownTrig;
	Font titleFont, choiceFont, rankFont;
	String diffStr[4] = { U"かんたん",U"ふつう",U"むずかしい",U"いいえ" };
	int diffNum, stageNum, rankingBeginNum;

public:
	Ranking(const InitData& init);
	void update() override;
	void draw() const override;
	void reload(bool newWrite);
};
