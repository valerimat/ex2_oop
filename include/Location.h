#pragma once

struct Location
{
    explicit Location(int row, int col) : row(row), col(col) {}
    int row;
    int col;
    void update_based_on_key(int key);
};
