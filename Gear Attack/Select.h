// include
#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Main.h"

// �X�e�[�W�I��
class Select :public SceneManager<String>::Scene
{
private:

public:
	Select(const InitData& init);
	void update() override;
	void draw() const override;
};
