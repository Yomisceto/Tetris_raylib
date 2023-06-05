#pragma once
#include "Vec2.h"
#include "raylibCpp.h"
#include <string>


/** Not the best way to save settings, but its alright for this project
 *  Note that we used inline - its new feature that keeps variables included only once.
 */
namespace settings
{	
	// Windows settings
	inline constexpr int screenWidth = 600;
	inline constexpr int screenHeight = 600;
	inline constexpr int fps = 60;
	inline constexpr Color BackgroundColor = BLACK;

	// Board settings
	inline constexpr int cellSize = 23;
	inline constexpr int padding = 2;
	inline constexpr Vec2<int> boardPosition{ 70,70 };
	inline constexpr Vec2<int> boardWidthHeight{ 10,20 };
	inline constexpr Color borderColor = WHITE;

	// Preview Board
	inline constexpr Vec2<int> previewBoardPos{ 400, 70 };
	inline constexpr Vec2<int> previewBoardSize{ 5, 5 };
	inline constexpr int previewCellSize = 23;
	inline constexpr int previewPadding = 1;
	inline constexpr Color previewBorderColor = WHITE;

	// Score monitor position
	inline constexpr Vec2<int> scorePos{ 400,300 };
	inline constexpr int scorePerRow = 10;

	// Game Over position
	inline constexpr Vec2<int> gameOverPos{ 400,300 };

	// Pause Text
	inline constexpr Vec2<int> pausePos{ 400,400 };
	inline constexpr int pauseFontSize = 20;
	inline constexpr Color pauseColor = WHITE;
	inline constexpr auto pauseText = "Paused";

	// Text 
	inline constexpr int fontSize = 20;
	inline constexpr Color textColor(WHITE);

	// hint Box
	inline constexpr auto hintText = "'D' - right\n'A' - left"
				"\n'E' - clockwise\n'Q' - counter-clockwise";
	inline constexpr Vec2<int> hintPos(340, 400);

	// Debug
	inline constexpr Vec2<int> fpsPos{ 10,10 };	
}