#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include "Box.cpp"

using namespace std;

class Board {
    public:
        Board(int boardSize){
            this->boardSize = boardSize;
            this->discoveredBoxes = 0;
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
        }

        void printBoard(){
            for (int i = 0; i<this->boardSize; i++){
                for (int j = 0; j<this->boardSize; j++){
                    if(board[i][j].getStatus() == false && board[i][j].getFlag() == false) cout << "? ";
                    else if (board[i][j].getValue() < 9 && board[i][j].getStatus() == true) cout << board[i][j].getValue() << " ";
                    else if (board[i][j].getFlag() == true) cout << "x" << " ";
                    else cout << "* ";
                }
                cout << "\n" << "";
            }
        }

        void flag(int x, int y){
            this->board[x][y].flag();
        }

        void unFlag(int x, int y){
            this->board[x][y].unFlag();
        }

        // auto clicks near empty boxes and numbered ones
        void recursiveClick(int x, int y){
            // base cases
            if (x < 0 || y < 0 || x >= this->boardSize || y >= this->boardSize) return;
            if (board[x][y].getStatus() == true) return;
            if(board[x][y].getValue() == 9) return;

            if(board[x][y].getValue() > 0) {
               board[x][y].click();
               return;
            }
            
            // recursion
            board[x][y].click();
            recursiveClick(x - 1, y);
            recursiveClick(x + 1, y);
            recursiveClick(x, y - 1);
            recursiveClick(x, y + 1);
            recursiveClick(x - 1, y - 1);
            recursiveClick(x - 1, y + 1);
            recursiveClick(x + 1, y - 1);
            recursiveClick(x + 1, y + 1);
        }

        int click(int x, int y){
            if(x < 0 || y < 0 || x > this->boardSize || y > this->boardSize) return -1;
            int res = this->board[x][y].click();

            if(res == 9) return res;
            else if(res>0) {
                this->discoveredBoxes++;
                if(discoveredBoxes == pow(this->boardSize, 2)-this->bombs) return 10; // win case
                else return res;
            }
            else {
                // recursive part
                recursiveClick(x - 1, y);
                recursiveClick(x + 1, y);
                recursiveClick(x, y - 1);
                recursiveClick(x, y + 1);
                recursiveClick(x - 1, y - 1);
                recursiveClick(x - 1, y + 1);
                recursiveClick(x + 1, y - 1);
                recursiveClick(x + 1, y + 1);
                return res;
            }
        }

    private:
        int bombs;
        int boardSize;
        int discoveredBoxes;
        vector<vector<Box>> board = {};

        void createBoard(){
            vector<Box> temp = {};
            for (int i = 0; i<this->boardSize; i++){
                for (int j = 0; j<this->boardSize; j++){
                    Box* newBox = new Box(0);
                    temp.push_back(*newBox);
                }
                this->board.push_back(temp);
            }

            int bombsToPlace = this->bombs;
            // random bombs
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dis(1, 6);

            for (int i = 0; i < this->boardSize; i++) {
                for (int j = 0; j < this->boardSize; j++) {
                    int random_number = dis(gen);
                    if (random_number == 3) {
                        board[i][j].setValue(9);
                        bombsToPlace--;
                    }
                }
            }

            // nearest bomb counting
            for (int i = 0; i<this->boardSize; i++){
                for (int j = 0; j<this->boardSize; j++){
                    if (board[i][j].getValue() != 9) continue;

                    if (i-1>-1 && board[i - 1][j].getValue() != 9) board[i - 1][j].setValue(board[i - 1][j].getValue() + 1); 
                    if (i-1>-1 && j-1>-1 && board[i - 1][j - 1].getValue() != 9) board[i - 1][j - 1].setValue(board[i - 1][j - 1].getValue() + 1);
                    if (i-1>-1 && j+1<this->boardSize && board[i - 1][j + 1].getValue() != 9) board[i - 1][j + 1].setValue(board[i - 1][j + 1].getValue() + 1);
                    if (j-1>-1 && board[i][j - 1].getValue() != 9) board[i][j - 1].setValue(board[i][j - 1].getValue() + 1);                
                    if (j+1<this->boardSize && board[i][j + 1].getValue() != 9) board[i][j + 1].setValue(board[i][j + 1].getValue() + 1);
                    if (i+1<this->boardSize && j-1>-1 && board[i + 1][j - 1].getValue() != 9) board[i + 1][j - 1].setValue(board[i + 1][j - 1].getValue() + 1);
                    if (i+1<this->boardSize && board[i + 1][j].getValue() != 9) board[i + 1][j].setValue(board[i + 1][j].getValue() + 1);
                    if (i+1<this->boardSize && j+1<this->boardSize && board[i + 1][j + 1].getValue() != 9) board[i + 1][j + 1].setValue(board[i + 1][j + 1].getValue() + 1);
                }
            }
        }
};

#endif
