#pragma once

// �V�[���\����
typedef enum
{
	Scene_Menu,
} Scene_S;

// �V�[���X�V
void SceneMgr_Update();

// �V�[���`��
void SceneMgr_Draw();

// �V�[���ύX
void SceneMgr_ChangeScene(Scene_S);