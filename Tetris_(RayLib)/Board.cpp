#include "Board.h"
#include <assert.h>
#include <iostream>

// Cell
void Board::Cell::SetColor(Color c_in)
{
	c = c_in;
	isActive = true;
}

// Board 
Board::Board(Vec2<int> screenPos, Vec2<int> widthHeight,
	int cellSize, int padding, int borderSize, Color borderColor)
	:
	screenPos(screenPos),
	borderColor(borderColor),
	width(widthHeight.GetX()),
	height(widthHeight.GetY()),
	padding(padding),
	cellSize(cellSize),
	borderSize(borderSize)
{
	/** unlike reserve calls constructor for each cell. */
	assert(width > 0 && height > 0);	// the width or height smaller than 1
	assert(cellSize > 0);				// the cell size is smaller than 1
	cells.resize(width * height);	
}

/** Board cell index is counted by formula 'index = y * width + x'
*	So 1D array is transformed to 2D coordinates.
*/ 

// Board Draw
void Board::Draw() const
{
	for (int iY = 0; iY < height; ++iY)
	{
		for (int iX = 0; iX < width; ++iX)
		{
			if (CellExists({ iX,iY })) {
				DrawCell(Vec2<int>{ iX, iY });
			}
		}
	}
	
	DrawBorder();
}
void Board::DrawBorder() const
{
	if (borderSize > 0)
	{
		raycpp::DrawRectangleLinesEx(
			screenPos - (cellSize / 2),
			Vec2<int>{ width* cellSize, height* cellSize } + cellSize,
			borderSize,
			borderColor);
	}
	
}
void Board::DrawCell(Vec2<int> pos) const
{
	AssertPosition(pos);
	Color color = cells[pos.GetY() * width + pos.GetX()].GetColor();
	DrawCell(pos, color);
}
void Board::DrawCell(Vec2<int> pos, Color color) const
{
	// x or y out of board bounds 
	assert(pos.GetX() >= 0 && pos.GetX() < width && pos.GetY() >= 0 && pos.GetY() < height); 

	Vec2<int> topLeft = screenPos + padding + (pos * cellSize);
	raycpp::DrawRectangle(topLeft, Vec2<int>{ cellSize, cellSize } - padding, color);
}

// Board operations
void Board::Clear()
{
	for (auto& cell : cells)
	{
		cell.Disable();
	}
}
void Board::RemoveRow(Vec2<int> pos)
{
	AssertPosition(pos);
	for (int iX = 0; iX < width; ++iX)
	{ 
		cells[pos.GetY() * width + iX].Disable();
	}
}
void Board::MoveDownRows(Vec2<int> pos)
{
	AssertPosition(pos);
	// Move down all rows above current
	for (int iY = pos.GetY() - 1; iY >= 0; --iY)
	{
		for (int iX = 0; iX < width; ++iX)
		{
			if (CellExists({ iX,iY })) {

				// Just disables cell and enable one below it.
				int i = iY * width + iX;
				cells[i].Disable();
				cells[i + width].SetActive();
			}
		}
	}
}

// Board Set
void Board::SetExists(Vec2<int> pos, Color color)
{
	AssertPosition(pos);
	int index = pos.GetY() * width + pos.GetX();
	cells[index].SetColor(color);
}
void Board::SetCell(Vec2<int> pos, Color c)
{
	AssertPosition(pos);
	cells[pos.GetY() * width + pos.GetX()].SetColor(c);
}

// Board Checks
bool Board::CheckForFill(Vec2<int> pos) const
{
	AssertPosition(pos);
	// Check for fill in current Y position
	for (int iX = 0; iX < width; ++iX)
	{
		if (!(CellExists({ iX,pos.GetY() }))) {
			return false;
		}
	}

	return true;
}

// returns false if cell disabled or if out of board
bool Board::CellExists(Vec2<int> pos) const
{
	AssertPosition(pos);
	return cells[pos.GetY() * width + pos.GetX()].Exists();
}

// checks if x or y out of board bounds
void Board::AssertPosition(Vec2<int> pos) const
{
	assert(pos.GetX() >= 0 && pos.GetX() < width && pos.GetY() >= 0 && pos.GetY() < height);
}
