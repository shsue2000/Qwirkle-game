
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile {
public:
   Colour colour;
   Shape  shape;

   Tile();
   Tile(Colour c, Shape s);

   /**
    * Returns the colour in char
    * @return
    */
   char getColour();

   /**
    * Returns the shape in int
    * @return
    */
   int getShape();
};

#endif // ASSIGN2_TILE_H
