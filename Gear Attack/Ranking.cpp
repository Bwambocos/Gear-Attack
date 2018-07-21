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
	titleFont = Font(54, Typeface::Bold);
	choiceFont = Font(28);
	rankFont = Font(36);
	choice1Rect.x = 10; choice1Rect.y = 20 + titleFont.height(); choice1Rect.w = (Window::Width() - 50) / 4; choice1Rect.h = 54;
	choice2Rect.x = choice1Rect.x + choice1Rect.w + 10; choice2Rect.y = 20 + titleFont.height(); choice2Rect.w = (Window::Width() - 50) / 4; choice2Rect.h = 54;
	choice3Rect.x = choice2Rect.x + choice2Rect.w + 10; choice3Rect.y = 20 + titleFont.height(); choice3Rect.w = (Window::Width() - 50) / 4; choice3Rect.h = 54;
	choice4Rect.x = choice3Rect.x + choice3Rect.w + 10; choice4Rect.y = 20 + titleFont.height(); choice4Rect.w = (Window::Width() - 50) / 4; choice4Rect.h = 54;
	goMenuRect = HighlightingShape<Rect>(Arg::center(Window::Width() / 4, Window::Height() - 10 - choiceFont.height() / 2), choiceFont(U"メニューへ戻る").region().w + 30, 36);
	goSelectRect = HighlightingShape<Rect>(Arg::center(Window::Width() / 4 * 3, Window::Height() - 10 - choiceFont.height() / 2), choiceFont(U"ゲームへ戻る").region().w + 30, 36);
	goUpTrig = HighlightingShape<Triangle>(17.5, choice1Rect.y + choice1Rect.h + 10, 25, choice1Rect.y + choice1Rect.h + 25, 10, choice1Rect.y + choice1Rect.h + 25);
	goDownTrig = HighlightingShape<Triangle>(17.5, choice1Rect.y + choice1Rect.h + 10 + rankFont.height() * 5, 10, choice1Rect.y + choice1Rect.h - 5 + rankFont.height() * 5, 25, choice1Rect.y + choice1Rect.h - 5 + rankFont.height() * 5);
	goLeftTrig = HighlightingShape<Triangle>(10, 35, 60, 10, 60, 60);
	goRightTrig = HighlightingShape<Triangle>(Window::Width() - 10, 35, Window::Width() - 60, 60, Window::Width() - 60, 10);
	if (getData().prevScene == U"Game" && getData().writeRankingFlag)
	{
		if (getData().playerName != U"名無し")
		{
			inputNameFlag = false;
			Ranking::reload(true);
		}
		else
		{
			inputNameFlag = true;
			initInputName();
		}
	}
	else
	{
		inputNameFlag = false;
		stageNum = 1;
		diffNum = 0;
	}
	getData().prevScene = U"Ranking";
}

// ランキング 更新
void Ranking::update()
{
	if (!inputNameFlag)
	{
		choice1Rect.update();
		choice2Rect.update();
		choice3Rect.update();
		choice4Rect.update();
		goMenuRect.update();
		goSelectRect.update();
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
		if (goMenuRect.leftClicked()) changeScene(U"Menu");
		if (goSelectRect.leftClicked()) changeScene(U"Select");
		if (rankingBeginNum >= 1)
		{
			goUpTrig.update();
			if (goUpTrig.leftClicked() || Mouse::Wheel() > 0) --rankingBeginNum;
		}
		if (rankingBeginNum + 5 < (signed)rankingData.size())
		{
			goDownTrig.update();
			if (goDownTrig.leftClicked() || Mouse::Wheel() < 0) ++rankingBeginNum;
		}
		if (stageNum > 1)
		{
			goLeftTrig.update();
			if (goLeftTrig.leftClicked())
			{
				--stageNum;
				Ranking::reload(false);
			}
		}
		if (FileSystem::Exists(U"data/Game/s" + Format(stageNum + 1) + U".txt"))
		{
			goRightTrig.update();
			if (goRightTrig.leftClicked())
			{
				++stageNum;
				Ranking::reload(false);
			}
		}
		if (KeyM.pressed()) changeScene(U"Menu");
	}
	else updateInputName();
}

// ランキング 描画
void Ranking::draw() const
{
	if (!inputNameFlag)
	{
		titleFont(U"ステージ" + Format(stageNum)).drawAt(Window::Width() / 2, 10 + titleFont.height() / 2);
		choice1Rect.drawHighlight(diffNum == 0 ? Color(0, 255, 255) : Color(255, 255, 255));
		choice2Rect.drawHighlight(diffNum == 1 ? Color(0, 255, 255) : Color(255, 255, 255));
		choice3Rect.drawHighlight(diffNum == 2 ? Color(0, 255, 255) : Color(255, 255, 255));
		choice4Rect.drawHighlight(diffNum == 3 ? Color(0, 255, 255) : Color(255, 255, 255));
		goMenuRect.drawHighlight(goMenuRect.mouseOver() ? Color(0, 255, 255) : Color(255, 255, 255));
		goSelectRect.drawHighlight(goSelectRect.mouseOver() ? Color(0, 255, 255) : Color(255, 255, 255));
		choiceFont(diffStr[0]).drawAt(choice1Rect.center());
		choiceFont(diffStr[1]).drawAt(choice2Rect.center());
		choiceFont(diffStr[2]).drawAt(choice3Rect.center());
		choiceFont(diffStr[3]).drawAt(choice4Rect.center());
		choiceFont(U"メニューへ戻る").drawAt(Window::Width() / 4, Window::Height() - 10 - choiceFont.height() / 2);
		choiceFont(U"ゲームへ戻る").drawAt(Window::Width() / 4 * 3, Window::Height() - 10 - choiceFont.height() / 2);
		if (rankingBeginNum >= 1) goUpTrig.drawHighlight(goUpTrig.mouseOver() ? Color(0, 255, 255) : Color(255, 255, 255));
		if (rankingBeginNum + 5 < (signed)rankingData.size()) goDownTrig.drawHighlight(goDownTrig.mouseOver() ? Color(0, 255, 255) : Color(255, 255, 255));
		if (stageNum > 1) goLeftTrig.drawHighlight(goLeftTrig.mouseOver() ? Color(0, 255, 255) : Color(255, 255, 255));
		if (FileSystem::Exists(U"data/Game/s" + Format(stageNum + 1) + U".txt")) goRightTrig.drawHighlight(goRightTrig.mouseOver() ? Color(0, 255, 255) : Color(255, 255, 255));
		for (auto i : step(Min<int>(5, (int)rankingData.size() - rankingBeginNum)))
		{
			rankFont(Format(i + 1 + rankingBeginNum) + U"位 " + rankingData[i + rankingBeginNum].second).draw(35, choice1Rect.y + choice1Rect.h + 10 + rankFont.height()*i, rankingData[i + rankingBeginNum].second == getData().playerName ? Palette::Orange : Palette::White);
			auto scoreWidth = rankFont(Format(rankingData[i + rankingBeginNum].first) + U"点").region().w;
			rankFont(Format(rankingData[i + rankingBeginNum].first) + U"点").draw(Window::Width() - 35 - scoreWidth, choice1Rect.y + choice1Rect.h + 10 + rankFont.height()*i, rankingData[i + rankingBeginNum].second == getData().playerName ? Palette::Orange : Palette::White);
		}
	}
	else drawInputName();
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
				begin = (int)i + 1;
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

// 名前入力 初期化
void Ranking::initInputName()
{
	if (getData().playerName != U"名無し")
	{
		inputNameFlag = false;
		Ranking::reload(true);
	}
	for (int i = 0; i < (signed)buttonChars.length(); ++i)
	{
		const auto x = (i % 12) * 50 + 60;
		const auto y = (i / 12) * 50 + 200;
		charButtons.emplace_back(String(1, buttonChars[i]), Rect(x, y, 44, 44));
	}
	charButtons.emplace_back(U" ", Rect(6 * 50 + 60, 3 * 50 + 200, 144, 44));
	charButtons.emplace_back(U"[BS]", Rect(9 * 50 + 60, 3 * 50 + 200, 94, 44));
	FontAsset::Register(U"nameFont", 42, Typeface::Medium);
	FontAsset::Register(U"buttonFont", 24, Typeface::Medium);
	maxNameLength = Window::Width() - 70 - rankFont(Format(getData().gameScore) + U"点").region().w - rankFont.height() * 2;
}

// 名前入力 更新
void Ranking::updateInputName()
{
	for (auto& button : charButtons)
	{
		if (button.update())
		{
			if (button.getText() == U"[BS]")
			{
				if (!getData().playerName.isEmpty()) getData().playerName.pop_back();
			}
			else if ((signed)getData().playerName.length() < maxNameLength) getData().playerName.append(button.getText());
			break;
		}
	}
	TextInput::UpdateText(getData().playerName);
	while (rankFont(getData().playerName).region().w > maxNameLength) getData().playerName.erase(getData().playerName.begin() + getData().playerName.length() - 1);
	if (getData().playerName.length() > 0 && getData().playerName[getData().playerName.length() - 1] == U'\n')
	{
		if (getData().playerName[getData().playerName.length() - 1] == U'\n') getData().playerName.erase(getData().playerName.begin() + getData().playerName.length() - 1);
		if (getData().playerName.length() == 0) getData().playerName = U"名無し";
		inputNameFlag = false;
		Ranking::reload(true);
	}
}

// 名前入力 描画
void Ranking::drawInputName() const
{
	FontAsset(U"nameFont")(U"ランキングにのせる名前を入力").drawAt(Window::Width() / 2, 10 + titleFont.height() / 2);
	for (const auto& button : charButtons) button.draw();
	RoundRect(60, 80, 594, 80, 8).draw(Color(240, 250, 255));
	FontAsset(U"nameFont")(getData().playerName).draw(77, 90, Color(20));
	FontAsset(U"nameFont")(U"ENTERキーで決定").drawAt(Window::Width() / 2, Window::Height() - 10 - titleFont.height() / 2);
}
