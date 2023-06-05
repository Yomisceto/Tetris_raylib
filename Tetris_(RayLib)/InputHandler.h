#pragma once
#include "Command.h"
#include "Game.h"


/** InputHandler stores commands and bind it to keys.
 *  Class is Singleton, just because one user instance is expected,
 *  but it looses flexibility.
 */
class InputHandler
{
public:
	static InputHandler* GetInstance();

	InputHandler(InputHandler& other) = delete;
	void operator=(const InputHandler&) = delete;
	
	void handleTetromino(Tetromino* tetromino);

	~InputHandler();

protected:
	InputHandler();

	static InputHandler* handler;

private:
	/** In fact that can be any button, so better to rename it. */
	Command* buttonA_;
	Command* buttonD_;
	Command* buttonE_;
	Command* buttonQ_;
	
	Command* buttonS_;
	
	Command* buttonEsc_;
	Command* buttonEnter_;
};
