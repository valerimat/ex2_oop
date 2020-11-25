//===========Include section============
#include <iostream>
#include <cstdlib> // for std::system()
#include "io.h"
#include "Board.h"
#include "Game_handler.h"


//=============Main section=============
int main()
{
    Board board;    
    Game_Handler game(board);

    // the main function
    game.Run_game();
  
    return EXIT_SUCCESS;
}
//----------------------------------------------------------------------------
