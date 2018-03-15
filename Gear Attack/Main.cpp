// include
#include <Siv3D.hpp>
#include "Main.h"
#include "SceneMgr.h"

void Main()
{
	Window::Resize({ windowWidth,windowHeight }, true);
	Window::SetTitle(U"Gear Attack v1.0");
	while (System::Update())
	{
		SceneMgr_Update();
		SceneMgr_Draw();
	}
}