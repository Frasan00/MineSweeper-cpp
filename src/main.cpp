#include <string>
#include <iostream>
#include "Game.cpp"

using namespace std;

int main(int argc, char* argv[]){
    system("clear");
    cout << "--- Welcome To Minesweeper ---\n\n";

    int difficulty = stoi(argv[1]);
    Game *game = new Game(difficulty);

    delete game;
}