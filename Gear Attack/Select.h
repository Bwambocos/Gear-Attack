// include
#pragma once
#include "Main.h"

// �X�e�[�W�I��
class Select :public MyApp::Scene
{
private:
	Font titleFont, stageFont, diffFont, choiceFont;
	HighlightingShape<Rect> stageRect[3], diffRect[4], startRect, backToMenuRect;
	HighlightingShape<Triangle> goUpTrig, goDownTrig;
	Audio selectSound;
	Line titleLine, startLine, centerLine;
	String diffString[4] = { U"���񂽂�",U"�ӂ�",U"�ނ�������",U"�s�\" };
	int stageNum;

public:
	Select(const InitData& init);
	void update() override;
	void draw() const override;
};
