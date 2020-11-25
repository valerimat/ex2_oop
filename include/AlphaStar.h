#pragma once

#include "Location.h"
#include <vector>
#include "Tile.h"
#include "macros.h"
#include "Board.h"
#include <math.h>

//==============================================================================
//   ______            ______   ________  ______   _______  
//  /      \          /      \ /        |/      \ /       \ 
// /$$$$$$  |        /$$$$$$  |$$$$$$$$//$$$$$$  |$$$$$$$  |
// $$ |__$$ | ______ $$ \__$$/    $$ |  $$ |__$$ |$$ |__$$ |
// $$    $$ |/      |$$      \    $$ |  $$    $$ |$$    $$< 
// $$$$$$$$ |$$$$$$/  $$$$$$  |   $$ |  $$$$$$$$ |$$$$$$$  |
// $$ |  $$ |        /  \__$$ |   $$ |  $$ |  $$ |$$ |  $$ |
// $$ |  $$ |        $$    $$/    $$ |  $$ |  $$ |$$ |  $$ |
// $$/   $$/          $$$$$$/     $$/   $$/   $$/ $$/   $$/
//==============================================================================

/*
Algorithm for calcluating shortest path for monsters
*/

// send locations and your board
std::vector<int> CalculatePath(Location& from, Location& to, Board& board);



//helper functions - for full documentation visit cpp
void get_around(const Tile& ,std::vector<Tile>& ,const std::vector<Tile>, Board&, int );

bool check_validity(Tile, std::vector<Tile>,Board& , enum Moves );

void calculate_score(std::vector<Tile>& ,const Location& ,int );

int calculate_g_value(const Location& ,const Location& );

int check_if_tile_in_vector(Tile ,const std::vector<Tile> );

int find_the_best_score(std::vector<Tile> );

void init_arround(std::vector<Tile>& ,const Location&,const Board& board,const std::vector<Tile>& ,int );

std::vector <int> make_path(std::vector<Tile> , Tile );





