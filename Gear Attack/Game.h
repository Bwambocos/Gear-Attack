// include
#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Main.h"

// const
const int fieldSize = 392;
const int cellSize = 28;
const int maxHP = 1000;
const int fieldCellKinds = 3;
const int gettingPlayerHP[4] = { 333,250,200,100 };
const int attackingEnemyHP[4] = { 80,160,240,400 };
const uint64 drawInfoMessageMilliSec = 1500;
const uint64 playerMoveMilliSec = 100;
const uint64 enemyStayMilliSec[4] = { 1000,750,500,300 };
const uint64 enemyMoveMilliSec[4] = { 500,450,400,300 };

// 構造体
struct doubleTime
{
	uint64 nowTime, startTime;
};
struct enemyData
{
	Line attackLine;
	double moveDistanceX, moveDistanceY;
	int px, py, tox, toy, moveFlag;
	doubleTime stayTime, moveTime;
};

// ゲーム画面
class Game :public MyApp::Scene
{
private:
	Texture gameFieldImg, fieldCellImg[fieldCellKinds], playerImg, enemyImg;
	Grid<int>fieldData;
	TextReader fieldReader;
	Rect infoRect, lifeRect, timeRect;
	RoundRect infoMessageRect;
	Font infoMessageFont, statsFont;
	doubleTime mainTime, playerTime;
	enemyData enemys[2];
	String infoMessage;
	uint64 score;
	int stageNum, diffNum, checkPointNum, playerMoveFlag, playerHP;
	double playerX, playerY, playerXMoveDistance, playerYMoveDistance;
	bool infoMessageFlag;

public:
	Game(const InitData& init);
	void update() override;
	void draw() const override;
	void initPlayer();
	void updatePlayer();
	void drawPlayer() const;
	void initEnemys();
	void updateEnemys();
	void drawEnemys() const;
};
