// include
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Credit.h"

// クレジット 初期化
Credit::Credit(const InitData& init) :IScene(init)
{
	mainImg = Texture(U"data//Credit//main.png");
	choiceFont = Font(28);
	selectSound = Audio(U"data//Credit//selectSound.wav");
	goTwitterRect = HighlightingShape<Rect>(Arg::center(Scene::Width() / 4, Scene::Height() - 10 - choiceFont.height() / 2), choiceFont(U"連絡先を開く").region().w + 30, 36);
	goMenuRect = HighlightingShape<Rect>(Arg::center(Scene::Width() / 4 * 3, Scene::Height() - 10 - choiceFont.height() / 2), choiceFont(U"メニューへ戻る").region().w + 30, 36);
}

// クレジット 更新
void Credit::update()
{
	goTwitterRect.update();
	goMenuRect.update();
	if (goTwitterRect.leftClicked())
	{
		selectSound.play();
		Twitter::OpenFollowWindow(U"babcs2035");
	}
	if (goMenuRect.leftClicked())
	{
		selectSound.play();
		changeScene(U"Menu");
	}
}

// クレジット 描画
void Credit::draw() const
{
	mainImg.drawAt(Scene::Center());
	goTwitterRect.drawHighlight();
	goMenuRect.drawHighlight();
	choiceFont(U"連絡先を開く").drawAt(goTwitterRect.center(), Color(32, 32, 32));
	choiceFont(U"メニューへ戻る").drawAt(goMenuRect.center(), Color(32, 32, 32));
}
