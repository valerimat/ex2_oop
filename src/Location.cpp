//======include header======
#include "Location.h"
#include "io.h"

// updates the location based on key pressed by the KB
void Location::update_based_on_key(int key)
{
    if (key == KB_UP) // up
        row--;
    if (key == KB_DOWN) // down
        row++;
    if (key == KB_LEFT) // left
        col--;
    if (key == KB_RIGHT) // right
        col++;
}
//----------------------------------------------------------------------------

// operator == function, checks if the locations are the same
bool Location::operator==(Location& location)const {
    if (this->col == location.col && this->row == location.row)
        return true;

    return false;

};
//----------------------------------------------------------------------------

// operator != function, checks if the locations aren't the same
bool Location::operator!=(Location& location)const {
    if (this->col == location.col && this->row == location.row)
        return false;

    return true;
};
//----------------------------------------------------------------------------