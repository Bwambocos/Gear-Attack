// include
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Menu.h"

// メニュー 初期化
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
	titleFont = Font(64, U"data//fontR.ttc", FontStyle::Bold);
	choiceFont = Font(42, U"data//fontR.ttc");
	getData().prevScene = U"Menu";
}

// メニュー 更新
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

// メニュー 描画
void Menu::draw() const
{
	rankingRect.drawHighlight();
	startRect.drawHighlight();
	tutorialRect.drawHighlight();
	settingsRect.drawHighlight();
	creditRect.drawHighlight();
	exitRect.drawHighlight();
	rankingThumb.drawAt(rankingRect.center(), (rankingRect.mouseOver() ? getData().schemeColor5 : getData().schemeColor4));
	startThumb.drawAt(startRect.center(), (startRect.mouseOver() ? getData().schemeColor5 : getData().schemeColor4));
	tutorialThumb.drawAt(tutorialRect.center(), (tutorialRect.mouseOver() ? getData().schemeColor5 : getData().schemeColor4));
	titleFont(U"Gear Attack " + versionStr).drawAt(Scene::Width() / 2, 56, getData().stringColor);
	choiceFont(U"スコア\nボード").drawAt(rankingRect.center(), getData().stringColor);
	choiceFont(U"ゲームに\n進む").drawAt(startRect.center(), getData().stringColor);
	choiceFont(U"操作\n説明").drawAt(tutorialRect.center(), getData().stringColor);
	choiceFont(U"設定").drawAt(settingsRect.center(), getData().stringColor);
	choiceFont(U"クレジット").drawAt(creditRect.center(), getData().stringColor);
	choiceFont(U"終了する").drawAt(exitRect.center(), getData().stringColor);
}
