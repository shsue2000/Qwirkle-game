
#include "Node.h"

Node::Node(){}

// Constructor for a LinkedList Node with a Tile.
Node::Node(Tile* tile, Node* next)
{
   this->tile = tile;
   this->next = next;
}

// Shallow Copy Constructor for a Node.
Node::Node(Node& other)
{
   this->tile = other.tile;
   this->next = other.next;
}
