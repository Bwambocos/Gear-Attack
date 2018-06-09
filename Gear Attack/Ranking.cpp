// include
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Ranking.h"

// ランキング 初期化
Ranking::Ranking(const InitData& init) :IScene(init)
{
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
	goUpTrig = HighlightingShape<Triangle>(17.5, choice1Rect.y + choice1Rect.h + 10, 25, choice1Rect.y + choice1Rect.h + 25, 10, choice1Rect.y + choice1Rect.h + 25);
	goDownTrig = HighlightingShape<Triangle>(17.5, choice1Rect.y + choice1Rect.h + 10 + rankFont.height() * 5, 10, choice1Rect.y + choice1Rect.h - 5 + rankFont.height() * 5, 25, choice1Rect.y + choice1Rect.h - 5 + rankFont.height() * 5);
}

// ランキング 更新
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
	if (rankingBeginNum >= 1)
	{
		goUpTrig.update();
		if (goUpTrig.leftClicked() || Mouse::Wheel() > 0) --rankingBeginNum;
	}
	if (rankingBeginNum + 5 < rankingData.size())
	{
		goDownTrig.update();
		if (goDownTrig.leftClicked() || Mouse::Wheel() < 0) ++rankingBeginNum;
	}
}

// ランキング 描画
void Ranking::draw() const
{
	titleFont(U"ステージ" + Format(stageNum)).drawAt(Window::Width() / 2, 10 + titleFont.height() / 2);
	choice1Rect.drawHighlight(diffNum == 0 ? Color(0, 255, 255) : Color(255, 255, 255));
	choice2Rect.drawHighlight(diffNum == 1 ? Color(0, 255, 255) : Color(255, 255, 255));
	choice3Rect.drawHighlight(diffNum == 2 ? Color(0, 255, 255) : Color(255, 255, 255));
	choice4Rect.drawHighlight(diffNum == 3 ? Color(0, 255, 255) : Color(255, 255, 255));
	choiceFont(diffStr[0]).drawAt(choice1Rect.center());
	choiceFont(diffStr[1]).drawAt(choice2Rect.center());
	choiceFont(diffStr[2]).drawAt(choice3Rect.center());
	choiceFont(diffStr[3]).drawAt(choice4Rect.center());
	if (rankingBeginNum >= 1) goUpTrig.drawHighlight(goUpTrig.mouseOver() ? Color(0, 255, 255) : Color(255, 255, 255));
	if (rankingBeginNum + 5 < rankingData.size()) goDownTrig.drawHighlight(goDownTrig.mouseOver() ? Color(0, 255, 255) : Color(255, 255, 255));
	for (auto i : step(Min<int>(5, rankingData.size() - rankingBeginNum)))
	{
		rankFont(Format(i + 1 + rankingBeginNum) + U"位 " + rankingData[i + rankingBeginNum].second).draw(35, choice1Rect.y + choice1Rect.h + 10 + rankFont.height()*i);
		auto scoreWidth = rankFont(Format(rankingData[i + rankingBeginNum].first) + U"点").region().w;
		rankFont(Format(rankingData[i + rankingBeginNum].first) + U"点").draw(Window::Width() - 35 - scoreWidth, choice1Rect.y + choice1Rect.h + 10 + rankFont.height()*i);
	}
}

// ランキング リロード
void Ranking::reload(bool newWrite)
{
	String fileDir = U"data//Ranking//Stage" + Format(stageNum) + U"//" + U"saveData" + Format(diffNum) + U".txt", fileLine;
	TextReader reader(fileDir);
	bool reWriteFlag = false;
	rankingData.clear();
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
		rankingData.push_back(std::make_pair(Parse<uint64>(arr[0]), arr[1]));
	}
	if (newWrite && !reWriteFlag) rankingData.push_back(std::make_pair(getData().gameScore, getData().playerName));
	std::sort(rankingData.rbegin(), rankingData.rend());
	reader.close();
	if (newWrite)
	{
		TextWriter writer(fileDir);
		for (auto data : rankingData) writer.writeln(Format(data.first) + U"," + data.second + ',');
		writer.close();
	}
	rankingBeginNum = 0;
}
