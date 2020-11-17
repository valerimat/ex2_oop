#pragma once
#include "Location.h"


void  Location::update_based_on_key(int key)
{
    if (key == 119) // up
        row--;
    if (key == 115) // down
        row++;
    if (key == 97) // left
        col--;
    if (key == 100) // right
        col++;
}