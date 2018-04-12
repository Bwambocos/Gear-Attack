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
	infoRect = Rect(490, 10, 220, 124);
	infoFont = Font(42, Typeface::Bold);
}

// ゲーム画面 更新
void Game::update()
{

}

// ゲーム画面 描画
void Game::draw() const
{
	gameField.draw(0, 0);
	infoRect.draw(Color(255, 255, 255, 120));
	infoFont(U"ステージ" + Format(getData().selectedStageNum)).draw(495, 15, Palette::Black);
	switch (getData().selectedDiffNum)
	{
	case 0:
		infoFont(U"かんたん").draw(495, 72, Palette::Yellowgreen);
		break;
	case 1:
		infoFont(U"ふつう").draw(495, 72, Palette::Yellow);
		break;
	case 2:
		infoFont(U"むずかしい").draw(495, 72, Palette::Orange);
		break;
	case 3:
		infoFont(U"いいえ").draw(495, 72, Palette::Red);
		break;
	}
}
