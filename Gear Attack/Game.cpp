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
}

// ゲーム画面 更新
void Game::update()
{

}

// ゲーム画面 描画
void Game::draw() const
{
	gameField.draw(0, 0);
}
