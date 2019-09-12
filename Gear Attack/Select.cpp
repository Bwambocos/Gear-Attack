// include
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Select.h"

// ステージ選択 初期化
Select::Select(const InitData& init) :IScene(init)
{
	titleFont = Font(54, Typeface::Bold);
	stageFont = Font(42, Typeface::Regular);
	diffFont = Font(45, Typeface::Regular);
	choiceFont = Font(36, Typeface::Medium);
	for (auto i : step(3)) stageRect[i] = HighlightingShape<Rect>(15, 144 + 71 * i, 330, 56);
	for (auto i : step(4)) diffRect[i] = HighlightingShape<Rect>(375, 99 + 75 * i, 330, 60);
	startRect = HighlightingShape<Rect>(Arg::center(Scene::Width() / 4 * 3, 441), choiceFont(U"ゲームスタート").region().w + 30, 48);
	backToMenuRect = HighlightingShape<Rect>(Arg::center(Scene::Width() / 4, 441), choiceFont(U"メニューに戻る").region().w + 30, 48);
	goUpTrig = HighlightingShape<Triangle>(180, 99, 210, 129, 150, 129);
	goDownTrig = HighlightingShape<Triangle>(150, 357, 210, 357, 180, 387);
	selectSound = Audio(U"data//Select//selectSound.wav");
	titleLine = Line(0, 84, Scene::Width(), 84);
	startLine = Line(0, 402, Scene::Width(), 402);
	centerLine = Line(Scene::Width() / 2, 84, Scene::Width() / 2, 402);
	stageNum = 0;
	while (FileSystem::Exists(U"data/Game/s" + Format(stageNum + 1) + U".txt")) ++stageNum;
	getData().selectedStageNum = -1;
	getData().selectedDiffNum = -1;
	getData().prevScene = U"Select";
}

// ステージ選択 更新
void Select::update()
{
	if (getData().firstPlayFlag)
	{
		getData().firstPlayFlag = false;
		changeScene(U"Rule");
	}
	for (auto i : step(3))
	{
		if (i + getData().stageListBeginNum > stageNum) break;
		stageRect[i].update();
		if (stageRect[i].leftClicked())
		{
			selectSound.play();
			getData().selectedStageNum = (getData().selectedStageNum == i + getData().stageListBeginNum ? -1 : i + getData().stageListBeginNum);
		}
	}
	for (auto i : step(4))
	{
		diffRect[i].update();
		if (diffRect[i].leftClicked())
		{
			selectSound.play();
			getData().selectedDiffNum = (getData().selectedDiffNum == i ? -1 : i);
		}
	}
	startRect.update();
	backToMenuRect.update();
	if (getData().stageListBeginNum > 1)
	{
		goUpTrig.update();
		if (goUpTrig.leftClicked() || Mouse::Wheel() < 0)
		{
			selectSound.play();
			--getData().stageListBeginNum;
		}
	}
	if (getData().stageListBeginNum + 3 <= stageNum)
	{
		goDownTrig.update();
		if (goDownTrig.leftClicked() || Mouse::Wheel() > 0)
		{
			selectSound.play();
			++getData().stageListBeginNum;
		}
	}
	if (getData().selectedStageNum != -1 && getData().selectedDiffNum != -1 && startRect.leftClicked())
	{
		selectSound.play();
		changeScene(U"Game");
	}
	if (backToMenuRect.leftClicked())
	{
		selectSound.play();
		changeScene(U"Menu");
	}
}

// ステージ選択 描画
void Select::draw() const
{
	for (auto i : step(3))
	{
		if (i + getData().stageListBeginNum > stageNum) break;
		stageRect[i].drawHighlight((i + getData().stageListBeginNum == getData().selectedStageNum ? Color(0, 255, 255) : Color(255, 255, 255)));
	}
	for (auto i : step(4)) diffRect[i].drawHighlight((i == getData().selectedDiffNum ? Color(0, 255, 255) : Color(255, 255, 255)));
	startRect.drawHighlight();
	backToMenuRect.drawHighlight();
	if (getData().stageListBeginNum > 1) goUpTrig.drawHighlight();
	if (getData().stageListBeginNum + 3 <= stageNum) goDownTrig.drawHighlight();
	titleLine.draw(LineStyle::RoundDot, 3);
	startLine.draw(LineStyle::RoundDot, 3);
	centerLine.draw(LineStyle::RoundDot, 3);
	titleFont(U"ステージと難易度を選択").drawAt(Scene::Width() / 2, 42, Color(255, 165, 64));
	for (auto i : step(3))
	{
		if (i + getData().stageListBeginNum > stageNum) break;
		stageFont(U"ステージ" + Format(i + getData().stageListBeginNum)).drawAt(stageRect[i].center(), Color(32, 32, 32));
	}
	for (auto i : step(4)) diffFont(diffString[i]).drawAt(diffRect[i].center(), Color(32, 32, 32));
	choiceFont(U"ゲームスタート").drawAt(Scene::Width() / 4 * 3, 441, (getData().selectedStageNum != -1 && getData().selectedDiffNum != -1 ? Color(255, 64, 64) : Palette::Gray));
	choiceFont(U"メニューに戻る").drawAt(Scene::Width() / 4, 441, Color(32, 32, 32));
}
