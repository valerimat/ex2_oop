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


bool Location::operator==(Location& location)const {
    if (this->col == location.col && this->row == location.row)
        return true;

    return false;

};

bool Location::operator!=(Location& location)const {
    if (this->col == location.col && this->row == location.row)
        return false;

    return true;

};