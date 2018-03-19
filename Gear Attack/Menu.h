// include
#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Main.h"

// ƒƒjƒ…[
class Menu :public SceneManager<String>::Scene
{
private:
	HighlightingShape<Rect>startRect, rankingRect, tutorialRect, creditRect, exitRect;
	Texture startThumb, rankingThumb, tutorialThumb;
	Font titleFont, choiceFont;

public:
	Menu(const InitData& init);
	void update() override;
	void draw() const override;
};
