#include "../inc/tictactoe.hh"
#include <cmath>

//Konstruktor klasy tictactoe z parametrami
tictactoe::tictactoe(const int new_size, const int new_to_win) {
    if (new_to_win < 0 || new_to_win > new_size) { to_win = new_size; size = new_size;}
    else if (new_size < 3 ) {size = 3; to_win = 3;}
    else {
        size = new_size;
        to_win = new_to_win;
    }
    state_matrix = new int*[size];
    for (int i = 0; i < size; i++) {
        state_matrix[i] = new int[size];
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) state_matrix[i][j] = 0;
    }
}

//Konstruktor klasy tictactoe
tictactoe::~tictactoe() {
    for (int i = 0; i < size; i++) {
        delete[] state_matrix[i];
    }
    delete[] state_matrix;
}

//Funkcja wyswietlajaca plansze 1 na X, -1 na O, 0 na puste pole
void tictactoe::print_board() const{
    system("clear");
    std::cout << "  ";
    for (int i = 0; i < size; i++) std::cout << " " << i << " ";
    std::cout << std::endl;
    for (int i = 0; i < size; i++) {
        std:: cout << i << " ";
        for (int j = 0; j < size; j++) {
            if (state_matrix[i][j] == 1) std::cout << "X ";
            else if (state_matrix[i][j] == -1 ) std::cout << "O ";
            else std::cout << "  ";
            if (j != size - 1) std::cout << "|";
        }
       std::cout << std::endl;
       std::cout << "  ";
       if (i != size-1) { 
            for (int k = 0; k < size; k++) std::cout << "---";
            std::cout << std::endl;
       }
    }
}

//Sprawdza czy pole jest zajete
bool tictactoe::is_field_occupied(const int x, const int y) const {
    if (state_matrix[x][y] != 0) return true;
    return false;
}

//Ustawia pole okreslonym znaczkiem
bool tictactoe::set_field(const int x, const int y, const int player) {
    if (x > size - 1 || y > size - 1 || x < 0 || y < 0) return false;
    if (!is_field_occupied(x,y)) { state_matrix[x][y] = player; return true; }
    return false;
}

//Usuwa znaczek z podanego pola
void tictactoe::remove_field(const int x, const int y) {
    if (x >= 0 && x < size && y >= 0 && y < size) state_matrix[x][y] = 0;
}

//Sprawdza aktualny stan gry (punkty)
//Bierze pod uwage ilosc serii znaczkow oby dwoch graczy
int tictactoe::check_game_state() const {
    int counter, best_counter, ai_counter, ai_best_counter;
    int score = 0;

    //Przekatne
    for (int j = 0; j <= size-to_win; j++) {
        counter = 0;
        best_counter = 0;
        ai_counter = 0;
        ai_best_counter = 0;
        int x = 0;
        int y = j;
        while (x < size && y < size) {
            if (state_matrix[x][y] == 0) {counter = 0; ai_counter = 0; x++; y++;}
            else {
                if (state_matrix[x][y] == 1){ counter++; ai_counter = 0; }
                else if(state_matrix[x][y] == -1) {counter = 0; ai_counter++; }
                
                if (counter > best_counter) best_counter = counter;
                if (ai_counter > ai_best_counter) ai_best_counter = ai_counter;

                if (counter == to_win) return 1000;
                if (ai_counter == to_win) return -1000;
                x++;
                y++;
                }
            }
        //score += (pow(best_counter,2) - pow(ai_best_counter,2));    
        score += (best_counter*best_counter - ai_best_counter*ai_best_counter);
        //score += (best_counter - ai_best_counter);  
        
        }
    for (int i = 1; i <= size-to_win; i++) {
        counter = 0;
        best_counter = 0;
        ai_counter = 0;
        ai_best_counter = 0;
        int x = i;
        int y = 0;
        while (x < size && y < size) {
            if (state_matrix[x][y] == 0) {counter = 0; ai_counter = 0; x++; y++;}
            else {
                if (state_matrix[x][y] == 1){ counter++; ai_counter = 0; }
                else if(state_matrix[x][y] == -1) {counter = 0; ai_counter++; }
                if (counter > best_counter) best_counter = counter;
                if (ai_counter > ai_best_counter) ai_best_counter = ai_counter;

                if (counter == to_win) return 1000;
                if (ai_counter == to_win) return -1000;
                x++;
                y++;
                }
            }
        //score += (pow(best_counter,2) - pow(ai_best_counter,2));    
        score += (best_counter*best_counter - ai_best_counter*ai_best_counter);
        //score += (best_counter - ai_best_counter);  
        
        }
    for (int i = size - 1; i >= to_win-1; i--) {
        counter = 0;
        best_counter = 0;
        ai_counter = 0;
        ai_best_counter = 0;
        int x = i;
        int y = 0;
        while (x >= 0 && y < size) {
            if (state_matrix[x][y] == 0) {counter = 0; ai_counter = 0; x--; y++;}
            else {
                if (state_matrix[x][y] == 1){ counter++; ai_counter = 0; }
                else if(state_matrix[x][y] == -1) {counter = 0; ai_counter++; }
                if (counter > best_counter) best_counter = counter;
                if (ai_counter > ai_best_counter) ai_best_counter = ai_counter;

                if (counter == to_win) return 1000;
                if (ai_counter == to_win) return -1000;
                x--;
                y++;
                }
            }
        //score += (pow(best_counter,2) - pow(ai_best_counter,2));    
        score += (best_counter*best_counter - ai_best_counter*ai_best_counter);
        //score += (best_counter - ai_best_counter);  
        
        }
    for (int j = 1; j <= size - to_win; j++) {
        counter = 0;
        best_counter = 0;
        ai_counter = 0;
        ai_best_counter = 0;
        int x = size - 1;
        int y = j;
        while (x >= 0 && y < size) {
            if (state_matrix[x][y] == 0) {counter = 0; ai_counter = 0; x--; y++;}
            else {
                if (state_matrix[x][y] == 1){ counter++; ai_counter = 0; }
                else if(state_matrix[x][y] == -1) {counter = 0; ai_counter++; }
                if (counter > best_counter) best_counter = counter;
                if (ai_counter > ai_best_counter) ai_best_counter = ai_counter;

                if (counter == to_win) return 1000;
                if (ai_counter == to_win) return -1000;
                x--;
                y++;
                }
            }
        //score += (pow(best_counter,2) - pow(ai_best_counter,2));    
        score += (best_counter*best_counter - ai_best_counter*ai_best_counter);
        //score += (best_counter - ai_best_counter);  
    }

    for (int i = 0; i < size; i++) {
        counter = 0;
        best_counter = 0;
        ai_counter = 0;
        ai_best_counter = 0;
        for (int j = 0; j < size; j++) {
            if (state_matrix[i][j] == 0) {counter = 0; ai_counter = 0; }
            else {
                if (state_matrix[i][j] == 1){ counter++; ai_counter = 0; }
                else if(state_matrix[i][j] == -1) {counter = 0; ai_counter++; }
                if (counter > best_counter) best_counter = counter;
                if (ai_counter > ai_best_counter) ai_best_counter = ai_counter;

                if (counter == to_win) return 1000;
                if (ai_counter == to_win) return -1000;
            }
        }
        //score += (pow(best_counter,2) - pow(ai_best_counter,2));    
        score += (best_counter*best_counter - ai_best_counter*ai_best_counter);
        //score += (best_counter - ai_best_counter);  
    }

    for (int i = 0; i < size; i++) {
        counter = 0;
        best_counter = 0;
        ai_counter = 0;
        ai_best_counter = 0;
        for (int j = 0; j < size; j++) {
            if (state_matrix[j][i] == 0) {counter = 0; ai_counter = 0; }
            else {
                if (state_matrix[j][i] == 1){ counter++; ai_counter = 0; }
                else if(state_matrix[j][i] == -1) {counter = 0; ai_counter++; }
                if (counter > best_counter) best_counter = counter;
                if (ai_counter > ai_best_counter) ai_best_counter = ai_counter;

                if (counter == to_win) return 1000;
                if (ai_counter == to_win) return -1000;
            }
        }
        //score += (pow(best_counter,2) - pow(ai_best_counter,2));    
        score += (best_counter*best_counter - ai_best_counter*ai_best_counter);
        //score += (best_counter - ai_best_counter);  

    }
    return score;
}

bool tictactoe::is_full() const {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if (state_matrix[i][j] == 0) return false;
        }
    }
    return true;
}

int tictactoe::check_neighbors(int x, int y, int player) {
    int neighbors = 0;
    if (x > 0 && y > 0 && state_matrix[x-1][y-1] == -player) neighbors++;
    if (x > 0 && state_matrix[x-1][y] == -player) neighbors++;
    if (x > 0 && y < size-1 && state_matrix[x-1][y+1] == -player) neighbors++;
    if (y > 0 && state_matrix[x][y-1] == -player) neighbors++;
    if (y < size-1 && state_matrix[x][y+1] == -player) neighbors++;
    if (x < size-1 && y > 0 && state_matrix[x+1][y-1] == -player) neighbors++;
    if (x < size-1 && state_matrix[x+1][y] == -player) neighbors++;
    if (x < size-1 && y < size-1 && state_matrix[x+1][y+1] == -player) neighbors++;
    return neighbors;
}

