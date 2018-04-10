// include
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Game.h"
#include "Select.h"

// �Q�[����� ������
Game::Game(const InitData& init) :IScene(init)
{
	gameField = Texture(U"data/Game/gameField.png");
	fieldData = Grid<int>(fieldSize / cellSize, fieldSize / cellSize);
}

// �Q�[����� �X�V
void Game::update()
{

}

// �Q�[����� �`��
void Game::draw() const
{
	gameField.draw(0, 0);
}
