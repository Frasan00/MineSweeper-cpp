#!/bin/bash

# install gnu compiler if not already installed
# sudo pacman -S gcc // installation for arch linux
# sudo apt-get update && sudo apt-get install -y build-essential on ubuntu

# ncurses is required to run this program
# pacman -S ncurses
# sudo apt-get install libncurses5-dev

g++ -c ./src/Board.cpp -o Board.o
g++ -c ./src/Game.cpp -o Game.o
g++ -c ./src/Box.cpp -o Box.o
g++ ./src/main.cpp Board.o Game.o -o minesweeper.exe -lncurses

./minesweeper.exe $1

rm ./minesweeper.exe
rm ./Board.o
rm ./Game.o
rm ./Box.o