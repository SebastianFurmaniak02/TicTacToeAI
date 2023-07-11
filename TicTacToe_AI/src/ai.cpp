#include "../inc/ai.hh"



int infinity = 10000;

int ai::minimax(tictactoe *board, int depth, int alpha, int beta, bool maximizing) {
    int game_state = board->check_game_state();

    if (depth == 0 || abs(game_state) == 1000 || board->is_full()) return game_state;

    if (maximizing) {
        int maxEval = -infinity; 
        for(int i = 0; i < board->get_size(); i++) {
            for(int j = 0; j < board->get_size(); j++) {
                if (!board->is_field_occupied(i,j)) {
                    board->set_field(i,j,1);
                    maxEval = std::max(maxEval,minimax(board, depth-1, alpha, beta, false));
                    board->remove_field(i,j);
                    alpha = std::max(alpha, maxEval);
                    if (beta <= alpha) return alpha;
                }
            }
        }
        return maxEval;
    }
    else {
        int minEval = infinity;
        for(int i = 0; i < board->get_size(); i++) {
            for(int j = 0; j < board->get_size(); j++) {
                if (!board->is_field_occupied(i,j)) {
                    board->set_field(i,j,-1);
                    minEval = std::min(minEval,minimax(board,depth-1,alpha,beta,true));  
                    board->remove_field(i,j);
                    beta = std::min(beta,minEval);
                    if (beta <= alpha) return beta;
                }
            }
        }
        return minEval;
    }
}

int ai::get_move(tictactoe *board) {
    int minEval = infinity;
    int eval = infinity;
    for(int i = 0; i < board->get_size(); i++) {
        for(int j = 0; j < board->get_size(); j++) {
            if (!board->is_field_occupied(i,j)) {

                board->set_field(i,j,-1); 
                if (board->check_game_state() == -1000) { board->remove_field(i,j); x = i; y = j; return -1000; }
                board->remove_field(i,j);
                
                board->set_field(i,j,-1);
                eval = std::min(eval,minimax(board,ai_depth-1,-infinity, infinity, true));
                board->remove_field(i,j);
                if (eval < minEval) {
                    minEval = eval;
                    x = i;
                    y = j;
                }
            }
        }
    }
    if (minEval == 1000) {
        int depth = ai_depth-1;
        while (minEval == 1000 && depth != 0)
        {
            eval = infinity;
            minEval = infinity;
            for(int i = 0; i < board->get_size(); i++) {
                for(int j = 0; j < board->get_size(); j++) {
                    if (!board->is_field_occupied(i,j)) {

                        board->set_field(i,j,1); 
                        if (board->check_game_state() == 1000) { board->remove_field(i,j); x = i; y = j; return 1000; }
                        board->remove_field(i,j);
                        
                        board->set_field(i,j,-1);
                        eval = std::min(eval,minimax(board,depth,-infinity, infinity, true));
                        board->remove_field(i,j);
                        if (eval < minEval) {
                            minEval = eval;
                            x = i;
                            y = j;
                        }
                    }
                }
            }
            depth--;
        }
        return 1000;
    }
    return minEval;
}
