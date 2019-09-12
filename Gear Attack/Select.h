// include
#pragma once
#include "Main.h"

// ステージ選択
class Select :public MyApp::Scene
{
private:
	Font titleFont, stageFont, diffFont, choiceFont;
	HighlightingShape<Rect> stageRect[3], diffRect[4], startRect, backToMenuRect;
	HighlightingShape<Triangle> goUpTrig, goDownTrig;
	Audio selectSound;
	Line titleLine, startLine, centerLine;
	String diffString[4] = { U"かんたん",U"ふつう",U"むずかしい",U"不可能" };
	int stageNum;

public:
	Select(const InitData& init);
	void update() override;
	void draw() const override;
};
