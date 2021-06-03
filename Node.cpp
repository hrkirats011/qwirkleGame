
#include "Node.h"
#include <memory>

Node::Node(std::shared_ptr<Tile> tile, std::shared_ptr<Node> next)
{
   this->tile = tile;
   this->next = next;
}

Node::Node(Node& other)
{
   this->tile = other.tile;
   this->next = other.next;
}

Node::~Node(){
}
