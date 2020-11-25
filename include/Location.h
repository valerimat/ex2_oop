#pragma once

// Location struct
struct Location
{
    explicit Location(int row, int col) : row(row), col(col) {}

    bool operator==(Location& location)const;
    bool operator!=(Location& location)const;

    void update_based_on_key(int key);

    // members
    int row;
    int col;
    
};
