#include <iostream>
#include <cstdlib> // for std::system()
#include "io.h"
#include "Board.h"



int main()
{
    //std::system("cls");
    //Screen::resetLocation();

    Board board;
    board.print_board();

    std::cout << board.get_location_of_player().row << " , " << board.get_location_of_player().col << std::endl;
    std::cout << board.get_height() << std::endl;
    std::cout << board.get_width() << std::endl;
    std::cout << board.is_above_ground() << std::endl;
    
    return EXIT_SUCCESS;
}
