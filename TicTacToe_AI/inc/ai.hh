#pragma once

#include "../inc/tictactoe.hh"

class ai {
    private:
    int x;
    int y;
    int ai_depth;

    public:
    ai() {}
    ai(int set_depth) { ai_depth = set_depth; x = 0; y = 0; }
    ~ai() {}
    int minimax(tictactoe *board, int depth, int alpha, int beta, bool maximizing);
    int get_move(tictactoe *board);
    int _x() { return x; }
    int _y() { return y; }
};