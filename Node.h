 
#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"

class Node {
public:

   Node(std::shared_ptr<Tile> tile, std::shared_ptr<Node> next);
   Node(Node& other);
   ~Node();

   std::shared_ptr<Tile> tile;
   std::shared_ptr<Node> next;
};

#endif // ASSIGN2_NODE_H
