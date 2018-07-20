// include
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Select.h"

// �X�e�[�W�I�� ������
Select::Select(const InitData& init) :IScene(init)
{
	for (auto i : step(3)) stageRect[i] = HighlightingShape<Rect>(15, 144 + 71 * i, 330, 56);
	for (auto i : step(4)) diffRect[i] = HighlightingShape<Rect>(375, 99 + 75 * i, 330, 60);
	goUpTrig = HighlightingShape<Triangle>(180, 99, 210, 129, 150, 129);
	goDownTrig = HighlightingShape<Triangle>(150, 357, 210, 357, 180, 387);
	warning = MessageBoxButtons();
	titleLine = Line(0, 84, Window::Width(), 84);
	startLine = Line(0, 402, Window::Width(), 402);
	centerLine = Line(Window::Width() / 2, 84, Window::Width() / 2, 402);
	titleFont = Font(54, Typeface::Bold);
	stageFont = Font(42, Typeface::Regular);
	diffFont = Font(45, Typeface::Regular);
	startFont = Font(36, Typeface::Medium);
	startRect = HighlightingShape<Rect>(Arg::center(Window::Width() / 2, 441), startFont(U"�Q�[���X�^�[�g").region().w + 30, 48);
	stageNum = 0, stageListBeginNum = 1;
	while (FileSystem::Exists(U"data/Game/s" + Format(stageNum + 1) + U".txt")) ++stageNum;
	getData().selectedStageNum = -1;
	getData().selectedDiffNum = -1;
	getData().prevScene = U"Select";
}

// �X�e�[�W�I�� �X�V
void Select::update()
{
	for (auto i : step(3))
	{
		if (i + stageListBeginNum > stageNum) break;
		stageRect[i].update();
		if (stageRect[i].leftClicked())
		{
			getData().selectedStageNum = (getData().selectedStageNum == i + stageListBeginNum ? -1 : i + stageListBeginNum);
		}
	}
	for (auto i : step(4))
	{
		diffRect[i].update();
		if (diffRect[i].leftClicked())
		{
			getData().selectedDiffNum = (getData().selectedDiffNum == i ? -1 : i);
		}
	}
	startRect.update();
	if (stageListBeginNum > 1)
	{
		goUpTrig.update();
		if (goUpTrig.leftClicked() || Mouse::Wheel() > 0) --stageListBeginNum;
	}
	if (stageListBeginNum + 3 <= stageNum)
	{
		goDownTrig.update();
		if (goDownTrig.leftClicked() || Mouse::Wheel() < 0) ++stageListBeginNum;
	}
	if (getData().selectedStageNum != -1 && getData().selectedDiffNum != -1 && startRect.leftClicked()) changeScene(U"Game");
}

// �X�e�[�W�I�� �`��
void Select::draw() const
{
	for (auto i : step(3))
	{
		if (i + stageListBeginNum > stageNum) break;
		stageRect[i].drawHighlight((i + stageListBeginNum == getData().selectedStageNum ? Color(0, 255, 255) : Color(255, 255, 255)));
	}
	for (auto i : step(4))
	{
		diffRect[i].drawHighlight((i == getData().selectedDiffNum ? Color(0, 255, 255) : Color(255, 255, 255)));
	}
	startRect.drawHighlight();
	if (stageListBeginNum > 1) goUpTrig.drawHighlight();
	if (stageListBeginNum + 3 <= stageNum) goDownTrig.drawHighlight();
	titleLine.draw(LineStyle::RoundDot, 3);
	startLine.draw(LineStyle::RoundDot, 3);
	centerLine.draw(LineStyle::RoundDot, 3);
	titleFont(U"�X�e�[�W�Ɠ�Փx��I��").drawAt(Window::Width() / 2, 42, Color(255, 165, 64));
	for (auto i : step(3))
	{
		if (i + stageListBeginNum > stageNum) break;
		stageFont(U"�X�e�[�W" + Format(i + stageListBeginNum)).drawAt(stageRect[i].center(), Color(32, 32, 32));
	}
	for (auto i : step(4))
	{
		diffFont(diffString[i]).drawAt(diffRect[i].center(), Color(32, 32, 32));
	}
	startFont(U"�Q�[���X�^�[�g").drawAt(Window::Width() / 2, 441, (getData().selectedStageNum != -1 && getData().selectedDiffNum != -1 ? Color(255, 64, 64) : Palette::Gray));
}
