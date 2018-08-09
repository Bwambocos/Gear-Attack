// include
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Credit.h"

// �N���W�b�g ������
Credit::Credit(const InitData& init) :IScene(init)
{
	mainImg = Texture(U"data//Credit//main.png");
}

// �N���W�b�g �X�V
void Credit::update()
{
	if (KeyT.pressed()) Twitter::OpenFollowWindow(U"babcs2035");
	if (KeyM.pressed()) changeScene(U"Menu");
}

// �N���W�b�g �`��
void Credit::draw() const
{
	mainImg.drawAt(Window::Center());
}
