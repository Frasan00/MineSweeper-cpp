#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "Box.cpp"

using namespace std;

class Board {
    public:
        Board(int boardSize){
            this->boardSize = boardSize;
            vector<vector<Box>> board(boardSize, vector<Box>(boardSize));

            switch (this->boardSize){
            case 8:
                this->bombs = 10;
                this->createBoard();
                break;
            
            case 16:
                this->bombs = 40;
                this->createBoard();
                break;

            case 40:
                this->bombs = 99;
                this->createBoard();
                break;
            
            default:
                this->bombs = 40;
                this->createBoard();
                break;
            }

            this->printBoard(); // to del
        }

    private:
        int bombs;
        int boardSize;
        vector<vector<Box>> board = {};

        void printBoard(){
            for (int i = 0; i<this->boardSize; i++){
                for (int j = 0; j<this->boardSize; j++){
                    if(board[i][j].getStatus() == false) cout << "?";
                    else cout << board[i][j].getValue();
                }
                cout << "\n" << "";
            }
        }

        void createBoard(){
            vector<Box> temp = {};
            for (int i = 0; i<this->boardSize; i++){
                for (int j = 0; j<this->boardSize; j++){
                    Box* newBox = new Box(0);
                    temp.push_back(*newBox);
                }
                this->board.push_back(temp);
            }
        }
};

#endif
