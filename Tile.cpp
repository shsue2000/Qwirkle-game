
#include "Tile.h"

Tile::Tile() {
    this->colour = ' ';
    this->shape = 0;
}

Tile::Tile(Colour c, Shape s) {
    this->colour = c;
    this->shape = s;
}

char Tile::getColour() {
    return this->colour;
}


int Tile::getShape() {
    return this->shape;
}
