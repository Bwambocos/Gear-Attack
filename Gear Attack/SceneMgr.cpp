// include
#include "SceneMgr.h"
#include "Menu.h"

// グローバル変数
static Scene_S nowScene = Scene_Menu;

// シーン更新
void SceneMgr_Update()
{
	switch (nowScene)
	{
	case Scene_Menu:
		Menu_Update();
		break;
	}
}

// シーン描画
void SceneMgr_Draw()
{
	switch (nowScene)
	{
	case Scene_Menu:
		Menu_Draw();
		break;
	}
}

// シーン変更
void SceneMgr_ChangeScene(Scene_S nextScene)
{
	nowScene = nextScene;
	switch (nowScene)
	{
	case Scene_Menu:
		Menu_Init();
		break;
	}
}