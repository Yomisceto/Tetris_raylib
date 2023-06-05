#pragma once
#include <raylib.h>
#include "Vec2.h"

// Raylib function addapter / wrapper to use Vec2
namespace raycpp
{
	void DrawRectangle(Vec2<int> pos, Vec2<int> widthHeight, Color color);
	void DrawRectangleLinesEx(Vec2<int> pos, Vec2<int> widthHeight, int lineThick, Color color);
}
