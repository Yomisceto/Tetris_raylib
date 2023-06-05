#pragma once
#include <string>
#include "Board.h"
#include "Tetrominoes.h"
#include "TetromineFactory.h"
#include "TextBox.h"


class Game
{
public:
	enum class State
	{
		START,
		RUNNING,
		PAUSE,
		GAMEOVER
	};

	Game(int width, int height, int fps, const std::string& title);
	Game(const Game& other) = delete; 
	Game& operator=(const Game& other) = delete;

	/** move members implicity deleted, because assign and copy deleted functions. */

	~Game() noexcept;

	void Run();

	bool GameShouldClose() const; 

private:
	// 
	inline void ResetScore();
	inline void IncreaseScore(int);
	inline bool TetrominoCanSpawn() const;

	// Update
	void Tick();
	void Update();
	void UpdateCurrentTetromino();

	// Draw
	void Draw();
	void SetTetrominoOnBoard();

	// Game manage
	void StartGame();
	void RestartGame();
	
	// TextBoxes
	TextBox gameStartText;
	TextBox gameOverText;
	TextBox restartText;
	TextBox pauseText;
	TextBox hintText;
	ValueDisplayer<int> scoreDisplay;

	// State of Game
	State state;

	// Boards
	Board board;
	Board previewBoard;

	// Input
	class InputHandler* inputHandler;

	// Tetromino
	TetromineFactory factory;
	Tetromino* currentTetromino;
	Tetromino* nextTetromino;

	// Score

	int score;

	// Times per frames to update tetromino 
	// the smallest value = quickest tetromino 
	int tetrominoRefreshRate = 10;
	
	int framesElapsed = 1;
};

inline bool Game::GameShouldClose() const
{
	return WindowShouldClose();
}
