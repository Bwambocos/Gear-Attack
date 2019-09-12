// include
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Main.h"
#include "Menu.h"
#include "Select.h"
#include "Game.h"
#include "Ranking.h"
#include "Rule.h"
#include "Credit.h"
#include "Settings.h"

void Main()
{
	Window::Resize(windowWidth, windowHeight);
	Window::SetTitle(U"Gear Attack " + versionStr);
	Scene::SetBackground(Color(22, 22, 22));

	// 使用するシーン
	MyApp SceneMgr;
	SceneMgr.setFadeColor(Color(22, 22, 22));
	SceneMgr.add<Menu>(U"Menu");
	SceneMgr.add<Select>(U"Select");
	SceneMgr.add<Game>(U"Game");
	SceneMgr.add<Ranking>(U"Ranking");
	SceneMgr.add<Rule>(U"Rule");
	SceneMgr.add<Credit>(U"Credit");
	SceneMgr.add<Settings>(U"Settings");

	// メインループ
	while (System::Update())
	{
		SceneMgr.updateScene();
		SceneMgr.drawScene();
	}
}
