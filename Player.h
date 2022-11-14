
#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include "LinkedList.h"

#define MAX_HAND_SIZE 6

class Player{

public:
    Player();

    /**
     * Gives the player a tile
     * @param tile The tile to give
     */
    void giveTile(Tile tile);

    /**
     * Prints the players hand
     */
    void printHand();

    /**
     * Returns a pointer to the player's hand
     * @return
     */
    LinkedList *getHand();

    /**
     * Returns whether a pile has a tile in their hand
     * @param tile
     * @return
     */
    bool hasTile(Tile tile);

    /**
     * Adds an amount to the players score
     * @param i
     */
    void addScore(int i);

    /**
     * Sets a players score
     * @param i
     */
    void setScore(int i);

    /**
     * Returns the players hand
     * @return
     */
    int getScore();

    /**
     * Removes a tile from the players hand
     * @param tile
     */
    void removeTile(Tile tile);

    /**
     * Sets the players name
     * @param name
     */
    void setName(std::string name);

    /**
     * Returns the players name
     * @return
     */
    std::string getName();

    /**
     * Deletes hand linkedList
     */
    void deleteHand();



private:
    LinkedList hand;
    int score;
    std::string name;
};

#endif // PLAYER_H