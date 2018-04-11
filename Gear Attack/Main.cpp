// include
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Main.h"
#include "Menu.h"
#include "Select.h"

void Main()
{
	Window::Resize({ windowWidth,windowHeight }, true);
	Window::SetTitle(U"Gear Attack v1.0");
	Graphics::SetBackground(Palette::Seagreen);

	// 使用するシーン
	MyApp SceneMgr;
	SceneMgr.setFadeColor(Color(255, 255, 255));
	SceneMgr.add<Menu>(U"Menu");
	SceneMgr.add<Select>(U"Select");

	// メインループ
	while (System::Update())
	{
		SceneMgr.updateScene();
		SceneMgr.drawScene();
	}
}
