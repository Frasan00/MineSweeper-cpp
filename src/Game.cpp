#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
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
    
    private:
        int difficulty;
        Board *board;
};

#endif