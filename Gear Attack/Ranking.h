// include
#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Main.h"

// const
const String buttonChars = U"ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!?-_";

// 順位データ
using rankData = std::pair<uint64, String>;

// 名前入力
class CharButton
{
private:
	String m_text;
	Rect m_rect;
	bool m_pressed = false;

public:
	CharButton() = default;
	CharButton(const String& text, const Rect& rect)
		: m_text(text)
		, m_rect(rect) {}
	bool update()
	{
		if (m_rect.leftClicked()) m_pressed = true;
		else if (m_pressed && !m_rect.mouseOver()) m_pressed = false;
		else if (m_pressed && m_rect.leftReleased())
		{
			m_pressed = false;
			return true;
		}
		return false;
	}
	void draw() const
	{
		const Color color(m_pressed ? 220 : m_rect.mouseOver() ? 240 : 255);
		RoundRect(m_rect, 4).draw(color);
		FontAsset(U"buttonFont")(m_text).drawAt(m_rect.center(), Palette::Black);
	}
	const String& getText() const { return m_text; }
};

// ランキング
class Ranking :public MyApp::Scene
{
private:
	std::vector<rankData>rankingData;
	HighlightingShape<Rect>choice1Rect, choice2Rect, choice3Rect, choice4Rect, goMenuRect, goSelectRect;
	HighlightingShape<Triangle>goUpTrig, goDownTrig, goLeftTrig, goRightTrig;
	Font titleFont, choiceFont, rankFont;
	String diffStr[4] = { U"かんたん",U"ふつう",U"むずかしい",U"いいえ" };
	Array<CharButton> charButtons;
	int diffNum, stageNum, rankingBeginNum, maxNameLength;
	bool inputNameFlag;

public:
	Ranking(const InitData& init);
	void update() override;
	void draw() const override;
	void reload(bool newWrite);
	void initInputName();
	void updateInputName();
	void drawInputName() const;
};
