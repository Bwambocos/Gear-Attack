// include
#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>

// ���j���[
class Menu :public SceneManager<String>::Scene
{
private:
	Texture image;

public:
	Menu(const InitData& init);
	void update() override;
	void draw() const override;
};
