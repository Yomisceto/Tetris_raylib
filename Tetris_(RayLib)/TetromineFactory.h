#pragma once
#include <random>
#include "Tetrominoes.h"

/** Class that creates instances of Tetrominos.
 *  Also provides a way to generate a random tetromino.
 */
class TetromineFactory
{
public:
	/** As tetromino is binded to board, we should provide it. */
	explicit TetromineFactory(Board* board);

	// creates random tetromino 
	Tetromino* createTetromine();

private:
	Board* board;

	// Stores all possible tetrominos creation methods.
	std::vector<Tetromino* (TetromineFactory::*)()> functionPointer;

	Tetromino* createStraight();
	Tetromino* createSquare();
	Tetromino* createTee();
	Tetromino* createJay();
	Tetromino* createEl();
	Tetromino* createSkewS();
	Tetromino* createSkewZ();
	Tetromino* createT();

	// For random generation
	std::default_random_engine engine;
	std::uniform_int_distribution<int> uniform_dist;
};
