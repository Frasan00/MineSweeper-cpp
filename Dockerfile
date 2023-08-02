FROM ubuntu:latest
WORKDIR /app
COPY ./src ./src
RUN apt-get update && \
    apt-get install -y build-essential && \
    apt-get install libncurses5-dev && \
    rm -rf /var/lib/apt/lists/*
RUN g++ -c ./src/Board.cpp -o Board.o
RUN g++ -c ./src/Game.cpp -o Game.o
RUN g++ ./src/main.cpp Board.o Game.o -o minesweeper.exe -lncurses
EXPOSE 5000
ENTRYPOINT [ "./minesweeper.exe 2" ]