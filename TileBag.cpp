
#include "TileBag.h"


TileBag::TileBag(){

    tile_bag = std::make_shared<LinkedList>();
     
}

TileBag::~TileBag(){
    
}

int TileBag::getSize(){
    return tile_bag->getSize();
}


std::shared_ptr<LinkedList> TileBag::getList(){
    return tile_bag;
}

void TileBag::addBack(std::shared_ptr<Tile> t){
    tile_bag->addBack(t);
}

void TileBag::fillBag(){

    char colours[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
    int shapes[] = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};

    for(char c : colours){
        for(int s : shapes){
            std::shared_ptr<Tile> t1 = std::make_shared<Tile>(c,s);
            std::shared_ptr<Tile> t2 = std::make_shared<Tile>(c,s); 
            tile_bag->addBack(t1);
            tile_bag->addBack(t2);

        }
    }
}

void TileBag::printTileBag(){
    tile_bag->printTiles();
}

std::string TileBag::getAllTiles(){
    return tile_bag->getAllTiles();
}

void TileBag::shuffle(){
    tile_bag->shuffle();
}

bool TileBag::isEmpty(){
    bool return_val = false;
    if(tile_bag->getSize()==0){
        return_val = true;
    } return return_val;
   
}

std::shared_ptr<Tile> TileBag::removeFront(){
    return tile_bag->removeFront();   
}
