// include
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Select.h"

// ステージ選択 初期化
Select::Select(const InitData& init) :IScene(init)
{
	for (auto i : step(3)) stageRect[i] = HighlightingShape<Rect>(15, 144 + 71 * i, 330, 56);
	for (auto i : step(4)) diffRect[i] = HighlightingShape<Rect>(375, 99 + 75 * i, 330, 60);
	goUpTrig = HighlightingShape<Triangle>(180, 99, 210, 129, 150, 129);
	goDownTrig = HighlightingShape<Triangle>(150, 357, 210, 357, 180, 387);
	titleLine = Line(0, 84, Window::Width(), 84);
	startLine = Line(0, 402, Window::Width(), 402);
	centerLine = Line(Window::Width() / 2, 84, Window::Width() / 2, 402);
	titleFont = Font(54, Typeface::Bold);
	stageFont = Font(42, Typeface::Regular);
	diffFont = Font(45, Typeface::Regular);
	startFont = Font(36, Typeface::Medium);
	startRect = HighlightingShape<Rect>(Arg::center(Window::Width() / 2, 441), startFont(U"ゲームスタート").region().w + 30, 48);
}

// ステージ選択 更新
void Select::update()
{
	for (auto i : step(3)) stageRect[i].update();
	for (auto i : step(4)) diffRect[i].update();
	startRect.update();
	goUpTrig.update();
	goDownTrig.update();
}

// ステージ選択 描画
void Select::draw() const
{
	for (auto i : step(3)) stageRect[i].drawHighlight();
	for (auto i : step(4)) diffRect[i].drawHighlight();
	startRect.drawHighlight();
	goUpTrig.drawHighlight();
	goDownTrig.drawHighlight();
	titleLine.draw(LineStyle::RoundDot, 3);
	startLine.draw(LineStyle::RoundDot, 3);
	centerLine.draw(LineStyle::RoundDot, 3);
	titleFont(U"ステージと難易度を選択！").drawAt(Window::Width() / 2, 42, Color(255, 165, 64));
	for (auto i : step(4)) diffFont(diffString[i]).drawAt(diffRect[i].center(), Color(64, 64, 64));
	startFont(U"ゲームスタート").drawAt(Window::Width() / 2, 441, Color(255, 64, 64));
}
