// include
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Menu.h"

// ���j���[ ������
Menu::Menu(const InitData& init) :IScene(init)
{
	image = Texture(U"example\\windmill.png");
}

// ���j���[ �X�V
void Menu::update()
{

}

// ���j���[ �`��
void Menu::draw() const
{
	image.drawAt(Window::Width() / 2, Window::Height() / 2);
}
