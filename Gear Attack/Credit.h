// include
#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Main.h"

// �N���W�b�g
class Credit :public MyApp::Scene
{
private:

public:
	Credit(const InitData& init);
	void update() override;
	void draw() const override;
};
