#include "Tetrominoes.h"

Tetromino::Tetromino(const bool* shape, int dimension,
	Color color, Board* board)
	:
	shape(shape),
	dimension(dimension),
	color(color),
	currentRotation(Rotation::UP),
	boardPos({0,0}),
	board(board)
{
	
}

//
void Tetromino::SetBoard(Board* board_)
{
	board = board_;
	boardPos = Vec2<int>{ board->GetWidth() / 2 - dimension / 2, 0 };
}

// Draw
void Tetromino::Draw() const
{
	ForEachCell([this](int x, int y) {
		if (IsCellActive(x, y, currentRotation))
		{
			board->DrawCell(boardPos + Vec2<int>{x, y}, color);
		}
		}
	);
}

bool Tetromino::isCollide() const
{
	bool notCollide = true;
	ForEachCell([this, &notCollide](int x, int y)
		{
			if (IsCellActive(x, y, currentRotation) 
				&& board->CellExists(boardPos + Vec2<int>{x, y}))
			{
				notCollide =  false;
			}
		}
	, notCollide);

	return notCollide;
}

std::vector<Vec2<int>> Tetromino::GetActiveCellPositions() const
{
	std::vector<Vec2<int>> activeCellPositions;

	ForEachCell([this, &activeCellPositions](int x, int y) {
		if (IsCellActive(x, y, currentRotation)) 
		{
			activeCellPositions
				.emplace_back(boardPos.GetX() + x, boardPos.GetY() + y);
		}
		});

	return activeCellPositions;
}

// Cells
bool Tetromino::IsCellActive(const int& x, const int& y, Rotation rotation) const
{
	// this formulas transform indexes to its rotation
	switch (rotation)
	{
	case Tetromino::Rotation::UP:    return shape[y * dimension + x];
	case Tetromino::Rotation::RIGHT: return shape[dimension * (dimension - 1) - dimension * x + y];
	case Tetromino::Rotation::DOWN:  return shape[(dimension * dimension - 1) - dimension * y - x];
	case Tetromino::Rotation::LEFT:  return shape[(dimension - 1) + dimension * x - y];
	default: return false;
	}
}

// Tries to make a move, return false if not possible
bool Tetromino::TryMoveDown()
{
	auto newPos = Vec2<int>(boardPos.GetX(), boardPos.GetY() + 1);

	bool canMoveDown = true;

	ForEachCell([this,&canMoveDown, &newPos](int x, int y)
		{
			if (!IsCellActive(x, y, currentRotation)) return;

			if (newPos.GetY() + y >= board->GetHeight() ||
				board->CellExists(newPos + Vec2<int>{x, y}) )
			{
				canMoveDown = false;
				return;
			}
		}
	);

	if (canMoveDown)
	{
		MoveDown();
	}

	return canMoveDown;
}
bool Tetromino::TryMoveRight()
{
	bool canMove = CanMoveRight();

	if (canMove)
	{
		MoveRight();
	}

	return canMove;
}
bool Tetromino::TryMoveLeft()
{
	bool canMove = CanMoveLeft();

	if (canMove) 
	{
		MoveLeft();
	}

	return canMove;
}
bool Tetromino::TryRotateClockWise()
{
	auto newRotation = Rotation((int(currentRotation) + 1) % 4);
	
	bool canRotate = CanRotate(boardPos.GetX(), boardPos.GetY(), newRotation);

	if (canRotate)
	{
		RotateClockwise();
	}
	else
	{
		canRotate = TryKickRotation(Vec2<int>{ boardPos.GetX(),boardPos.GetY()}, 
			newRotation);
	}

	return canRotate;
}
bool Tetromino::TryRotateCounterClockWise()
{
	auto newRotation = currentRotation == Rotation::UP 
		? Rotation::LEFT : Rotation((int(currentRotation) - 1) % 4);

	bool canRotate = CanRotate(boardPos.GetX(), boardPos.GetY(), newRotation);

	if (canRotate)
	{
		RotateCounterClockWise();
	}
	else
	{
		canRotate = TryKickRotation(Vec2<int>{ boardPos.GetX(), boardPos.GetY()},
			newRotation, false);
	}

	return canRotate;
}
bool Tetromino::TryKickRotation(Vec2<int> pos, Rotation newRotation, bool ClockWise)
{
	bool canRotate = false;

	/**
	* Checks offset X position for tetromino,
	* figure can be offset by maximum dimension - 1 
	* (for example 1 x 5 piece, can be moved max by 4)
	*/ 
	for (int x = 1; x < dimension - 1; ++x)
	{
		// Check both sides -x and +x
		if (CanRotate(pos.GetX() - x, pos.GetY(), newRotation))
		{
			MoveLeft(x);
			canRotate = true;
		}
		else if (CanRotate(pos.GetX() + x, pos.GetY(), newRotation))
		{
			MoveLeft(-x);	
			canRotate = true;
		}

		if (canRotate)
		{
			if (ClockWise) RotateClockwise();
			else RotateCounterClockWise(); 
			return canRotate;
		}
	}

	return canRotate;
}

// Checks is move is possible
bool Tetromino::CanMoveRight(int step) const 
{
	bool canMoveRight = true;

	auto newPos = Vec2<int>(boardPos.GetX() + step, boardPos.GetY());

	ForEachCell([this,&newPos,&canMoveRight](int x, int y)
		{
			if (!IsCellActive(x, y, currentRotation)) return;

			if (newPos.GetX() + x >= board->GetWidth() || 
				board->CellExists(newPos + Vec2<int>{x, y}))
			{
				canMoveRight = false;
				return;
			}
		}
	);

	return canMoveRight;
}
bool Tetromino::CanMoveLeft(int step) const 
{
	bool canMoveLeft = true;

	auto newPos = Vec2<int>(boardPos.GetX() - step, boardPos.GetY());

	ForEachCell([this, &canMoveLeft, &newPos](int x, int y)
		{
			if (!IsCellActive(x, y, currentRotation)) return;

			if (newPos.GetX() + x < 0 ||
				board->CellExists(newPos + Vec2<int>{x, y}))
			{
				canMoveLeft = false;
				return;
			}
		}
	);

	return canMoveLeft;
}
bool Tetromino::CanRotate(int posX, int posY, Rotation newRotation) const
{
	bool canRotate = true;

	ForEachCell([this, &newRotation, &posX, &posY, &canRotate](int x, int y)
		{
			// Not active cells should not be checked
			if (!IsCellActive(x, y, newRotation)) return;
			
			// Checks bound of board
			if (posX + x < 0 || posX + x >= board->GetWidth()
				|| posY + y < 0 || posY + y >= board->GetHeight())
			{
				canRotate = false;
				return;
			}

			// In bounds of board check if not active cells overlap
			if (board->CellExists(Vec2<int>{posX,posY} + Vec2<int>{x, y}))
			{
				canRotate = false;
				return;
			}

		}
	, canRotate);

	return canRotate;
}


// Change position of tetromino
void Tetromino::MoveRight(int amount)
{
	SetPosition(Vec2<int>{boardPos.GetX() + amount, boardPos.GetY()});
}
void Tetromino::MoveLeft(int amount)
{
	SetPosition(Vec2<int>{boardPos.GetX() - amount, boardPos.GetY()});
}
void Tetromino::MoveDown(int amount)
{
	SetPosition(Vec2<int>{boardPos.GetX(), boardPos.GetY() + amount});
}

void Tetromino::RotateClockwise()
{
	// 4 rotation is possible
	currentRotation = Rotation( (int(currentRotation) + 1) % 4 );
}
void Tetromino::RotateCounterClockWise()
{
	// UP is 0, so check for negative value
	currentRotation = currentRotation == Rotation::UP ?
		Rotation::LEFT : Rotation((int(currentRotation) - 1) % 4);
}
