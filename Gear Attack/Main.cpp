// include
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Main.h"
#include "Menu.h"

void Main()
{
	Window::Resize({ windowWidth,windowHeight }, true);
	Window::SetTitle(U"Gear Attack v1.0");
	Graphics::SetBackground(Color(200, 255, 200));

	// 使用するシーン
	SceneManager<String> SceneMgr;
	SceneMgr.setFadeColor(Color(255, 255, 255));
	SceneMgr.add<Menu>(U"Menu");
	SceneMgr.changeScene(U"Menu", 500, true);
	
	// メインループ
	while (System::Update())
	{
		SceneMgr.updateScene();
		SceneMgr.drawScene();
	}
}
