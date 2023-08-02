#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <thread>
#include <ncurses.h>
#include "Board.cpp"

using namespace std;

class Game {
    public:
        Game(int difficulty){
            this->difficulty = difficulty;
            switch (this->difficulty){
            case 1:
                this->board = new Board(8); // 10 bombs
                break;

            case 2:
                this->board = new Board(16); // 40 bombs
                break;

            case 3:
                this->board = new Board(30); // 99 bombs
                break;
            
            default:
                this->board = new Board(16); // default medium level
                break;
            }
        }

        void start(){
            string init;
            cout <<  "--- Welcome To Minesweeper ---\n\n";
            cout << "Press Q any time to quit the game" << endl;
            cout << "Press Enter Key to discover a cell" << endl;
            cout << "Press F to flag a cell" << endl;
            cout << "Press U to unFlag a cell" << endl;
            cout << "press any key to start! ";
            int key = getchar();
            cout << static_cast<char>(key);

            bool hasWin = false;
            bool hasLost = false;
            initscr();
            cbreak();
            noecho();
            keypad(stdscr, TRUE);

            int x = 0;
            int y = 0;
            int height = this->board->getLen();
            int width = this->board->getLen();

            WINDOW* win = newwin(height, width, 0, 0);
            refresh();

            auto displayString = [&](int y, int x) {
                wclear(win);
                mvwprintw(win, 0, 0, this->board->getBoard().c_str());
                wmove(win, y, x);
                wrefresh(win);
            };

            displayString(y, x);

            int ch;
            while ((ch = getch()) != 'q' && hasWin == false && hasLost == false) {
                switch (ch) {
                    case 'w':
                        if (y > 0) y--;
                        break;

                    case 's':
                        if (y < height - 1) y++;
                        break;

                    case 'a':
                        if (x > 0) x--;
                        break;

                    case 'd':
                        if (x < width - 1) x++;
                        break;

                    case 'f':
                        this->board->flag(y, x); 
                        break;

                    case 'u':
                        this->board->unFlag(y, x); 
                        break;

                    case ' ':
                        int result = this->board->click(y, x);

                        if(result == 9) hasLost = true;
                        else if(result == 10) hasWin = true;
                        break;
                }
                displayString(y, x);
            }
            delwin(win);
            endwin();

            if(hasLost == true) {
                cout << "You took a bomb!" << endl;
            }

            else if(hasWin == true) {
                cout << "You Won!" << endl;
            }
            cout << "Thanks for playing!" << endl;
        }
    
    private:
        int difficulty;
        Board *board;
};

#endif