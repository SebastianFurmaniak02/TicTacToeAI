#include <chrono>
#include "../inc/ai.hh"


int main () {
    //Zmienne do parametrow gry
   int size, to_win, depth; 
   bool first_move;
    //Podanie parametrow gry
   std::cout << "Podaj wymiar planszy: ";
   std::cin >> size;
   std::cout << "Podaj ilosc pol do wygranej: ";
   std::cin >> to_win;
   std::cout << "Kto zaczyna? (1-gracz, 0-AI): ";
   std::cin >> first_move;
   std::cout << "Podaj glebokosc rekursji AI: ";
   std::cin >> depth;
    //Tworzenie planszy
   tictactoe board(size,to_win);
    //Tworzenie SI
   ai ai_player(depth);
    //Zmienne do zapisania ruchu oraz do wyswietlania najlepszego ruchu.
   int x,y; 
   int minEval = 0;
    //Zmienne do zapisywania czasu
   auto begin = std::chrono::high_resolution_clock::now();
   auto end = std::chrono::high_resolution_clock::now();
   auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(begin - begin);
    //Jesli gracz ma zaczynac
   if(first_move) {
    //Gra trwa, az plansza zostanie zapelniona lub ktos wygra
    while (!board.is_full() && abs(board.check_game_state()) != 1000)
    {   
         //Wyswietlenie planszy i podglad parametrow
        board.print_board(); 
        std::cout << std::endl << "Stan gry: " << board.check_game_state() << std::endl << "Minimalny wynik MinMax: " << minEval << std::endl;
        std::cout << "Czas: " << elapsed.count()*1e-9 << " s" << std::endl << std::endl;
         //Ruch gracza
        do {
            std::cout << "Podaj wiersz: ";
            
            do {std::cin.clear(); std::cin.ignore(1024,'\n'); std::cin >> x; } while (std::cin.fail());
            std::cout << "Podaj kolumne: ";
            do {std::cin.clear(); std::cin.ignore(1024,'\n'); std::cin >> y; } while (std::cin.fail());
        } while (!board.set_field(x,y,1));
         //Sprawdzenie stanu gry
        if (board.check_game_state() == 1000 || board.is_full()) break;
         //Wyswietlenie planszy i podglad parametrow
        board.print_board();
        std::cout << std::endl << "Stan gry: " << board.check_game_state() << std::endl << std::endl;
        std::cout << "AI liczy najlepszy ruch ..." << std::endl;
         //Pomiar czasu i sprawdzanie najlepszego ruchu SI
        begin = std::chrono::high_resolution_clock::now();
        minEval = ai_player.get_move(&board);
        end = std::chrono::high_resolution_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
         //Ruch SI
        board.set_field(ai_player._x(),ai_player._y(),-1);
    }
   }
    //Jestli AI ma zaczynac
   else {
    //Gra trwa, az plansza zostanie zapelniona lub ktos wygra
    while (!board.is_full() && abs(board.check_game_state()) != 1000)
    {   
        std::cout << "AI liczy najlepszy ruch ..." << std::endl;
         //Pomiar czasu i sprawdzenie najlepszego ruchu SI
        begin = std::chrono::high_resolution_clock::now();
        minEval = ai_player.get_move(&board);
        end = std::chrono::high_resolution_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
         //Ruch SI
        board.set_field(ai_player._x(),ai_player._y(),-1);
         //Wyswietlenie planszy i podglad parametrow
        board.print_board();
        std::cout << std::endl << "Stan gry: " << board.check_game_state() << std::endl << "Minimalny wynik MinMax: " << minEval << std::endl;
        std::cout << "Czas: " << elapsed.count()*1e-9 << " s" << std::endl << std::endl;
         //Sprawdzenie stanu gry
        if (board.check_game_state() == -1000 || board.is_full()) break;
         //Ruch gracza
        do {
            std::cout << "Podaj wiersz: ";
            do { std::cin.clear(); std::cin.ignore(1024,'\n'); std::cin >> x; } while (std::cin.fail());
            std::cout << "Podaj kolumne: ";
            do { std::cin.clear(); std::cin.ignore(1024,'\n'); std::cin >> y; } while (std::cin.fail());
        } while (!board.set_field(x,y,1));
         //Wyswietlenie planszy i podglad parametrow
        board.print_board();
        std::cout << std::endl << "Stan gry: " << board.check_game_state() << std::endl << std::endl;
    }
   }
   //Podsumowanie
   int final_state = board.check_game_state();
   board.print_board();
   std::cout << std::endl << "Stan gry: " << final_state << std::endl << std::endl;
   if(final_state == 1000) std::cout << "Wygrywa gracz!" << std::endl << std::endl;
   else if(final_state == -1000) std::cout << "Wygrywa AI!" << std::endl << std::endl;
   else std::cout << "Remis!" << std::endl << std::endl;

    return 0;
}