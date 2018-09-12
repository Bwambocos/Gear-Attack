// include
#pragma once
#include "Main.h"

// ƒƒjƒ…[
class Menu :public MyApp::Scene
{
private:
	HighlightingShape<Rect>startRect, rankingRect, tutorialRect, settingsRect, creditRect, exitRect;
	Texture startThumb, rankingThumb, tutorialThumb;
	Audio selectSound;
	Font titleFont, choiceFont;

public:
	Menu(const InitData& init);
	void update() override;
	void draw() const override;
};
