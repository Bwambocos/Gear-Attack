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
const uint64 playerMoveMilliSec = 100;
const uint64 enemyStayMilliSec[4] = { 1000,750,500,300 };
const uint64 enemyMoveMilliSec[4] = { 500,450,400,300 };

// ç\ë¢ëÃ
struct doubleTime
{
	uint64 nowTime, startTime;
};
struct enemyData
{
	double moveDistanceX, moveDistanceY;
	int px, py, tox, toy, moveFlag;
	doubleTime stayTime, moveTime;
};

// ÉQÅ[ÉÄâÊñ 
class Game :public MyApp::Scene
{
private:
	Texture gameFieldImg, fieldCellImg[fieldCellKinds], playerImg, enemyImg;
	Grid<int>fieldData;
	TextReader fieldReader;
	Rect infoRect, lifeRect, timeRect;
	Font statsFont;
	doubleTime mainTime, playerTime;
	enemyData enemys[2];
	int stageNum, diffNum, playerHP, playerMoveFlag;
	double playerX, playerY, playerXMoveDistance, playerYMoveDistance;

public:
	Game(const InitData& init);
	void update() override;
	void draw() const override;
	void initEnemys();
	void updateEnemys();
	void drawEnemys() const;
};
