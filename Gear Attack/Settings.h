// include
#pragma once
#include "Main.h"

// ê›íË
class Settings :public MyApp::Scene
{
private:
	Font titleFont, choiceFont;
	Audio selectSound;
	HighlightingShape<Rect>goMenuRect, bgmCheckRect, bgmNumRect, seCheckRect;

public:
	Settings(const InitData& init);
	void update() override;
	void draw() const override;
};
