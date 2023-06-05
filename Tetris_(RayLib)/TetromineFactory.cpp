#include "TetromineFactory.h"
#include "Board.h"
#include <assert.h>

TetromineFactory::TetromineFactory(Board* board)
    :
    board(board),
    engine(time(0)),
    uniform_dist(0,6)
{  
    functionPointer.push_back(&TetromineFactory::createStraight);
    functionPointer.push_back(&TetromineFactory::createSquare);
    functionPointer.push_back(&TetromineFactory::createTee);
    functionPointer.push_back(&TetromineFactory::createJay);
    functionPointer.push_back(&TetromineFactory::createEl);
    functionPointer.push_back(&TetromineFactory::createSkewS);
    functionPointer.push_back(&TetromineFactory::createSkewZ);

    //functionPointer.push_back(&TetromineFactory::createT);
    
    // Check to see if our random generator not out of bounds
    assert(uniform_dist.max() <= functionPointer.size() - 1);
}

// calls random create function from a vector of function pointetrs.
Tetromino* TetromineFactory::createTetromine()
{
    int num = uniform_dist(engine);
    return (this->*functionPointer[num])();  
}

// Just returns new Tetromino constructed
Tetromino* TetromineFactory::createStraight()
{
    return new Straight(board);
}

Tetromino* TetromineFactory::createSquare()
{
    return new Square(board);
}

Tetromino* TetromineFactory::createTee()
{
    return new Tee(board);
}

Tetromino* TetromineFactory::createJay()
{
    return new Jay(board);
}

Tetromino* TetromineFactory::createEl()
{
    return new El(board);
}

Tetromino* TetromineFactory::createSkewS()
{
    return new SkewS(board);
}

Tetromino* TetromineFactory::createSkewZ()
{
    return new SkewZ(board);
}

Tetromino* TetromineFactory::createT()
{
    return new T(board);
}
