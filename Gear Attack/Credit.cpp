// include
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Credit.h"

// �N���W�b�g ������
Credit::Credit(const InitData& init) :IScene(init)
{
	mainImg = Texture(U"data//Credit//main.png");
	choiceFont = Font(28);
	selectSound = Audio(U"data//Credit//selectSound.wav");
	goTwitterRect = HighlightingShape<Rect>(Arg::center(Scene::Width() / 4, Scene::Height() - 10 - choiceFont.height() / 2), choiceFont(U"�A������J��").region().w + 30, 36);
	goMenuRect = HighlightingShape<Rect>(Arg::center(Scene::Width() / 4 * 3, Scene::Height() - 10 - choiceFont.height() / 2), choiceFont(U"���j���[�֖߂�").region().w + 30, 36);
}

// �N���W�b�g �X�V
void Credit::update()
{
	goTwitterRect.update();
	goMenuRect.update();
	if (goTwitterRect.leftClicked())
	{
		selectSound.play();
		Twitter::OpenFollowWindow(U"babcs2035");
	}
	if (goMenuRect.leftClicked())
	{
		selectSound.play();
		changeScene(U"Menu");
	}
}

// �N���W�b�g �`��
void Credit::draw() const
{
	mainImg.drawAt(Scene::Center());
	goTwitterRect.drawHighlight();
	goMenuRect.drawHighlight();
	choiceFont(U"�A������J��").drawAt(goTwitterRect.center(), Color(32, 32, 32));
	choiceFont(U"���j���[�֖߂�").drawAt(goMenuRect.center(), Color(32, 32, 32));
}
