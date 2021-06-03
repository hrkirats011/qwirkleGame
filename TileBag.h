#ifndef ASSIGN2_TILEBAG_H
#define ASSIGN2_TILEBAG_H

#include "LinkedList.h"
#include <vector>
#include<memory>


using std::vector;
using std::string;

class TileBag {

public:
    TileBag();
    ~TileBag();
    int getSize();
    std::shared_ptr<LinkedList> getList();
    void addBack(std::shared_ptr<Tile> t);
    void fillBag();
    void printTileBag();
    std::string getAllTiles();
    void shuffle();
    std::shared_ptr<Tile> removeFront(); 
    bool isEmpty();
    

private:
    std::shared_ptr<LinkedList> tile_bag;
    

};

#endif // ASSIGN2_TILEBAG_H