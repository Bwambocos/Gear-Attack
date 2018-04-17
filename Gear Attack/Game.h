// include
#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Main.h"

// const
const int fieldSize = 392;
const int cellSize = 28;
const int maxHP = 200;

// ÉQÅ[ÉÄâÊñ 
class Game :public MyApp::Scene
{
private:
	Texture gameField;
	Grid<int>fieldData;
	Rect infoRect, lifeRect, timeRect;
	Font statsFont;
	uint64 nowTime, startTime;
	int playerHP;

public:
	Game(const InitData& init);
	void update() override;
	void draw() const override;
};
