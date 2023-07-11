#pragma once

#include <iostream>
#include <algorithm>

class tictactoe {
    private:

    int size;
    int to_win; 
    int **state_matrix;

    public:
    tictactoe(){};
    tictactoe(const int size, const int to_win);
    ~tictactoe();
    void print_board() const;
    bool is_field_occupied(const int x, const int y) const;
    bool set_field(const int x, const int y, const int player);
    void remove_field(const int x, const int y);
    bool is_full() const;
    int check_game_state() const;
    int get_size() const { return size; }
    int get_to_win() const { return to_win; }
    int check_neighbors(int x, int y, int player);
};