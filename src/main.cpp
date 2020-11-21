#include <iostream>
#include <cstdlib> // for std::system()
#include "io.h"
#include "Board.h"
#include "Game_handler.h"


int main()
{
  
    Board board;
    Game_Handler game(board);
    game.Run_game();
    
    return EXIT_SUCCESS;
}
