
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

// get the tile codes
#include "TileCodes.h"
#include <iostream>
#include <string>
#include <memory>

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile {
public:
   Colour colour;
   Shape  shape;

   // constructor method
   Tile(Colour colour, Shape shape); 
   Tile(const Tile &t);
   Tile(); 


   // getters to get colour and shape 
   Colour getColour(); 
   Shape getShape(); 

   // Setters
   void setColour(Colour c);
   void setShape(Shape s);

   // compare 2 tiles and shape/colour separately
   bool compareTile(std::shared_ptr<Tile> t);
   bool hasLabel(std::string str);
   std::string toString();

   bool isSameColour(const Tile &t);
   bool isSameShape(const Tile &t);

   friend std::ostream &operator<<(std::ostream &out, const Tile &t);
   Tile &operator=(const Tile &t);
   friend bool operator==(const Tile &t1, const Tile &t2);   

};

#endif // ASSIGN2_TILE_H
