#include "Game.h"
#include <assert.h>
#include "raylibCpp.h"
#include "Settings.h"
#include <iostream>
#include "InputHandler.h"

Game::Game(int width, int height, int fps, const std::string& title)
	:
	// should not init in constuctor
	board(
		settings::boardPosition,
		settings::boardWidthHeight,
		settings::cellSize,
		settings::padding,
		settings::cellSize / 2,
		settings::borderColor
	),
	previewBoard(
		settings::previewBoardPos,
		settings::previewBoardSize,
		settings::previewCellSize,
		settings::previewPadding,
		0,
		settings::previewBorderColor
	),
	gameStartText(Vec2<int>(90,300),
		"Press 'R' to Start",
		settings::fontSize,
		settings::textColor),

	gameOverText(Vec2<int>(350, 350),
		"GAME OVER",
		settings::fontSize,
		settings::textColor),

	restartText(Vec2<int>(350,400),
		"Press 'R'\nto Restart",
		settings::fontSize,
		settings::textColor),

	pauseText(
		settings::pausePos,
		"Paused",
		settings::fontSize,
		settings::textColor),

	hintText(
		settings::hintPos,
		settings::hintText,
		settings::fontSize,
		settings::textColor),

	scoreDisplay(
		settings::scorePos,
		"Score: %04i",
		settings::fontSize,
		settings::textColor,
		&score
	),

	score(0),
	factory(&previewBoard), 
	currentTetromino(nullptr),
	nextTetromino(factory.createTetromine()),
	inputHandler(InputHandler::GetInstance())
{
	// triggers when windows is already opened.
	assert(!GetWindowHandle());

	SetTargetFPS(fps);

	InitWindow(width, height, title.c_str());

	state = State::START;

}

/** made noexcept due to stack unwinding */
Game::~Game() noexcept
{
	// triggers windows is already closed.
	assert(GetWindowHandle()); 
	CloseWindow();
}

void Game::Run()
{
	while (!GameShouldClose())
	{
		Tick();
	}
}

void Game::Draw()
{
	ClearBackground(settings::BackgroundColor);
	DrawFPS(settings::fpsPos.GetX(), settings::fpsPos.GetY());

	scoreDisplay.Draw();

	previewBoard.Draw();
	board.Draw();
	
	nextTetromino->Draw();

	// Not running, no current tetromino present for drawing
	if (currentTetromino && state == State::RUNNING)
	{
		currentTetromino->Draw();
		hintText.Draw();
	}
	else if (state == State::GAMEOVER)
	{
		gameOverText.Draw();
		restartText.Draw();
	}
	else if (state == State::START)
	{
		gameStartText.Draw();
	}
	else if (state == State::PAUSE)
	{
		pauseText.Draw();
	}	
}
void Game::Tick()
{
	BeginDrawing();
	
	Update();	
	Draw();
	
	EndDrawing();
}
void Game::Update()
{
	if (state == State::RUNNING)
	{
		// If there is tetromino that can be controlled
		if (currentTetromino)
		{
			inputHandler->handleTetromino(currentTetromino);
		}

		if (IsKeyPressed(KEY_SPACE)) {
			state = State::PAUSE;
		}

		if (IsKeyDown(KEY_S))
		{
			framesElapsed = ++framesElapsed % 2;
		}
		else
		{
			framesElapsed = ++framesElapsed % tetrominoRefreshRate;
		}

		// Zero means it's time to update tetromino
		if (framesElapsed == 0)
		{
			UpdateCurrentTetromino();
		}
	}

	else if (state == State::GAMEOVER)
	{
		if (IsKeyPressed(KEY_R))
		{
			RestartGame();
		}
	}

	else if (state == State::START)
	{
		if (IsKeyPressed(KEY_R))
		{
			StartGame();
		}
	}
	else if (state == State::PAUSE)
	{
		if (IsKeyPressed(KEY_SPACE)) 
		{
			state = State::RUNNING;
		}
	}

}

void Game::UpdateCurrentTetromino()
{
	// Checks if there is tetromino and it can't be moved down
	// condition fails when tetromino can be moved, and it moves
	if (currentTetromino && !currentTetromino->TryMoveDown())
	{
		// Activates cells that on place of tetromino
		SetTetrominoOnBoard();

		delete currentTetromino;
		currentTetromino = nullptr;
	}

	if (currentTetromino == nullptr)
	{
		currentTetromino = nextTetromino;
		currentTetromino->SetBoard(&board);
		nextTetromino = new Straight(&previewBoard);// = factory.createTetromine();

		// Check if new tetromino can be spawned
		if (!TetrominoCanSpawn())
		{
			delete currentTetromino;
			currentTetromino = nullptr;
			state = State::GAMEOVER;
		}
	}
}
void Game::SetTetrominoOnBoard()
{
	std::vector<Vec2<int>> cellsPos(currentTetromino->GetActiveCellPositions());
	int clearedRows = 0;

	for (const auto& cellPos : cellsPos)
	{
		board.SetExists(cellPos, WHITE);

		if (board.CheckForFill(cellPos))
		{
			board.RemoveRow(cellPos);
			board.MoveDownRows(cellPos);
			++clearedRows;
		}
	}

	if (clearedRows > 0)
	{
		int toScore = settings::scorePerRow;

		for (int i = 2; i <= clearedRows; ++i)
		{
			toScore += settings::scorePerRow;
			toScore *= i;
		}

		IncreaseScore(toScore);
	}
}
bool Game::TetrominoCanSpawn() const
{
	return currentTetromino->isCollide();
}

void Game::RestartGame()
{
	board.Clear();
	delete nextTetromino;

	currentTetromino = factory.createTetromine();
	currentTetromino->SetBoard(&board);

	nextTetromino = factory.createTetromine();

	state = State::RUNNING;
}
void Game::StartGame()
{
	state = State::RUNNING;
}

void Game::ResetScore()
{
	score = 0;
}
void Game::IncreaseScore(int scoreToAdd)
{
	score += scoreToAdd;
}
