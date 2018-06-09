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
	Font titleFont, rankFont;
	String diffStr[4] = { U"かんたん",U"ふつう",U"むずかしい",U"いいえ" };
	int diffNum, stageNum;

public:
	Ranking(const InitData& init);
	void update() override;
	void draw() const override;
};
