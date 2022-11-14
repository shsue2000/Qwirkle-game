#ifndef TEMP_APT_A2_BOARD_H
#define TEMP_APT_A2_BOARD_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Tile.h"
#include "LinkedList.h"
#include "TileCodes.h"
#include "Player.h"

#define MAX_BOARD_SIZE 26
#define INIT_SIZE 3


class Board {
private:
    std::vector<std::vector<Tile> > tiles;
    int width;
    int height;

public:

    /**
     * The constructor creates an empty 3x3
     */
    Board();


    /**
     * constructor for new board with defined width and height
     * @param width board width as int
     * @param height board width as int
      */
    Board(int width, int height);

    ~Board();

    /** 
     * Builds empty board
     * 
     */
    void buildEmptyBoard();


    /**
     * Prints the board including rows and column titles
     */
    void printBoard();

    /**
     * Gets the tile at a coordinate
     * @param x The x coordinate
     * @param y The y coordinate
     * @return The tile at that location or a nullptr
     */
    Tile* getAtCoord(int x, char y);

    /** REFACTOR TO GAME OBJECT??
     * Places a tile on the board
     * @param x The x coordinate
     * @param y The y coordinate
     * @param tile The tile placed, will place a copy
     * @return Whether or not the tile could be placed there
     */
    void placeTile(int x, char y, Tile tile);

    /**
     * Resizes the board based on the new tile
     * @param x
     * @param y
     */
    void resize(int x, int y);

    /**
     * Checks if a tile can be placed in a spot
     * @param x
     * @param y
     * @param tile the tile to place
     * @return
     */
    int isLegalMove(int x, int y, Tile tile);

    /**
     * Sets the board width
     * @param width
     */
    void setWidth(int width);

    /**
     * Sets the board height
     * @param height
     */
    void setHeight(int height);

    /**
     * Gets the board height
     * @return
     */
    int getHeight();

    /**
     * Gets the board width
     * @return
     */
    int getWidth();

    /**
     * Gets state string for specified tile at height and width on board
     * @param y the y coordinate of the tile
     * @param x the x coordinate of the tile
     * @return string of tile@position
     */
    std::string getBoardState(int y, int x);

    /**
     * Returns whether or not the board is empty
     * @return
     */
    bool isEmpty();
};

#endif //TEMP_APT_A2_BOARD_H
