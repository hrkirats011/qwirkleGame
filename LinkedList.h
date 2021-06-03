
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include <memory>

class LinkedList {
public:

   LinkedList();
   LinkedList(LinkedList& other);
   ~LinkedList();

   void addBack(std::shared_ptr<Tile> tile);
   std::shared_ptr<Tile> removeFront();
   std::shared_ptr<Tile> remove(int index);

   void printTiles();
   std::string getAllTiles();
   void shuffle();
   
   int getSize();
   int getIndex(std::shared_ptr<Tile> t);
   int getTileIndex(std::string str);
   std::shared_ptr<Node> getNode(int index); //
  
   bool containsTile(std::shared_ptr<Tile> tile);

private:
   std::shared_ptr<Node> head;
   int size;
};

#endif // ASSIGN2_LINKEDLIST_H
