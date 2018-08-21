// include
#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Main.h"

// ê›íË
class Settings :public MyApp::Scene
{
private:
	
public:
	Settings(const InitData& init);
	void update() override;
	void draw() const override;
};
