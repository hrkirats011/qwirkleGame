
#include "Tile.h"
#include<string>

// constructor
Tile::Tile(Colour current_c, Shape current_s) {
  this->colour = current_c;
  this->shape = current_s;
}

// copy constructor
Tile::Tile(const Tile &t) {
  colour = t.colour;
  shape = t.shape;
}

// default constructor
Tile::Tile() {
  shape = 0;
  colour = ' ';
}

// getters
Shape Tile::getShape() {
  return shape;
}

Colour Tile::getColour() {
  return colour;
}

// setters 
void Tile::setShape(Shape current_s) {
  shape = current_s;
}

void Tile::setColour(Colour current_c) {
  colour = current_c;
}

// return true if tiles have the same color
// and the same shape

bool Tile::isSameColour(const Tile &t) {
  return colour == t.colour;
}

bool Tile::isSameShape(const Tile &t) {
  return shape == t.shape;
}

// compare the tile (shape AND colour)

bool Tile::compareTile(std::shared_ptr<Tile> t){
  bool result = false;
  if (this->colour == t->getColour() && this->shape == t->getShape()) {
    result = true;
  }
  return result;
}

bool Tile::hasLabel(std::string str){
    bool return_val = false;
    
    if (str.size() == 2){
    
      if (std::to_string(str[0]) == std::to_string(colour) && ((int)str[1]-48) == shape){
        
        return_val = true;
      }
    } return return_val;
}

std::string Tile::toString(){
  
  std::string s = "";
  s += colour;
  s += std::to_string(shape);
  return s;
}

 
Tile &Tile::operator=(const Tile &t) {
  colour = t.colour;
  shape = t.shape;
  return *this; // why not return void ?
}

bool operator==(const Tile &t1, const Tile &t2) {
  return t1.colour == t2.colour && t1.shape == t2.shape;
}
