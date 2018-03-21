// include
#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Main.h"

// ステージ選択
class Select :public SceneManager<String>::Scene
{
private:

public:
	Select(const InitData& init);
	void update() override;
	void draw() const override;
};
