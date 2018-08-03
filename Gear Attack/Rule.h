// include
#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Main.h"

// ‘€ìà–¾
class Rule :public MyApp::Scene
{
private:
	Texture mainImg;

public:
	Rule(const InitData& init);
	void update() override;
	void draw() const override;
};
