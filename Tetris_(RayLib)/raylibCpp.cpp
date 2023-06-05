#include "raylibCpp.h"
#include <assert.h>

// Checks if data valid and delegate call to raylib draw
void raycpp::DrawRectangle(Vec2<int> pos, Vec2<int> widthHeight, Color color)
{
	assert(pos.GetX() >= 0 && pos.GetY() >= 0 &&
		pos.GetX() < GetScreenWidth() && pos.GetY() < GetScreenHeight()); // x or y beyond screen
	DrawRectangle(pos.GetX(), pos.GetY(), widthHeight.GetX(), widthHeight.GetY(), color);
}

// Checks if data valid and delegate call to raylib draw
void raycpp::DrawRectangleLinesEx(Vec2<int> pos, Vec2<int> widthHeight, int lineThick, Color color)
{
	assert(pos.GetX() >= 0 && pos.GetY() >= 0 &&
		pos.GetX() < GetScreenWidth() && pos.GetY() < GetScreenHeight()); // x or y beyond screen
	assert(lineThick > 0);												  // linethick is too small
	DrawRectangleLinesEx(
		{
			(float) pos.GetX(),
			(float) pos.GetY(),
			(float) widthHeight.GetX(), 
			(float) widthHeight.GetY() 
		}, 
		(float) lineThick,
		color);
}
