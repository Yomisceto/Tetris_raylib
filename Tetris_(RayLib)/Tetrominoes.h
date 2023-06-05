#pragma once
#include <assert.h>
#include <functional>
#include "Vec2.h"
#include "raylibCpp.h"
#include "Board.h"

/**  Tetromino is array of active(disabled) values.
 *	 Each array transformed to 2d box, and index is counted according to dimension.
 *	 From that data it can be displayed on board.
 */
class Tetromino
{
public:
	/** Rotation changes index formula*/
	enum class Rotation
	{
		UP,
		RIGHT,
		DOWN,
		LEFT
	};

	Tetromino(const bool* shape, int dimension, Color color, Board* board);
	
	void Draw() const;

	/** User can only try to move Tetromino, return true is moved. 
	*   Its safer, as user can't go out of bounds. 
	*/
	bool TryRotateClockWise();
	bool TryRotateCounterClockWise();
	bool TryMoveDown();
	bool TryMoveRight();
	bool TryMoveLeft();

	bool isCollide() const;

	void SetBoard(Board* board_);

	int GetDimension() const { return dimension; }
	Vec2<int> GetPosition() { return boardPos; }

	/** Let's user know which cells currently active. */
	std::vector<Vec2<int>> GetActiveCellPositions() const;

private:
	void SetPosition(const Vec2<int>& pos) { boardPos = pos; }

	/** Check for tetromino moves. */
	bool CanRotate(int posX, int posY, Rotation newRotation) const;
	bool CanMoveLeft(int step = 1) const;
	bool CanMoveRight(int step = 1) const;

	/** Tries to rotate tetromino with shifting
	*   when no space for rotation, or it will be out of bounds. */
	bool TryKickRotation(Vec2<int> pos, Rotation newRotation, bool ClockWise = true);

	/** Changes tetromino position on board, shoould be called only when it's safe. */
	void MoveRight(int amount = 1);
	void MoveDown(int amount = 1);
	void MoveLeft(int amount = 1);
	void RotateClockwise();
	void RotateCounterClockWise();
	
	/** Checks if cell on board is activated. */
	bool IsCellActive(const int& x, const int& y, Rotation rotation) const;

	/** Helper function to procceed each cell of tetromino. */
	template <typename Action>
	void ForEachCell(Action&& action, const bool& shoudNotEnd = true) const;

	const bool* shape;
	const int dimension;
	const Color color;
	Rotation currentRotation;
	Vec2<int> boardPos;
	Board* board;
};

/** Now we can create different shapes and just decribe its details. */

class Straight : public Tetromino
{
public:
	explicit Straight(Board* board)
		:
		Tetromino(shape, dimension, color, board)
	{
		static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension);
	}
private:
	static constexpr bool shape[] = { 0,0,0,0,
									  1,1,1,1,
									  0,0,0,0,
									  0,0,0,0 };
	static constexpr int dimension = 4;

	static constexpr Color color = SKYBLUE;
};

class Square : public Tetromino
{
public:
	explicit Square(Board* board)
		:
		Tetromino(shape, dimension, color, board)
	{
		static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension);
	}
private:
	static constexpr bool shape[] = { 1,1,
									  1,1 };
	static constexpr int dimension = 2;
	static constexpr Color color = YELLOW;
};

class Tee : public Tetromino
{
public:
	explicit Tee(Board* board)
		:
		Tetromino(shape, dimension, color, board)
	{
		static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension);
	}
private:
	static constexpr bool shape[] = { 0,1,0,
									  1,1,1,
									  0,0,0 };
	static constexpr int dimension = 3;
	static constexpr Color color = MAGENTA;
};

class Jay : public Tetromino
{
public:
	explicit Jay(Board* board)
		:
		Tetromino(shape, dimension, color, board)
	{
		static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension);
	}
private:
	static constexpr bool shape[] = { 1,0,0,
									  1,1,1,
									  0,0,0 };
	static constexpr int dimension = 3;
	static constexpr Color color = DARKBLUE;
};

class El : public Tetromino
{
public:
	explicit El(Board* board)
		:
		Tetromino(shape, dimension, color, board)
	{
		static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension);
	}
private:
	static constexpr bool shape[] = { 0,0,1,
									  1,1,1,
									  0,0,0 };
	static constexpr int dimension = 3;
	static constexpr Color color = ORANGE;
};

class SkewS : public Tetromino
{
public:
	explicit SkewS(Board* board)
		:
		Tetromino(shape, dimension, color, board)
	{
		static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension);
	}
private:
	static constexpr bool shape[] = { 0,1,1,
									  1,1,0,
									  0,0,0 };
	static constexpr int dimension = 3;
	static constexpr Color color = GREEN;
};

class SkewZ : public Tetromino
{
public:
	explicit SkewZ(Board* board)
		:
		Tetromino(shape, dimension, color, board)
	{
		static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension);
	}
private:
	static constexpr bool shape[] = { 1,1,0,
									  0,1,1,
									  0,0,0 };
	static constexpr int dimension = 3;
	static constexpr Color color = RED;
}; 

class OneXFive : public Tetromino
{
public:
	explicit OneXFive(Board* board)
		:
		Tetromino(shape, dimension, color, board)
	{
		static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension);
	}
private:
	static constexpr bool shape[] = { 0,0,1,0,0,
									  0,0,1,0,0,
									  0,0,1,0,0,
									  0,0,1,0,0,
									  0,0,1,0,0 };
	static constexpr int dimension = 5;
	static constexpr Color color = LIGHTGRAY;
};

class T : public Tetromino
{
public:
	explicit T(Board* board)
		:
		Tetromino(shape, dimension, color, board)
	{
		static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension);
	}
private:
	static constexpr bool shape[] = { 0,1,0,
									  0,1,0,
									  1,1,1};
	static constexpr int dimension = 3;
	static constexpr Color color = LIGHTGRAY;
};


/** For each cell takes function,
*   and a optional boolean to end loop when no need to continue.
*/
template <typename Action>
void Tetromino::ForEachCell(Action&& action, const bool& shoudNotEnd) const
{
	for (int y = 0; y < dimension; ++y)
	{
		for (int x = 0; x < dimension; ++x)
		{
			action(x, y);

			if (!shoudNotEnd) return;
		}
	}
}
