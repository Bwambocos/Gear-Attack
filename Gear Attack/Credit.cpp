// include
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Credit.h"

// クレジット 初期化
Credit::Credit(const InitData& init) :IScene(init)
{
	mainImg = Texture(U"data//Credit//main.png");
}

// クレジット 更新
void Credit::update()
{
	if (KeyT.pressed()) Twitter::OpenFollowWindow(U"babcs2035");
	if (KeyM.pressed()) changeScene(U"Menu");
}

// クレジット 描画
void Credit::draw() const
{
	mainImg.drawAt(Window::Center());
}
