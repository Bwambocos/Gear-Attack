// include
#pragma once
#include "Main.h"

// const
const int fieldSize = 392;
const int cellSize = 28;
const int maxHP = 1000;
const int fieldCellKinds = 3;
const int gettingPlayerHP[4] = { 250,200,100,50 };
const int attackingEnemyHP[4] = { 160,240,300,500 };
const uint64 drawInfoMessageMilliSec = 1500;
const uint64 playerMoveMilliSec = 100;
const uint64 enemyStayMilliSec[4] = { 1000,750,500,300 };
const uint64 enemyMoveMilliSec[4] = { 500,450,400,300 };
const uint64 calcScoreConst = 10000;

// ç\ë¢ëÃ
struct doubleTime
{
	uint64 nowTime, startTime;
};
struct enemyData
{
	Line attackLine;
	doubleTime stayTime, moveTime;
	double moveDistanceX, moveDistanceY;
	int px, py, tox, toy, moveFlag, attackFlag;
};

// ÉQÅ[ÉÄâÊñ 
class Game :public MyApp::Scene
{
private:
	Texture gameFieldImg, fieldCellImg[fieldCellKinds], playerImg, enemyImg;
	Audio bgm, gameClearSound, gameOverSound, getStarSound, enemySound, attackedSound;
	Grid<int>fieldData;
	TextReader fieldReader;
	Rect infoRect, lifeRect, timeRect;
	RoundRect infoMessageRect;
	Font infoMessageFont, statsFont;
	String infoMessage;
	uint64 score, clearTime;
	doubleTime mainTime, playerTime;
	enemyData enemys[2];
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
