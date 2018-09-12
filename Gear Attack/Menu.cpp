// include
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Menu.h"

// ���j���[ ������
Menu::Menu(const InitData& init) :IScene(init)
{
	rankingRect = HighlightingShape<Rect>(Arg::center(125, 221), 220, 220);
	startRect = HighlightingShape<Rect>(Arg::center(360, 221), 220, 220);
	tutorialRect = HighlightingShape<Rect>(Arg::center(595, 221), 220, 220);
	settingsRect = HighlightingShape<Rect>(Arg::center(125, 405), 220, 119);
	creditRect = HighlightingShape<Rect>(Arg::center(360, 405), 220, 119);
	exitRect = HighlightingShape<Rect>(Arg::center(595, 405), 220, 119);
	rankingThumb = Texture(U"data\\Menu\\rankingThumb.png");
	startThumb = Texture(U"data\\Menu\\startThumb.png");
	tutorialThumb = Texture(U"data\\Menu\\tutorialThumb.png");
	selectSound = Audio(U"data//Menu//selectSound.wav");
	titleFont = Font(64, Typeface::Bold);
	choiceFont = Font(42, Typeface::Medium);
	getData().prevScene = U"Menu";
}

// ���j���[ �X�V
void Menu::update()
{
	rankingRect.update();
	startRect.update();
	tutorialRect.update();
	settingsRect.update();
	creditRect.update();
	exitRect.update();
	if (rankingRect.leftClicked())
	{
		selectSound.play();
		changeScene(U"Ranking");
	}
	if (startRect.leftClicked())
	{
		selectSound.play();
		changeScene(U"Select");
	}
	if (tutorialRect.leftClicked())
	{
		selectSound.play();
		changeScene(U"Rule");
	}
	if (settingsRect.leftClicked())
	{
		selectSound.play();
		changeScene(U"Settings");
	}
	if (creditRect.leftClicked())
	{
		selectSound.play();
		changeScene(U"Credit");
	}
	if (exitRect.leftClicked())
	{
		selectSound.play();
		System::Exit();
	}
}

// ���j���[ �`��
void Menu::draw() const
{
	rankingRect.drawHighlight();
	startRect.drawHighlight();
	tutorialRect.drawHighlight();
	settingsRect.drawHighlight();
	creditRect.drawHighlight();
	exitRect.drawHighlight();
	rankingThumb.drawAt(rankingRect.center(), (rankingRect.mouseOver() ? Color(222, 222, 222) : Palette::Gray));
	startThumb.drawAt(startRect.center(), (startRect.mouseOver() ? Color(222, 222, 222) : Palette::Gray));
	tutorialThumb.drawAt(tutorialRect.center(), (tutorialRect.mouseOver() ? Color(222, 222, 222) : Palette::Gray));
	titleFont(U"Gear Attack "+versionStr).drawAt(Window::Width() / 2, 56, Color(222, 222, 222));
	choiceFont(U"�X�R�A\n�{�[�h").drawAt(rankingRect.center(), Color(32, 32, 32));
	choiceFont(U"�Q�[����\n�i��").drawAt(startRect.center(), Color(32, 32, 32));
	choiceFont(U"����\n����").drawAt(tutorialRect.center(), Color(32, 32, 32));
	choiceFont(U"�ݒ�").drawAt(settingsRect.center(), Color(32, 32, 32));
	choiceFont(U"�N���W�b�g").drawAt(creditRect.center(), Color(32, 32, 32));
	choiceFont(U"�I������").drawAt(exitRect.center(), Color(32, 32, 32));
}
