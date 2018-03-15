// include
#include "SceneMgr.h"
#include "Menu.h"

// �O���[�o���ϐ�
static Scene_S nowScene = Scene_Menu;

// �V�[���X�V
void SceneMgr_Update()
{
	switch (nowScene)
	{
	case Scene_Menu:
		Menu_Update();
		break;
	}
}

// �V�[���`��
void SceneMgr_Draw()
{
	switch (nowScene)
	{
	case Scene_Menu:
		Menu_Draw();
		break;
	}
}

// �V�[���ύX
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