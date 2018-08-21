// include
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Settings.h"

// 設定 初期化
Settings::Settings(const InitData& init) :IScene(init)
{
	titleFont = Font(54, Typeface::Bold);
	choiceFont = Font(36);
	selectSound = Audio(U"data//Settings//selectSound.wav");
	goMenuRect = HighlightingShape<Rect>(Arg::center(Window::Width() / 2, Window::Height() - 10 - choiceFont.height() / 2), choiceFont(U"メニューへ戻る").region().w + 30, 36);
	bgmCheckRect = HighlightingShape<Rect>(Window::Width() - 51, 30 + titleFont.height(), 36, 36);
	bgmNumRect = HighlightingShape<Rect>(Window::Width() - 51, 45 + titleFont.height() + choiceFont.height(), 36, 36);
	seCheckRect = HighlightingShape<Rect>(Window::Width() - 51, 60 + titleFont.height() + choiceFont.height() * 2, 36, 36);
}

// 設定 更新
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
		getData().bgmNum %= 2;
	}
	if (seCheckRect.leftClicked())
	{
		selectSound.play();
		getData().seFlag = !getData().seFlag;
	}
}

// 設定 描画
void Settings::draw() const
{
	goMenuRect.drawHighlight();
	bgmCheckRect.drawHighlight(getData().bgmFlag ? Color(0, 255, 255) : Color(255, 255, 255));
	seCheckRect.drawHighlight(getData().seFlag ? Color(0, 255, 255) : Color(255, 255, 255));
	bgmNumRect.drawHighlight(bgmNumRect.mouseOver() ? Color(0, 255, 255) : Color(255, 255, 255));
	titleFont(U"設定").drawAt(Window::Width() / 2, choiceFont.height(), Palette::Black);
	choiceFont(U"BGMの有無").draw(15, 30 + titleFont.height(), Palette::Black);
	if (getData().bgmFlag) choiceFont(U"○").drawAt(bgmCheckRect.center());
	choiceFont(U"BGMの選択").draw(15, 45 + titleFont.height() + choiceFont.height(), Palette::Black);
	choiceFont(Format(getData().bgmNum + 1)).drawAt(bgmNumRect.center(), Palette::Black);
	choiceFont(U"SEの有無").draw(15, 60 + titleFont.height() + choiceFont.height() * 2, Palette::Black);
	if (getData().seFlag) choiceFont(U"○").drawAt(seCheckRect.center());
	choiceFont(U"メニューへ戻る").drawAt(goMenuRect.center());
}
