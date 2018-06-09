// include
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Ranking.h"

// �����L���O ������
Ranking::Ranking(const InitData& init) :IScene(init)
{
	rankingData.clear();
	diffNum = getData().selectedDiffNum;
	stageNum = getData().selectedStageNum;
	rankingBeginNum = 0;
	Ranking::reload(true);
	titleFont = Font(54, Typeface::Bold);
	choiceFont = Font(28);
	rankFont = Font(36);
	choice1Rect.x = 10; choice1Rect.y = 20 + titleFont.height(); choice1Rect.w = (Window::Width() - 50) / 4; choice1Rect.h = 54;
	choice2Rect.x = choice1Rect.x + choice1Rect.w + 10; choice2Rect.y = 20 + titleFont.height(); choice2Rect.w = (Window::Width() - 50) / 4; choice2Rect.h = 54;
	choice3Rect.x = choice2Rect.x + choice2Rect.w + 10; choice3Rect.y = 20 + titleFont.height(); choice3Rect.w = (Window::Width() - 50) / 4; choice3Rect.h = 54;
	choice4Rect.x = choice3Rect.x + choice3Rect.w + 10; choice4Rect.y = 20 + titleFont.height(); choice4Rect.w = (Window::Width() - 50) / 4; choice4Rect.h = 54;
}

// �����L���O �X�V
void Ranking::update()
{
	choice1Rect.update();
	choice2Rect.update();
	choice3Rect.update();
	choice4Rect.update();
	if (choice1Rect.leftClicked())
	{
		diffNum = 0;
		Ranking::reload(false);
	}
	if (choice2Rect.leftClicked())
	{
		diffNum = 1;
		Ranking::reload(false);
	}
	if (choice3Rect.leftClicked())
	{
		diffNum = 2;
		Ranking::reload(false);
	}
	if (choice4Rect.leftClicked())
	{
		diffNum = 3;
		Ranking::reload(false);
	}
}

// �����L���O �`��
void Ranking::draw() const
{
	titleFont(U"�X�e�[�W" + Format(stageNum)).drawAt(Window::Width() / 2, 10 + titleFont.height() / 2);
	choice1Rect.drawHighlight(diffNum == 0 ? Color(0, 255, 255) : Color(255, 255, 255));
	choice2Rect.drawHighlight(diffNum == 1 ? Color(0, 255, 255) : Color(255, 255, 255));
	choice3Rect.drawHighlight(diffNum == 2 ? Color(0, 255, 255) : Color(255, 255, 255));
	choice4Rect.drawHighlight(diffNum == 3 ? Color(0, 255, 255) : Color(255, 255, 255));
	choiceFont(diffStr[0]).drawAt(choice1Rect.center());
	choiceFont(diffStr[1]).drawAt(choice2Rect.center());
	choiceFont(diffStr[2]).drawAt(choice3Rect.center());
	choiceFont(diffStr[3]).drawAt(choice4Rect.center());
	for (auto i : step(rankingData.size())) rankFont(Format(i + 1) + U"�� " + rankingData[i].second + U" " + Format(rankingData[i].first) + U"�_").draw(15, choice1Rect.y + choice1Rect.h + 10 + rankFont.height()*i);
}

// �����L���O �����[�h
void Ranking::reload(bool newWrite)
{
	String fileDir = U"data//Ranking//Stage" + Format(stageNum) + U"//" + U"saveData" + Format(diffNum) + U".txt", fileLine;
	TextReader reader(fileDir);
	bool reWriteFlag = false;
	while (reader.readLine(fileLine))
	{
		Array<String>arr;
		int begin = 0;
		for (auto i : step(fileLine.length()))
		{
			if (fileLine[i] == U',')
			{
				arr.push_back(fileLine.substr(begin, i - begin));
				begin = i + 1;
			}
			if (fileLine[i] == U'\n') break;
		}
		if (newWrite && arr[1] == getData().playerName)
		{
			arr[0] = Format(Max(Parse<uint64>(arr[0]), getData().gameScore));
			reWriteFlag = true;
		}
		else rankingData.push_back(std::make_pair(Parse<uint64>(arr[0]), arr[1]));
	}
	if (newWrite && !reWriteFlag) rankingData.push_back(std::make_pair(getData().gameScore, getData().playerName));
	std::sort(rankingData.rbegin(), rankingData.rend());
	reader.close();
	TextWriter writer(fileDir);
	for (auto data : rankingData) writer.writeln(Format(data.first) + U"," + data.second + ',');
	writer.close();
}