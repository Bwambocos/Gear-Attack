// include
#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Main.h"

// const
const int fieldSize = 392;
const int cellSize = 28;

// ƒQ[ƒ€‰æ–Ê
class Game :public SceneManager<String>::Scene
{
private:
	Texture gameField;
	Grid<int>fieldData;
	int stageNum, diffNum;

public:
	Game(const InitData& init);
	void update() override;
	void draw() const override;
};
