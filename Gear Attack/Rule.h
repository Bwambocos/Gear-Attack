// include
#pragma once
#include "Main.h"

// �������
class Rule :public MyApp::Scene
{
private:
	Texture mainImg;

public:
	Rule(const InitData& init);
	void update() override;
	void draw() const override;
};
