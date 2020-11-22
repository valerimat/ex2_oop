#pragma once

struct Location
{
    explicit Location(int row, int col) : row(row), col(col) {}
    bool operator==(Location& location)const;
    bool operator!=(Location& location)const;
    int row;
    int col;
    void update_based_on_key(int key);
};
