// include
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Game.h"
#include "Select.h"

// ゲーム画面 初期化
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
}

// ゲーム画面 更新
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
}

// ゲーム画面 描画
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
	infoRect.draw(Color(255, 255, 255, 120));
	infoRect.drawFrame(2);
	timeRect.draw(Color(64, 64, 64, 120));
	timeRect.drawFrame(2, Color(16, 16, 16));
	lifeRect.draw(Color(255, 132, 143, 120));
	lifeRect.drawFrame(2, Color(255, 132, 143));
	statsFont(U"ステージ" + Format(getData().selectedStageNum)).draw(495, 15, Palette::Black);
	switch (getData().selectedDiffNum)
	{
	case 0:
		statsFont(U"かんたん").draw(495, 66, Palette::Yellowgreen);
		break;
	case 1:
		statsFont(U"ふつう").draw(495, 66, Palette::Yellow);
		break;
	case 2:
		statsFont(U"むずかしい").draw(495, 66, Palette::Orange);
		break;
	case 3:
		statsFont(U"いいえ").draw(495, 66, Palette::Red);
		break;
	}
	statsFont(U"経過時間").draw(495, 132, Color(200, 200, 200));
	statsFont(Format((mainTime.nowTime - mainTime.startTime) / 1000.)).draw(495, 183, Color(200, 200, 200));
	statsFont(U"残り体力").draw(495, 249, Palette::Hotpink);
	RoundRect(495, 300, 210, 35, 2).draw(Palette::Black);
	RoundRect(495, 300, 210 * playerHP / maxHP, 35, 2).draw((playerHP >= 100 ? Palette::Lightgreen : (playerHP >= 50 ? Palette::Yellow : Palette::Red)));
}
