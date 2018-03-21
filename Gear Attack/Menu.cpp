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
	creditRect = HighlightingShape<Rect>(Arg::center(242, 405), 220, 119);
	exitRect = HighlightingShape<Rect>(Arg::center(477, 405), 220, 119);
	rankingThumb = Texture(U"data\\Menu\\rankingThumb.png");
	startThumb = Texture(U"data\\Menu\\startThumb.png");
	tutorialThumb = Texture(U"data\\Menu\\tutorialThumb.png");
	titleFont = Font(64, Typeface::Bold);
	choiceFont = Font(42, Typeface::Medium);
}

// メニュー 更新
void Menu::update()
{
	rankingRect.update();
	startRect.update();
	tutorialRect.update();
	creditRect.update();
	exitRect.update();
	if (startRect.leftClicked()) changeScene(U"Select");
	if (exitRect.leftClicked()) System::Exit();
}

// メニュー 描画
void Menu::draw() const
{
	rankingRect.drawHighlight();
	startRect.drawHighlight();
	tutorialRect.drawHighlight();
	creditRect.drawHighlight();
	exitRect.drawHighlight();
	rankingThumb.drawAt(rankingRect.center(), (rankingRect.mouseOver() ? Color(222, 222, 222) : Palette::Gray));
	startThumb.drawAt(startRect.center(), (startRect.mouseOver() ? Color(222, 222, 222) : Palette::Gray));
	tutorialThumb.drawAt(tutorialRect.center(), (tutorialRect.mouseOver() ? Color(222, 222, 222) : Palette::Gray));
	titleFont(U"Gear Attack").drawAt(Window::Width() / 2, 56, Color(222, 222, 222));
	choiceFont(U"スコア\nボード").drawAt(rankingRect.center(), Color(32, 32, 32));
	choiceFont(U"ゲームに\n進む").drawAt(startRect.center(), Color(32, 32, 32));
	choiceFont(U"操作\n説明").drawAt(tutorialRect.center(), Color(32, 32, 32));
	choiceFont(U"クレジット").drawAt(creditRect.center(), Color(32, 32, 32));
	choiceFont(U"終了する").drawAt(exitRect.center(), Color(32, 32, 32));
}
