#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <thread>
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
            bool hasWin = false;
            bool hasLost = false;
            string tempX;
            string tempY;
            string comand;

            system("clear");
            cout << "--- Welcome To Minesweeper ---\n\n";

            while(hasWin == false && hasLost == false){
                this->board->printBoard();
                cout << "\n";
                cin >> tempX;
                cin >> tempY;
                cin >> comand;

                if(comand == "q" || comand == "e" || comand == "quit" || comand == "exit") {
                    cout << "Thanks for playing!" << endl;
                    break;       
                }

                if(comand == "flag") { 
                    this->board->flag(stoi(tempX), stoi(tempY)); 
                    system("clear");
                    continue; 
                }
                if(comand == "unFlag") { 
                    this->board->unFlag(stoi(tempX), stoi(tempY)); 
                    system("clear");
                    continue; 
                }

                int result = this->board->click(stoi(tempX), stoi(tempY));
                
                switch (result){
                    case 9:
                        hasLost = true;
                        system("clear");
                        this->board->printBoard();
                        cout << "\n" << "Sorry you took a bomb!" << endl;
                        cout << "Thanks for playing!" << endl;
                        break;

                    case -1:
                        system("clear");
                        cout << "Please insert valid indexs" << endl;
                        break;

                    case 10:
                        hasWin = true;
                        system("clear");
                        this->board->printBoard();
                        cout << "\n" << "You won!" << endl;
                        cout << "Thanks for playing!" << endl;         
                    
                    default:
                        system("clear");
                        break;
                }
            }
        }
    
    private:
        int difficulty;
        Board *board;
};

#endif