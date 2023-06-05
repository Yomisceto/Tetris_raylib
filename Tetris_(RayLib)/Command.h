#pragma once
#include "Tetrominoes.h"

/** Commands are used to perform simple tetrominos movements.
 * 
 *  In case of simple tetris where player can't change (for now) keys
 *  it doesn't make a lot of sence,but it flexible. 
 */
class Command
{
public:
	Command() = default;
	virtual ~Command() = default;
	virtual void execute(Tetromino* tetromino) = 0;
};

class MoveRightCommand : public Command
{
public:
	using Command::Command;
	void execute(Tetromino* tetromino) override { tetromino->TryMoveRight(); }
};

class MoveLeftCommand : public Command
{
public:
	using Command::Command;
	void execute(Tetromino* tetromino) override { tetromino->TryMoveLeft(); }
};

class RotateClockWiseCommand : public Command
{
public:
	using Command::Command;
	void execute(Tetromino* tetromino) override { tetromino->TryRotateClockWise(); }
};

class RotateCounterClockWiseCommand : public Command
{
public:
	using Command::Command;
	void execute(Tetromino* tetromino) override { tetromino->TryRotateCounterClockWise(); }
};
