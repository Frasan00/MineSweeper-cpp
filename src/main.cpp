#include <string>
#include <iostream>
#include "Game.cpp"

using namespace std;

int main(int argc, char* argv[]){
    int difficulty = stoi(argv[1]);
    Game *game = new Game(difficulty);
    game->start();

    delete game;
}