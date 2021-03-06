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
	bgm = Audio(U"data//Game//bgm//bgm" + Format(getData().bgmNum + 1) + U".mp3");
	gameClearSound = Audio(U"data//Game//gameClearSound.wav");
	gameOverSound = Audio(U"data//Game//gameOverSound.wav");
	getStarSound = Audio(U"data//Game//getStarSound.wav");
	enemySound = Audio(U"data//Game//enemySound.wav");
	attackedSound = Audio(U"data//Game//attackedSound.wav");
	fieldData = Grid<int>(fieldSize / cellSize, fieldSize / cellSize);
	fieldReader = TextReader(U"data/Game/s" + Format(getData().selectedStageNum) + U".txt");
	String tmp;
	fieldReader.readLine(tmp);
	playerX = Parse<int>(tmp.substr(0, tmp.indexOf(' ')).c_str()) - 1;
	playerY = Parse<int>(tmp.substr(tmp.indexOf(' ') + 1).c_str()) - 1;
	checkPointNum = 0;
	for (auto x : step(fieldSize / cellSize))
	{
		char32 ctmp;
		for (auto y : step(fieldSize / cellSize))
		{
			fieldReader.readChar(ctmp);
			fieldData[y][x] = ctmp - '0';
			if (fieldData[y][x] == 2) ++checkPointNum;
		}
		fieldReader.readChar(ctmp);
	}
	infoRect = Rect(490, 10, 220, 107);
	timeRect = Rect(490, 127, 220, 107);
	lifeRect = Rect(490, 244, 220, 96);
	infoMessageRect = RoundRect(25, 25, Scene::Width() - 50, Scene::Height() - 50, 10);
	infoMessageFont = Font(72, U"data//fontR.ttc", FontStyle::Bold);
	statsFont = Font(36, U"data//fontR.ttc", FontStyle::Bold);
	infoMessage = U"ゲームスタート！";
	clearTime = 0;
	mainTime.nowTime = mainTime.startTime = Time::GetMillisec();
	stageNum = getData().selectedStageNum;
	diffNum = getData().selectedDiffNum;
	infoMessageFlag = true;
	Game::initPlayer();
	Game::initEnemys();
	getData().prevScene = U"Game";
	if (getData().bgmFlag)
	{
		bgm.setLoop(true);
		bgm.play();
	}
}

// ゲーム画面 更新
void Game::update()
{
	mainTime.nowTime = Time::GetMillisec();
	if (infoMessageFlag)
	{
		if (mainTime.nowTime - mainTime.startTime >= drawInfoMessageMilliSec)
		{
			infoMessageFlag = false;
			if (checkPointNum == 0)
			{
				if (getData().bgmFlag) bgm.stop();
				getData().gameScore = playerHP * calcScoreConst / (clearTime / 100);
				getData().writeRankingFlag = true;
				changeScene(U"Ranking");
			}
			if (playerHP == 0)
			{
				if (getData().bgmFlag) bgm.stop();
				getData().writeRankingFlag = false;
				changeScene(U"Ranking");
			}
			mainTime.nowTime = mainTime.startTime = Time::GetMillisec();
		}
	}
	else
	{
		if (checkPointNum == 0)
		{
			infoMessageFlag = true;
			infoMessage = U"ステージクリア！";
			clearTime = mainTime.nowTime - mainTime.startTime;
			mainTime.nowTime = mainTime.startTime = Time::GetMillisec();
			if (getData().seFlag) gameClearSound.play();
		}
		if (playerHP == 0)
		{
			infoMessageFlag = true;
			infoMessage = U"ゲームオーバー！";
			mainTime.nowTime = mainTime.startTime = Time::GetMillisec();
			if (getData().seFlag) gameOverSound.play();
		}
		Game::updatePlayer();
		Game::updateEnemys();
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
	infoRect.draw(getData().schemeColor2);
	infoRect.drawFrame(2, getData().schemeColor3);
	timeRect.draw(getData().schemeColor2);
	timeRect.drawFrame(2, getData().schemeColor3);
	lifeRect.draw(getData().schemeColor2);
	lifeRect.drawFrame(2, getData().schemeColor3);
	statsFont(U"ステージ" + Format(stageNum)).draw(495, 15, getData().stringColor);
	switch (diffNum)
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
		statsFont(U"不可能").draw(495, 66, Palette::Red);
		break;
	}
	statsFont(U"経過時間").draw(495, 132, getData().stringColor);
	statsFont((!infoMessageFlag ? Format((mainTime.nowTime - mainTime.startTime) / 1000.) : Format(clearTime / 1000.))).draw(495, 183, getData().stringColor);
	statsFont(U"残り体力").draw(495, 249, getData().stringColor);
	RoundRect(495, 300, 210, 35, 2).draw(getData().schemeColor3);
	RoundRect(495, 300, 210 * playerHP / maxHP, 35, 2).draw((playerHP >= maxHP / 2 ? Palette::Lightgreen : (playerHP >= maxHP / 4 ? Palette::Yellow : Palette::Red)));
	Game::drawPlayer();
	Game::drawEnemys();
	if (infoMessageFlag)
	{
		infoMessageRect.draw(Color(getData().schemeColor3, 150));
		infoMessageRect.drawFrame(2, 3, (checkPointNum == 0 ? Palette::Yellow : Palette::Darkgray));
		infoMessageFont(infoMessage).drawAt(infoMessageRect.center(), getData().stringColor);
	}
}

// プレーヤー 初期化
void Game::initPlayer()
{
	playerImg = Texture(U"data/Game/playerImg.png");
	playerHP = maxHP;
	playerMoveFlag = false;
	playerXMoveDistance = playerYMoveDistance = 0;
	getData().gameScore = score = 0;
}

// プレーヤー 更新
void Game::updatePlayer()
{
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
			if (fieldData[(int)playerX][(int)playerY] == 2)
			{
				playerHP += gettingPlayerHP[diffNum];
				playerHP = Min(playerHP, maxHP);
				fieldData[(int)playerX][(int)playerY] = 0;
				--checkPointNum;
				if (getData().seFlag) getStarSound.play();
			}
		}
		else
		{
			auto dis = (double)cellSize * (playerTime.nowTime - playerTime.startTime) / playerMoveMilliSec;
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

	auto playerRect = Rect(44 + cellSize * playerX + playerXMoveDistance, 44 + cellSize * playerY + playerYMoveDistance, cellSize, cellSize);
	if ((enemys[0].moveFlag == -1 && playerRect.intersects(enemys[0].attackLine)) || (enemys[1].moveFlag == -1 && playerRect.intersects(enemys[1].attackLine)))
	{
		playerHP -= attackingEnemyHP[diffNum] / 60;
		playerHP = Max(playerHP, 0);
		if (getData().seFlag) attackedSound.play();
	}
}

// プレーヤー 描画
void Game::drawPlayer() const
{
	playerImg.draw(44 + cellSize * playerX + playerXMoveDistance, 44 + cellSize * playerY + playerYMoveDistance);
}

// 敵 初期化
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

// 敵 更新
void Game::updateEnemys()
{
	for (auto i : step(2))
	{
		if (enemys[i].moveFlag == -1)
		{
			enemys[i].stayTime.nowTime = Time::GetMillisec();
			double ratio = Min((double)(enemys[i].stayTime.nowTime - enemys[i].stayTime.startTime) / (double)enemyStayMilliSec[diffNum], 1.);
			if (i == 0)
			{
				if (enemys[i].attackFlag == 0)
				{
					enemys[i].attackLine = Line(44 + enemys[0].px * cellSize + enemys[0].moveDistanceX + enemyImg.width() / 2., 10 + enemyImg.height() / 2., 44 + enemys[0].px * cellSize + enemys[0].moveDistanceX + enemyImg.width() / 2., 10 + enemyImg.height() / 2. + (gameFieldImg.width() - 54) * ratio);
				}
				else
				{
					enemys[i].attackLine = Line(44 + enemys[0].px * cellSize + enemys[0].moveDistanceX + enemyImg.width() / 2., 10 + enemyImg.height() / 2. + (gameFieldImg.width() - 54) * (1 - ratio), 44 + enemys[0].px * cellSize + enemys[0].moveDistanceX + enemyImg.width() / 2., 10 + enemyImg.height() / 2. + (gameFieldImg.width() - 54));
				}
			}
			if (i == 1)
			{
				if (enemys[i].attackFlag == 0)
				{
					enemys[i].attackLine = Line(10 + enemyImg.width() / 2., 44 + enemys[1].py * cellSize + enemys[1].moveDistanceY + enemyImg.height() / 2., 10 + enemyImg.width() / 2. + (gameFieldImg.height() - 54) * ratio, 44 + enemys[1].py * cellSize + enemys[1].moveDistanceY + enemyImg.height() / 2.);
				}
				else
				{
					enemys[i].attackLine = Line(10 + enemyImg.width() / 2. + (gameFieldImg.height() - 54) * (1 - ratio), 44 + enemys[1].py * cellSize + enemys[1].moveDistanceY + enemyImg.height() / 2., 10 + enemyImg.width() / 2. + (gameFieldImg.height() - 54), 44 + enemys[1].py * cellSize + enemys[1].moveDistanceY + enemyImg.height() / 2.);
				}
			}
			if (enemys[i].stayTime.nowTime - enemys[i].stayTime.startTime >= enemyStayMilliSec[diffNum] * 3 / 2
				&& ((i == 0 && enemys[i].px != playerX) || (i == 1 && enemys[i].py != playerY)))
			{
				enemys[i].tox = (int)playerX;
				enemys[i].toy = (int)playerY;
				if (i == 0) enemys[0].moveFlag = (enemys[0].px < enemys[0].tox ? 4 : 3);
				else enemys[1].moveFlag = (enemys[1].py < enemys[1].toy ? 2 : 1);
				enemys[i].moveTime.nowTime = enemys[i].moveTime.startTime = Time::GetMillisec();
			}
			else if (getData().seFlag) enemySound.play();
		}
		else
		{
			enemys[i].moveTime.nowTime = Time::GetMillisec();
			if ((i == 0 && enemys[i].moveTime.nowTime - enemys[i].moveTime.startTime >= abs(enemys[i].tox - enemys[i].px) * enemyMoveMilliSec[diffNum])
				|| (i == 1 && enemys[i].moveTime.nowTime - enemys[i].moveTime.startTime >= abs(enemys[i].toy - enemys[i].py) * enemyMoveMilliSec[diffNum]))
			{
				enemys[i].px = enemys[i].tox;
				enemys[i].py = enemys[i].toy;
				enemys[i].moveFlag = -1;
				enemys[i].moveDistanceX = enemys[i].moveDistanceY = 0;
				enemys[i].stayTime.nowTime = enemys[i].stayTime.startTime = Time::GetMillisec();
				enemys[0].attackLine = Line(44 + enemys[0].px * cellSize + enemys[0].moveDistanceX + enemyImg.width() / 2., 10 + enemyImg.height() / 2., 44 + enemys[0].px * cellSize + enemys[0].moveDistanceX + enemyImg.width() / 2., 10 + enemyImg.height() / 2.);
				enemys[1].attackLine = Line(10 + enemyImg.width() / 2., 44 + enemys[1].py * cellSize + enemys[1].moveDistanceY + enemyImg.height() / 2., 10 + enemyImg.width() / 2., 44 + enemys[1].py * cellSize + enemys[1].moveDistanceY + enemyImg.height() / 2.);
				enemys[0].attackFlag = RandomBool();
				enemys[1].attackFlag = RandomBool();
			}
			else
			{
				auto dis = (double)cellSize * (enemys[i].moveTime.nowTime - enemys[i].moveTime.startTime) / enemyMoveMilliSec[diffNum];
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

// 敵 描画
void Game::drawEnemys() const
{
	if (!infoMessageFlag)
	{
		if (enemys[0].moveFlag == -1)
		{
			enemys[0].attackLine.draw(8, Palette::Deepskyblue);
			enemys[0].attackLine.draw(5, Palette::Lightskyblue);
		}
		if (enemys[1].moveFlag == -1)
		{
			enemys[1].attackLine.draw(8, Palette::Deepskyblue);
			enemys[1].attackLine.draw(5, Palette::Lightskyblue);
		}
	}
	enemyImg.draw(44 + enemys[0].px * cellSize + enemys[0].moveDistanceX, 10);
	enemyImg.draw(44 + enemys[0].px * cellSize + enemys[0].moveDistanceX, gameFieldImg.width() - 44);
	enemyImg.draw(10, 44 + enemys[1].py * cellSize + enemys[1].moveDistanceY);
	enemyImg.draw(gameFieldImg.height() - 44, 44 + enemys[1].py * cellSize + enemys[1].moveDistanceY);
}
