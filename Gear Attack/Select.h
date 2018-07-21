// include
#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Main.h"

// �X�e�[�W�I��
class Select :public MyApp::Scene
{
private:
	HighlightingShape<Rect> stageRect[3], diffRect[4], startRect;
	HighlightingShape<Triangle> goUpTrig, goDownTrig;
	Line titleLine, startLine, centerLine;
	Font titleFont, stageFont, diffFont, startFont;
	String diffString[4] = { U"���񂽂�",U"�ӂ�",U"�ނ�������",U"������" };
	int stageNum;

public:
	Select(const InitData& init);
	void update() override;
	void draw() const override;
};
