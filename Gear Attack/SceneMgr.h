#pragma once

// シーン構造体
typedef enum
{
	Scene_Menu,
} Scene_S;

// シーン更新
void SceneMgr_Update();

// シーン描画
void SceneMgr_Draw();

// シーン変更
void SceneMgr_ChangeScene(Scene_S);