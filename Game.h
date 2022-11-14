#ifndef TEMP_APT_A2_GAME_H
#define TEMP_APT_A2_GAME_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include <chrono>
#include <regex>
#include "Tile.h"
#include "LinkedList.h"
#include "TileCodes.h"
#include "Player.h"
#include "Board.h"

#define NUM_PLAYERS 2
#define MAX_FILE_LINES 10
#define PLAYER_ONE_ID 0 // index in players[]
#define PLAYER_TWO_ID 1 // index in players[]

typedef std::vector<std::string> stringVec;


class Game {
    private:
        Board* board;
        LinkedList* bag;
        std::vector<Player> players;
        int currentPlayer;

        /**
        * splits a string with delimiter
        * @param inputString string to be split
        * @param delimiter char delimiter to split at
        * @return vector of split strings
        */
        stringVec splitString(std::string inputString, char delimiter);

    public:
        /**
         * Constructor
          */
        Game();

        ~Game();

        /**
        * sets bag, player hands and current player for a new game
        */
        void newGame();

        /**
        * Initilaises player vector with players
        */
        void buildPlayers();

        /**
        * sets player names
        * @param name name of new player
        * @param playerID which player index
        */
        void setPlayerName(std::string name, int playerID);

        /**
         * randomises bag
        */
        void setBag();
        
        /**
        * sets players starting hands
        */
        void setPlayerHands();

        /**
        * Prints the specified hand
        * @param playerID The user id
        */
        void printHand(int playerID);


        /**
        * Gets the hand of a player playing in the vector
        * @param playerID The id of the player
        * @return The hand of the player, or nullptr if doesnt exist
        */
        LinkedList* getPlayerHand(int playerID);


        /**
        * starts game play
        */
        void playGame();

       
        /**
        * Loads an already existed saved game
        * @param fileName The filename of the game
        * @return Whether or not the load was successful
        */
        bool loadGame(std::string fileName);

        /**
        * Sets player hand from read in array of std::strings
        * @param readLines ptr to array of strings
        * @param playerID the ID of the player hand to be set
        */
        void setPlayerHand(std::vector<std::string> tiles, int playerID);


        /**
         * Sets current player
         * @param playerID takes current player ID as int
        */
        void setCurrentPlayer(int playerID);

        /**
         * Saves a currently in progress game
         * @param fileName The filename used
         */
        void saveGame(std::string fileName);

        /**
         * Checks if a Player Name string has only upper case Latin Letters.
         * @param name The standard string that represents the Players Name
         * @return True if the string consists only of Upper Case Letters.
         */
        bool checkValidName(std::string name);

        /**
         *
         * @param x
         * @param y
         * @param playerID
         * @param tile
         * @return
         */
        bool placeTile(int x, char y, int playerID, Tile tile);

        /**
         * Replaces a tile in the current players hand
         * @param tile The tile to remove
         * @return whether or not the tile is replaced
         */
        bool replace(Tile tile);
};

#endif //TEMP_APT_A2_GAME_H