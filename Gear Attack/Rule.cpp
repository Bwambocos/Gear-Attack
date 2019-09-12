// include
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Rule.h"

// ‘€ìà–¾ ‰Šú‰»
Rule::Rule(const InitData& init) :IScene(init)
{
	mainImg = Texture(U"data/Rule/main.png");
	getData().firstPlayFlag = false;
}

// ‘€ìà–¾ XV
void Rule::update()
{
	if (KeyG.pressed()) changeScene(U"Select");
}

// ‘€ìà–¾ •`‰æ
void Rule::draw() const
{
	mainImg.drawAt(Scene::Center());
}
