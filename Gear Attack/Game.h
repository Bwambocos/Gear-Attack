// include
#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Main.h"

// const
const int fieldSize = 392;
const int cellSize = 28;
const int maxHP = 200;
const int fieldCellKinds = 3;
const double playerMoveMilliSec = 100;

// ç\ë¢ëÃ
struct doubleTime
{
	uint64 nowTime, startTime;
};

// ÉQÅ[ÉÄâÊñ 
class Game :public MyApp::Scene
{
private:
	Texture gameFieldImg, fieldCellImg[fieldCellKinds], playerImg;
	Grid<int>fieldData;
	TextReader fieldReader;
	Rect infoRect, lifeRect, timeRect;
	Font statsFont;
	doubleTime mainTime, playerTime;
	int playerHP, playerMoveFlag;
	double playerX, playerY, playerXMoveDistance, playerYMoveDistance;

public:
	Game(const InitData& init);
	void update() override;
	void draw() const override;
};
