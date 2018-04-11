// include
#pragma once
#include <Siv3D.hpp>

// const
const int32 windowWidth = 720;
const int32 windowHeight = 480;

// 共有データ
struct GameData
{
	int selectedStageNum, selectedDiffNum;
};

using MyApp = SceneManager<String, GameData>;

template <class ShapeType>
class HighlightingShape : public ShapeType
{
private:
	Transition m_transition = Transition(0.2s, 0.1s);

public:
	HighlightingShape() = default;

	explicit HighlightingShape(const ShapeType& shape)
		: ShapeType(shape) {}

	template <class ...Args>
	explicit HighlightingShape(Args&&... args)
		: ShapeType(std::forward<Args>(args)...) {}

	void update()
	{
		m_transition.update(ShapeType::mouseOver());
	}

	void drawHighlight(Color color = Color(255, 255, 255)) const
	{
		ShapeType::drawFrame(0, 2, color);
		ShapeType::draw(Color(color, (uint32)(m_transition.value() * 64)));
	}

	const Transition& getTransition() const
	{
		return m_transition;
	}
};
