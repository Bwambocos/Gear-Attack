// include
#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Main.h"

// ƒQ[ƒ€‰æ–Ê
class Game :public SceneManager<String>::Scene
{
private:

public:
	Game(const InitData& init);
	void update() override;
	void draw() const override;
};
