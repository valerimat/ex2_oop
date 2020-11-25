//.......include section.......
#include <iostream>
#include <cstdlib> // for std::system()
#include "io.h"
#include "Board.h"
#include "Game_handler.h"

//.......main section.......
int main()
{
    Board board;    
    Game_Handler game(board);
    game.Run_game();
    board.print_board();
    
    return EXIT_SUCCESS;
}
