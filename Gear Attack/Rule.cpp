// include
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Rule.h"

// ������� ������
Rule::Rule(const InitData& init) :IScene(init)
{
	mainImg = Texture(U"data/Rule/main.png");
	getData().firstPlayFlag = false;
}

// ������� �X�V
void Rule::update()
{
	if (KeyG.pressed()) changeScene(U"Select");
}

// ������� �`��
void Rule::draw() const
{
	mainImg.drawAt(Scene::Center());
}
