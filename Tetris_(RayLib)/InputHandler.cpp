#include "InputHandler.h"

InputHandler* InputHandler::handler = nullptr;

/** Assign every button a command. */
InputHandler::InputHandler()
	:
	buttonA_(new MoveLeftCommand()),
	buttonD_(new MoveRightCommand()),
	buttonE_(new RotateClockWiseCommand()),
	buttonQ_(new RotateCounterClockWiseCommand())
{

}

/** Make sure that there is one instance of input handler. */
InputHandler* InputHandler::GetInstance()
{
	// C++ 11 variant, I've read that is thread safer, 
	// but in this case it doesn't make a lot of sense
	//static InputHandler* instance = new InputHandler();
	//return instance;

	if (handler == nullptr) {
		handler = new InputHandler();
	}
	return handler;
}

// the easiest way, just to proceed through keys and their commands.
void InputHandler::handleTetromino(Tetromino* tetromino)
{
	if (IsKeyPressed(KEY_A)) buttonA_->execute(tetromino);
	else if (IsKeyPressed(KEY_D)) buttonD_->execute(tetromino);
	else if (IsKeyPressed(KEY_Q)) buttonQ_->execute(tetromino);
	else if (IsKeyPressed(KEY_E)) buttonE_->execute(tetromino);
}

// Clears commands
InputHandler::~InputHandler()
{
	delete buttonA_;
	delete buttonD_;
	delete buttonE_;
	delete buttonQ_;
}
