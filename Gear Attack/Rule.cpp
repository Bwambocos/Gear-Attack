// include
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Rule.h"

// ������� ������
Rule::Rule(const InitData& init) :IScene(init)
{
	mainImg = Texture(U"data/Rule/main.png");
}

// ������� �X�V
void Rule::update()
{

}

// ������� �`��
void Rule::draw() const
{
	mainImg.drawAt(Window::Center());
}
