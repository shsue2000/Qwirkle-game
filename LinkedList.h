
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include <iostream>
#include <stdexcept>

class LinkedList
{
public:
   /**
    * Constructor for a Linked-List instance.
    */
   LinkedList();

   /**
    * Destructor to free Linked-List Nodes allocated on the Heap.
    */
   ~LinkedList();

   /**
    * Counts the number of Nodes in the Linked List until the end of the 
    * Linked List is reached.
    * @return The Size/Length of the Linked List as a Integer.
    */
   int getSize();

   /**
    * Deletes all Nodes from Front to Back.
    */
   void clearList();

   /**
    * Helper Function to Clear/Delete/Free the Linked List.
    */
   void clearHelper();


   /**
    * Adds a Node to the Head of the Linked List.
    * @param tile The tile that is to be added to the front of the Linked List.
    */
   void addFront(Tile *tile);

   /**
    * Adds a Node to the Tail of the Linked List.
    * @param tile The tile that is to be added to the back of the Linked List.
    */
   void addBack(Tile *tile);

   /**
    * Deletes a Node at the Head of the Linked List. Change to return Tile.
    * @return The tile that was deleted from the front of the Linked List.
    */
   Tile deleteFront();

   /**
    * Deletes a Node at the Tail of the Linked List. Change to return Tile.
    * @return The tile that was deleted from the back of the Linked List.
    */
   Tile deleteBack();

   /**
    * Prints the contents of a Linked List.
    */
   void print();

   /**
    * Pop removes the head and returns the popped Tile. (delete)
    * @param tile The tile that is to be added to the Linked List.
    */
   void add(Tile tile);

   /**
    * Removes the head and returns the 'popped' Tile.
    * @returns The tile at the head of the Linked List.
    */
   Tile pop();

   /**
    * Returns a pointer to a Tile at the given Index.
    * @param index The 'ith' index of the Linked List.
    * @return The tile at the 'ith' index of the Linked List.
    */
   Tile *get(int index);

   /**
    * Returns the Tile stored in the Linked List at the index defined
    * in the parameter.
    * @param index The 'ith' index of the Linked List.
    * @return The tile at the 'ith' index of the Linked List.
    */
   Tile *getAt(int index);

   /**
    * Returns the Tile at the Head of the Linked List.
    * @return The tile at the 'ith' index of the Linked List.
    */
   Tile *getHead();

   /**
    * Deletes a Node at the index of the Linked List provided as a parameter.
    * @param index The index of the Linked List whose Node is to be deleted.
    */
   void deleteAt(int index);

private:
   Node *head;
};

#endif // ASSIGN2_LINKEDLIST_H
