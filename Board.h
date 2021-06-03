#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H

#include "Tile.h"
#include<iostream>
#include<vector>
#include<string>
#include<memory>

using std::vector;
using std::string;
using std::cout;
using std::endl;

class Board{

public:
    Board();
    ~Board();
    Board(Board& other);
    void printBoard();
    void printElement(string str);
    void printRedShape(int shape);
    void printOrangeShape(int shape);
    void printYellowShape(int shape);
    void printGreenShape(int shape);
    void printBlueShape(int shape);
    void printPurpleShape(int shape);    
    std::string toString();
    char intToChar(int i);
    void placeTile(std::shared_ptr<Tile> t, int r, int c);
    bool isEmpty(int r, int c);
    bool isEmpty();
    std::string getTile(int i, int j);
    

private:
    vector<vector<string>> board;
};

#endif // ASSIGN2_BOARD_H



