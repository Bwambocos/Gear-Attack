// include
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Settings.h"

// �ݒ� ������
Settings::Settings(const InitData& init) :IScene(init)
{
	titleFont = Font(54, U"data//fontR.ttc", FontStyle::Bold);
	choiceFont = Font(36, U"data//fontR.ttc");
	selectSound = Audio(U"data//Settings//selectSound.wav");
	goMenuRect = HighlightingShape<Rect>(Arg::center(Scene::Width() / 2, Scene::Height() - 10 - choiceFont.height() / 2), choiceFont(U"���j���[�֖߂�").region().w + 30, 36);
	bgmCheckRect = HighlightingShape<Rect>(Scene::Width() - 51, 30 + titleFont.height(), 36, 36);
	bgmNumRect = HighlightingShape<Rect>(Scene::Width() - 51, 45 + titleFont.height() + choiceFont.height(), 36, 36);
	seCheckRect = HighlightingShape<Rect>(Scene::Width() - 51, 60 + titleFont.height() + choiceFont.height() * 2, 36, 36);
}

// �ݒ� �X�V
void Settings::update()
{
	goMenuRect.update();
	bgmCheckRect.update();
	bgmNumRect.update();
	seCheckRect.update();
	if (goMenuRect.leftClicked())
	{
		selectSound.play();
		changeScene(U"Menu");
	}
	if (bgmCheckRect.leftClicked())
	{
		selectSound.play();
		getData().bgmFlag = !getData().bgmFlag;
	}
	if (bgmNumRect.leftClicked())
	{
		selectSound.play();
		++getData().bgmNum;
		getData().bgmNum %= 3;
	}
	if (seCheckRect.leftClicked())
	{
		selectSound.play();
		getData().seFlag = !getData().seFlag;
	}
}

// �ݒ� �`��
void Settings::draw() const
{
	goMenuRect.drawHighlight();
	bgmCheckRect.drawHighlight(getData().bgmFlag ? getData().schemeColor5 : getData().schemeColor4);
	seCheckRect.drawHighlight(getData().seFlag ? getData().schemeColor5 : getData().schemeColor4);
	bgmNumRect.drawHighlight(bgmNumRect.mouseOver() ? getData().schemeColor5 : getData().schemeColor4);
	titleFont(U"�ݒ�").drawAt(Scene::Width() / 2, choiceFont.height(), getData().stringColor);
	choiceFont(U"BGM�̗L��").draw(15, 30 + titleFont.height(), getData().stringColor);
	if (getData().bgmFlag) choiceFont(U"��").drawAt(bgmCheckRect.center(), getData().stringColor);
	choiceFont(U"BGM�̑I��").draw(15, 45 + titleFont.height() + choiceFont.height(), getData().stringColor);
	choiceFont(Format(getData().bgmNum + 1)).drawAt(bgmNumRect.center(), getData().stringColor);
	choiceFont(U"SE�̗L��").draw(15, 60 + titleFont.height() + choiceFont.height() * 2, getData().stringColor);
	if (getData().seFlag) choiceFont(U"��").drawAt(seCheckRect.center(), getData().stringColor);
	choiceFont(U"���j���[�֖߂�").drawAt(goMenuRect.center(), getData().stringColor);
}
