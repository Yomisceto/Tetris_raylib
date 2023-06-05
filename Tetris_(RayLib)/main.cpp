#include "Game.h"
#include "Settings.h"

/** Mini Tetris Game, made with raylib 
 * 05/06/2023 
 */
int main(void)
{
    Game tetris{ 
        settings::screenWidth, 
        settings::screenHeight, 
        settings::fps , 
        "Mini Tetris"
    };

    //SetWindowIcon();

    tetris.Run();
   
    return 0;
}
