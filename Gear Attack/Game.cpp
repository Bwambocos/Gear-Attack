// include
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Game.h"
#include "Select.h"

// ÉQÅ[ÉÄâÊñ  èâä˙âª
Game::Game(const InitData& init) :IScene(init)
{
	gameFieldImg = Texture(U"data/Game/gameField.png");
	for (auto i : step(fieldCellKinds)) fieldCellImg[i] = Texture(U"data/Game/cell" + Format(i + 1) + U".png");
	fieldData = Grid<int>(fieldSize / cellSize, fieldSize / cellSize);
	fieldReader = TextReader(U"data/Game/s" + Format(getData().selectedStageNum) + U".txt");
	String tmp;
	fieldReader.readLine(tmp);
	playerX = Parse<int>(tmp.substr(0, tmp.indexOf(' ')).c_str()) - 1;
	playerY = Parse<int>(tmp.substr(tmp.indexOf(' ') + 1).c_str()) - 1;
	for (auto x : step(fieldSize / cellSize))
	{
		char32 tmp;
		for (auto y : step(fieldSize / cellSize))
		{
			fieldReader.readChar(tmp);
			fieldData[y][x] = tmp - '0';
		}
		fieldReader.readChar(tmp);
	}
	playerImg = Texture(U"data/Game/playerImg.png");
	infoRect = Rect(490, 10, 220, 107);
	timeRect = Rect(490, 127, 220, 107);
	lifeRect = Rect(490, 244, 220, 96);
	statsFont = Font(36, Typeface::Bold);
	mainTime.nowTime = mainTime.startTime = Time::GetMillisec();
	playerHP = maxHP;
	playerMoveFlag = false;
	playerXMoveDistance = playerYMoveDistance = 0;
	stageNum = getData().selectedStageNum;
	diffNum = getData().selectedDiffNum;
	Game::initEnemys();
}

// ÉQÅ[ÉÄâÊñ  çXêV
void Game::update()
{
	mainTime.nowTime = Time::GetMillisec();
	if (playerMoveFlag == -1)
	{
		if (playerY > 0 && (KeyW.pressed() || KeyUp.pressed()))
		{
			if (fieldData[(int)playerX][(int)playerY - 1] != 1) playerMoveFlag = 1;
		}
		if (playerY < fieldSize / cellSize - 1 && (KeyS.pressed() || KeyDown.pressed()))
		{
			if (fieldData[(int)playerX][(int)playerY + 1] != 1) playerMoveFlag = 2;
		}
		if (playerX > 0 && (KeyA.pressed() || KeyLeft.pressed()))
		{
			if (fieldData[(int)playerX - 1][(int)playerY] != 1) playerMoveFlag = 3;
		}
		if (playerX < fieldSize / cellSize - 1 && (KeyD.pressed() || KeyRight.pressed()))
		{
			if (fieldData[(int)playerX + 1][(int)playerY] != 1) playerMoveFlag = 4;
		}
		if (playerMoveFlag != -1) playerTime.nowTime = playerTime.startTime = Time::GetMillisec();
	}
	else
	{
		playerTime.nowTime = Time::GetMillisec();
		if (playerTime.nowTime - playerTime.startTime > playerMoveMilliSec)
		{
			switch (playerMoveFlag)
			{
			case 1:
				--playerY;
				break;
			case 2:
				++playerY;
				break;
			case 3:
				--playerX;
				break;
			case 4:
				++playerX;
				break;
			}
			playerMoveFlag = -1;
			playerXMoveDistance = playerYMoveDistance = 0;
		}
		else
		{
			auto dis = (double)cellSize*(playerTime.nowTime - playerTime.startTime) / playerMoveMilliSec;
			switch (playerMoveFlag)
			{
			case 1:
				playerYMoveDistance = -dis;
				break;
			case 2:
				playerYMoveDistance = dis;
				break;
			case 3:
				playerXMoveDistance = -dis;
				break;
			case 4:
				playerXMoveDistance = dis;
				break;
			}
		}
	}
	Game::updateEnemys();
}

// ÉQÅ[ÉÄâÊñ  ï`âÊ
void Game::draw() const
{
	gameFieldImg.draw(0, 0);
	for (auto x : step(fieldSize / cellSize))
	{
		for (auto y : step(fieldSize / cellSize))
		{
			fieldCellImg[fieldData[x][y]].draw(44 + x * cellSize, 44 + y * cellSize);
		}
	}
	playerImg.draw(44 + cellSize * playerX + playerXMoveDistance, 44 + cellSize * playerY + playerYMoveDistance);
	Game::drawEnemys();
	infoRect.draw(Color(255, 255, 255, 120));
	infoRect.drawFrame(2);
	timeRect.draw(Color(64, 64, 64, 120));
	timeRect.drawFrame(2, Color(16, 16, 16));
	lifeRect.draw(Color(255, 132, 143, 120));
	lifeRect.drawFrame(2, Color(255, 132, 143));
	statsFont(U"ÉXÉeÅ[ÉW" + Format(stageNum)).draw(495, 15, Palette::Black);
	switch (diffNum)
	{
	case 0:
		statsFont(U"Ç©ÇÒÇΩÇÒ").draw(495, 66, Palette::Yellowgreen);
		break;
	case 1:
		statsFont(U"Ç”Ç¬Ç§").draw(495, 66, Palette::Yellow);
		break;
	case 2:
		statsFont(U"ÇﬁÇ∏Ç©ÇµÇ¢").draw(495, 66, Palette::Orange);
		break;
	case 3:
		statsFont(U"Ç¢Ç¢Ç¶").draw(495, 66, Palette::Red);
		break;
	}
	statsFont(U"åoâﬂéûä‘").draw(495, 132, Color(200, 200, 200));
	statsFont(Format((mainTime.nowTime - mainTime.startTime) / 1000.)).draw(495, 183, Color(200, 200, 200));
	statsFont(U"écÇËëÃóÕ").draw(495, 249, Palette::Hotpink);
	RoundRect(495, 300, 210, 35, 2).draw(Palette::Black);
	RoundRect(495, 300, 210 * playerHP / maxHP, 35, 2).draw((playerHP >= 100 ? Palette::Lightgreen : (playerHP >= 50 ? Palette::Yellow : Palette::Red)));
}

// ìG èâä˙âª
void Game::initEnemys()
{
	enemyImg = Texture(U"data/Game/enemyImg.png");
	enemys[0].px = fieldSize / cellSize / 2;
	enemys[0].py = 0;
	enemys[1].px = 0;
	enemys[1].py = fieldSize / cellSize / 2;
	enemys[0].moveDistanceX = enemys[0].moveDistanceY = 0;
	enemys[1].moveDistanceX = enemys[1].moveDistanceY = 0;
	enemys[0].moveTime.nowTime = enemys[0].moveTime.startTime = Time::GetMillisec();
	enemys[0].stayTime.nowTime = enemys[0].stayTime.startTime = Time::GetMillisec();
	enemys[1].moveTime.nowTime = enemys[1].moveTime.startTime = Time::GetMillisec();
	enemys[1].stayTime.nowTime = enemys[1].stayTime.startTime = Time::GetMillisec();
	enemys[0].moveFlag = enemys[1].moveFlag = -1;
}

// ìG çXêV
void Game::updateEnemys()
{
	for (auto i : step(2))
	{
		if (enemys[i].moveFlag == -1)
		{
			enemys[i].stayTime.nowTime = Time::GetMillisec();
			if (enemys[i].stayTime.nowTime - enemys[i].stayTime.startTime >= enemyStayMilliSec[diffNum])
			{
				enemys[i].tox = playerX;
				enemys[i].toy = playerY;
				if (i == 0) enemys[0].moveFlag = (enemys[0].px < enemys[0].tox ? 4 : 3);
				else enemys[1].moveFlag = (enemys[1].py < enemys[1].toy ? 2 : 1);
				enemys[i].moveTime.nowTime = enemys[i].moveTime.startTime = Time::GetMillisec();
			}
		}
		else
		{
			enemys[i].moveTime.nowTime = Time::GetMillisec();
			if ((i == 0 && enemys[i].moveTime.nowTime - enemys[i].moveTime.startTime >= abs(enemys[i].tox - enemys[i].px)*enemyMoveMilliSec[diffNum])
				|| (i == 1 && enemys[i].moveTime.nowTime - enemys[i].moveTime.startTime >= abs(enemys[i].toy - enemys[i].py)*enemyMoveMilliSec[diffNum]))
			{
				enemys[i].px = enemys[i].tox;
				enemys[i].py = enemys[i].toy;
				enemys[i].moveFlag = -1;
				enemys[i].moveDistanceX = enemys[i].moveDistanceY = 0;
				enemys[i].stayTime.nowTime = enemys[i].stayTime.startTime = Time::GetMillisec();
			}
			else
			{
				auto dis = (double)cellSize*(enemys[i].moveTime.nowTime - enemys[i].moveTime.startTime) / enemyMoveMilliSec[diffNum];
				switch (enemys[i].moveFlag)
				{
				case 1:
					enemys[i].moveDistanceY = -dis;
					break;
				case 2:
					enemys[i].moveDistanceY = dis;
					break;
				case 3:
					enemys[i].moveDistanceX = -dis;
					break;
				case 4:
					enemys[i].moveDistanceX = dis;
					break;
				}
			}
		}
	}
}

// ìG ï`âÊ
void Game::drawEnemys() const
{
	enemyImg.draw(44 + enemys[0].px*cellSize + enemys[0].moveDistanceX, 10);
	enemyImg.draw(44 + enemys[0].px*cellSize + enemys[0].moveDistanceX, gameFieldImg.width() - 44);
	enemyImg.draw(10, 44 + enemys[1].py*cellSize + enemys[1].moveDistanceY);
	enemyImg.draw(gameFieldImg.height() - 44, 44 + enemys[1].py*cellSize + enemys[1].moveDistanceY);
}
