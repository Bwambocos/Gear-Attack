// include
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Menu.h"

// メニュー 初期化
Menu::Menu(const InitData& init) :IScene(init)
{
	image = Texture(U"example\\windmill.png");
}

// メニュー 更新
void Menu::update()
{

}

// メニュー 描画
void Menu::draw() const
{
	image.drawAt(Window::Width() / 2, Window::Height() / 2);
}
