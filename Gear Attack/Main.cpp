// include
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Main.h"
#include "Menu.h"
#include "Select.h"
#include "Game.h"

void Main()
{
	Window::Resize({ windowWidth,windowHeight }, true);
	Window::SetTitle(U"Gear Attack v1.0");
	Graphics::SetBackground(Palette::Seagreen);

	// 使用するシーン
	SceneManager<String> SceneMgr;
	SceneMgr.setFadeColor(Color(255, 255, 255));
	SceneMgr.add<Menu>(U"Menu");
	SceneMgr.add<Select>(U"Select");
	SceneMgr.add<Game>(U"Game");
	
	// メインループ
	while (System::Update())
	{
		SceneMgr.updateScene();
		SceneMgr.drawScene();
	}
}
