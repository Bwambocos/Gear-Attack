// include
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Ranking.h"

// ランキング 初期化
Ranking::Ranking(const InitData& init) :IScene(init)
{
	diffNum = getData().selectedDiffNum;
	stageNum = getData().selectedStageNum;
	String fileDir = U"data//Ranking//Stage" + Format(stageNum) + U"//" + U"saveData" + Format(diffNum) + U".ini", fileLine;
	TextReader reader(fileDir);
	while (reader.readLine(fileLine))
	{
		Array<String>arr;
		int begin = 0;
		for (auto i : step(fileLine.length()))
		{
			if (fileLine[i] == U',')
			{
				arr.push_back(fileLine.substr(begin, i - begin + 1));
				begin = i + 1;
			}
		}
		rankingData.push_back(std::make_pair(Parse<uint64>(arr[1]), arr[0]));
	}
	rankingData.push_back(std::make_pair(getData().gameScore, getData().playerName));
	std::sort(rankingData.rbegin(), rankingData.rend());
	TextWriter writer(fileDir);
	for (auto data : rankingData) writer.writeln(Format(data.first) + U"," + data.second + ',');
	titleFont = Font(54, Typeface::Bold);
	rankFont = Font(36);
}

// ランキング 更新
void Ranking::update()
{

}

// ランキング 描画
void Ranking::draw() const
{
	titleFont(U"ステージ" + Format(stageNum) + U" / " + diffStr[diffNum]).drawAt(Window::Width() / 2, 15, Palette::Black);

}
