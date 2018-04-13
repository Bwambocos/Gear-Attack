// include
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Game.h"
#include "Select.h"

// ゲーム画面 初期化
Game::Game(const InitData& init) :IScene(init)
{
	gameField = Texture(U"data/Game/gameField.png");
	fieldData = Grid<int>(fieldSize / cellSize, fieldSize / cellSize);
	infoRect = Rect(490, 10, 220, 107);
	lifeRect = Rect(490, 127, 220, 96);
	statsFont = Font(36, Typeface::Bold);
	playerHP = maxHP;
}

// ゲーム画面 更新
void Game::update()
{
	if (KeyZ.pressed()) playerHP -= 1;
}

// ゲーム画面 描画
void Game::draw() const
{
	gameField.draw(0, 0);
	infoRect.draw(Color(255, 255, 255, 120));
	infoRect.drawFrame(2);
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
	statsFont(U"残り体力").draw(495, 132, Palette::Hotpink);
	RoundRect(495, 183, 210, 35, 2).draw(Palette::Black);
	RoundRect(495, 183, 210 * playerHP / maxHP, 35, 2).draw((playerHP >= 100 ? Palette::Lightgreen : (playerHP >= 50 ? Palette::Yellow : Palette::Red)));
}
