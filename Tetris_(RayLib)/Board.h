#pragma once
#include <vector>
#include "raylibCpp.h"
#include "Vec2.h"

/** Board is a grid of cells with form of rectangles,
 *  Cells are activated (become visible) to simulate tetrominos.
 */
class Board
{
private:
	class Cell
	{
	public:
		Cell() = default;
		void SetActive() { isActive = true; }
		void SetColor(Color c_in);
		void Disable();
		bool Exists() const;
		Color GetColor() const;

	private: 

		bool isActive{ false };
		Color c{ WHITE };
	};
public:
	Board(Vec2<int> screenPos, Vec2<int> widthHeight, 
		int cellSize, int padding, int borderSize, Color borderColor);
	
	// Draw
	void Draw() const;
	void DrawBorder() const;
	void DrawCell(Vec2<int> pos) const;
	void DrawCell(Vec2<int> pos, Color color) const;

	// Board operations
	void Clear();
	void MoveDownRows(Vec2<int> pos);
	void RemoveRow(Vec2<int> pos);
	
	// Checks
	bool CellExists(Vec2<int> pos) const;
	bool CheckForFill(Vec2<int> pos) const;
	
	// Get
	int GetHeight() const;
	int GetWidth() const;

	// Set
	void SetExists(Vec2<int> pos, Color color);
	void SetCell(Vec2<int> pos, Color c);

private:
	inline void AssertPosition(Vec2<int> pos) const;

	std::vector<Cell> cells;

	Vec2<int> screenPos;
	Color borderColor;

	const int width;
	const int height;
	const int padding;
	const int cellSize;
	const int borderSize;
};

// Cells
inline void Board::Cell::Disable()
{
	isActive = false;
}

inline bool Board::Cell::Exists() const
{
	return isActive;
}

inline Color Board::Cell::GetColor() const
{
	return c;
}


// Board
inline int Board::GetWidth() const
{
	return width;
}

inline int Board::GetHeight() const
{
	return height;
}
