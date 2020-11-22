#include "Location.h"
#include <vector>
#include "Tile.h"
#include "macros.h"
#include "Board.h"
#include <math.h>

std::vector<int> CalculatePath(Location& from, Location& to, int ranking,  Board& board);
void get_around(const Tile& curr_tile, std::vector<Tile>& arround, const std::vector<Tile> closed_list, Board& board, int idex_of_father);
bool check_validity(Tile curr_tile, const std::vector<Tile> closed_list, bool y_axis);
void calculate_score(const std::vector<Tile> arround, const Location& to, int h_score);
int calculate_g_value(const Location& from, const Location& to);
int check_if_tile_in_open(Tile tile, const std::vector<Tile>& open_list);
int find_the_best_score(std::vector<Tile> openlist);
int ending_tile_in_open(const std::vector<Tile>& open_list, Tile end_tile);
std::vector <int> make_path(std::vector < Tile> closed, Tile to);



