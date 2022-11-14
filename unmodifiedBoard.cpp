#include "Board.h"


Board::Board() {
    this->width = INIT_SIZE;
    this->height = INIT_SIZE;

    //Make empty board
    for (int y = 0; y < this->height; ++y) {
        std::vector<Tile> curRow;
        for(int x = 0; x < this->width; ++x) {
            curRow.push_back(Tile());
        }
        tiles.push_back(curRow);
    }

    for (int i = 0; i < this->numPlayers; ++i) {
        players.push_back(Player());
    }

    this->setupBagHands();

    //tests below
//    this->printBoard();
//    this->placeTile(2, 'B', 0, Tile(RED, CIRCLE));

}

void Board::setupBagHands() {
    //TODO randomise bag
    for(char c : colours) {
        for(int s : shapes) {
            for (int i = 0; i < 3; ++i) {
                this->bag.add(Tile(c, s));
            }
        }
    }

    //hand setup
    for (int i = 0; i < numPlayers; ++i) {
        players[i].giveTile(bag.pop());
    }

}

Board::~Board() {
    //TODO cleanup game and ensure no leaks
}

void Board::printBoard() {

    //Top Bar
    std::cout << "   ";
    for(int i = 0; i < this->width; ++i) {
        std::cout << i << "  ";
    }
    std::cout << std::endl << "  ";
    for(int i = 0; i < (this->width * 3) + 1; ++i) {
        std::cout << '-';
    }
    std::cout << std::endl;

    //Main board + alphabetical rows
    for (int y = 0; y < this->height; ++y) {
        std::cout << (char)('A' + y) << " |";
        for(int x = 0; x < this->width; ++x) {
            std::cout << this->tiles[y][x].colour;
            if(this->tiles[y][x].shape == 0) {
                std::cout << " " << "|";
            } else {
                std::cout << this->tiles[y][x].shape << "|";
            }
        }
        std::cout << std::endl;
    }
}

void Board::printHand(int playerID) {
    this->players[playerID].printHand();
}

Tile* Board::getAtCoord(int x, char y) {
    return &(this->tiles[y][x]);
}

LinkedList* Board::getPlayerHand(int playerID) {
    return players[playerID].getHand();
}

bool Board::placeTile(int x, char y, int playerID, Tile tile) {
    int yInt = (int)(y - 'A');
    //check if they have the tile
    if(players[playerID].hasTile(tile)) {
        //is the move legal
        int potentialScore = this->isLegalMove(x, yInt, tile);
        if(potentialScore != 0) {

            //add to board
            this->tiles[yInt][x] = tile;

            //check if it was added to edge and resize
            //TODO if anyone has a way to make this more efficient from last assign, let me know
            //check at top or bottom
            std::vector<Tile> emptyRow;
            for (int i = 0; i < this->width; ++i) {
                emptyRow.push_back(Tile());
            }

            if (yInt == 0) {
                this->tiles.insert(this->tiles.begin(), emptyRow);
                ++this->height;
            } else if (yInt == this->height - 1) {
                this->tiles.push_back(emptyRow);
                ++this->height;
            }
            //check if on right or left
            if (x == 0) {
                for (int i = 0; i < this->height; ++i) {
                    this->tiles[i].insert(this->tiles[i].begin(), Tile());
                }
                ++this->width;
            } else if (x == this->width - 1) {
                for (int i = 0; i < this->height; ++i) {
                    this->tiles[i].push_back(Tile());
                }
                ++this->width;
            }

            //update score
            this->players[playerID].addScore(potentialScore);

            //remove from player hand
            players[playerID].removeTile(tile);
            //draw replacement and add to players hand
            this->players[playerID].giveTile(this->bag.pop());
        }
    }

    return false;
}

bool Board::replace(int x, char y, int playerID, Tile tile) {
    return false;
}

int Board::isLegalMove(int x, int y, Tile tile) {
    bool legal = true;
    bool immediatelyTouchingNeighbour = false;
    //check if immediately touching
    //U-D-L-R
    if(y != 0) {
        if(this->tiles[y-1][x].colour == tile.colour || this->tiles[y-1][x].shape == tile.shape) {
            immediatelyTouchingNeighbour = true;
        }
    }
    if(y != this->height - 1) {
        if(this->tiles[y+1][x].colour == tile.colour || this->tiles[y+1][x].shape == tile.shape) {
            immediatelyTouchingNeighbour = true;
        }
    }
    if(x != 0) {
        if(this->tiles[y][x-1].colour == tile.colour || this->tiles[y][x-1].shape == tile.shape) {
            immediatelyTouchingNeighbour = true;
        }
    }
    if(x != this->width - 1) {
        if(this->tiles[y][x+1].colour == tile.colour || this->tiles[y][x+1].shape == tile.shape) {
            immediatelyTouchingNeighbour = true;
        }
    }
    //check the line for dupes Up
    bool running = true;
    int curY = y;
    int curX = x;
    int vertLength = 1;
    int horzLength = 1;
    while(running) {
        --curY;
        if(curY != 0) {
            if(this->tiles[curY][x].colour == ' ' && this->tiles[curY][x].shape == 0) {
                //end of the line
                running = false;
            } else {
                //keep going check if dupe
                if(this->tiles[curY][x].colour == tile.colour && this->tiles[curY][x].shape == tile.shape) {
                    //dupe
                    legal = false;
                    running = false;
                } else {
                    //not dupe
                    ++vertLength;
                }
            }
        }
    }
    //check the line for dupes Down
    running = true;
    curY = y;
    curX = x;
    while(running) {
        ++curY;
        if(curY != this->height - 1) {
            if(this->tiles[curY][x].colour == ' ' && this->tiles[curY][x].shape == 0) {
                //end of the line
                running = false;
            } else {
                //keep going check if dupe
                if(this->tiles[curY][x].colour == tile.colour && this->tiles[curY][x].shape == tile.shape) {
                    //dupe
                    legal = false;
                    running = false;
                } else {
                    //not dupe
                    ++vertLength;
                }
            }
        }
    }
    //check the line for dupes Left
    running = true;
    curY = y;
    curX = x;
    while(running) {
        --curX;
        if(curX != 0) {
            if(this->tiles[y][curX].colour == ' ' && this->tiles[y][curX].shape == 0) {
                //end of the line
                running = false;
            } else {
                //keep going check if dupe
                if(this->tiles[y][curX].colour == tile.colour && this->tiles[y][curX].shape == tile.shape) {
                    //dupe
                    legal = false;
                    running = false;
                } else {
                    //not dupe
                    ++horzLength;
                }
            }
        }
    }
    //check the line for dupes Right
    running = true;
    curY = y;
    curX = x;
    while(running) {
        ++curX;
        if(curX != this->width - 1) {
            if(this->tiles[y][curX].colour == ' ' && this->tiles[y][curX].shape == 0) {
                //end of the line
                running = false;
            } else {
                //keep going check if dupe
                if(this->tiles[y][curX].colour == tile.colour && this->tiles[y][curX].shape == tile.shape) {
                    //dupe
                    legal = false;
                    running = false;
                } else {
                    //not dupe
                    ++horzLength;
                }
            }
        }
    }

    if(legal && immediatelyTouchingNeighbour && (vertLength <= 6) && (horzLength <= 6)) {
        //get score
        return vertLength + horzLength;
    } else {
        return 0;
    }
}


bool Board::load(std::string fileName) {

    bool loadResult;

    // TODO
    // check the format of the file is correct (file type? total lines?)
    // print success message // should move print function out of here?
    //std::cout << "Qwirkle game successfully loaded" << std::endl;
    
    
    // load in file
    std::ifstream loadFile(fileName);

    //size already known so can use array
    std::string readLines[MAX_FILE_LINES];

    // check file exists
    if (!loadFile) {

        std::cout << "Error loading file, please try again" << std::endl;

        loadResult = false;

    }
    else {

        std::string line;

        while (std::getline(loadFile, line)) {

            for (int i = 0; i < MAX_FILE_LINES; ++i) {

                std::getline(loadFile, line);
                readLines[i] = line;
            
            }
        
        }

    }

    // SET PLAYER 1 NAME
    std::string player1Name = readLines[0];
    this->players[0].setName(player1Name);

    // SET PLAYER 1 SCORE
    int player1Score = std::stoi(readLines[1]);
    this->players[0].setScore(player1Score);

    // SET PLAYER 1 HAND
    setPlayerHand(readLines, 1);

    // SET PLAYER 2 NAME
    std::string player2Name = readLines[3];
    this->players[1].setName(player2Name);

    // SET PLAYER 2 SCORE
    int player2Score = std::stoi(readLines[4]);
    this->players[0].setScore(player1Score);
    

    // SET PLAYER 2 HAND
    setPlayerHand(readLines, 2);


    // SET CURRENT BOARD SHAPE line 6, index 5

    // SET CURRENT BOARD STATE line 7, index 6

    // SET TILE BAG CONTENTS  line 8, index 7

    // SET CURRENT PLAYER NAME line 9, index 8

    

    return loadResult;
}

void Board::setPlayerHand(std::string* readLines, int playerID) {


    // take string from array, separate at delim ',', add to vector of strings
    std::string sHand = readLines[2];
    
    std::stringstream ss (sHand);
    char delim = ',';
    std::string sTile;
    std::vector<std::string> vTiles;
    while (getline(ss, sTile, delim)) {
        vTiles.push_back(sTile);
    }
    

    // build vector of tiles from vector of strings
    std::vector<Tile> playerTiles;
    Colour c;
    Shape s;
    for (int i = 0; i < vTiles.size(); ++i) {

        std::string sTileChar = vTiles.at(i);

        //colour is first char in string, shape is second char in string
        c = sTileChar[0];
        s = sTileChar[1] - '0'; //char to int convert, '0' ascii equiv to 48

        //add tile to vector of tiles
        Tile tempTile = Tile(c, s);
        playerTiles.push_back(tempTile);
    }

    // add tiles to playerHand linkedList
    LinkedList playerHand;
    for (int i = 0; i < playerTiles.size(); ++i) {

        Tile* ptrTile = &(playerTiles.at(i));
        playerHand.addBack(ptrTile);
    }

    // set new player hand to player ID
    this->playerHands[playerID] = playerHand;

}

void Board::save(std::string fileName)
{
    std::string p0_hand_str;
    std::string p1_hand_str;
    std::string board_state_str;
    std::string bag_str; 
    // LinkedList *p0_hand = getPlayerHand(0);
    // LinkedList *p1_hand = getPlayerHand(1);

    // DUMMY VALUES START
    LinkedList *p0_hand = new LinkedList();
    LinkedList *p1_hand = new LinkedList();

    p0_hand->addFront(new Tile(RED, SQUARE));
    p0_hand->addFront(new Tile(BLUE, SQUARE));
    p0_hand->addFront(new Tile(GREEN, SQUARE));
    p1_hand->addFront(new Tile(RED, DIAMOND));
    p1_hand->addFront(new Tile(BLUE, DIAMOND));
    p1_hand->addFront(new Tile(GREEN, DIAMOND));

    bag.addFront(new Tile(RED, DIAMOND));
    bag.addFront(new Tile(BLUE, DIAMOND));
    bag.addFront(new Tile(GREEN, DIAMOND));
    bag.addFront(new Tile(RED, CIRCLE));
    bag.addFront(new Tile(BLUE, CIRCLE));
    bag.addFront(new Tile(GREEN, CIRCLE));

    // DUMMY VALUES END

    std::cout << p0_hand->getSize() << std::endl;
    // stringify the player hand (tiles)
    for (int i = 0; i < p0_hand->getSize(); i++)
    {
        Tile* tile = p0_hand->getAt(i);
        p0_hand_str += tile->colour;
        p0_hand_str += std::to_string(tile->shape);

        if (i != p0_hand->getSize() - 1)
        {
            p0_hand_str += ",";
        }
    }
    for (int i = 0; i < p1_hand->getSize(); i++)
    {
        Tile* tile = p1_hand->getAt(i);
        p1_hand_str += tile->colour;
        p1_hand_str += std::to_string(tile->shape);

        if (i != p1_hand->getSize() - 1)
        {
            p1_hand_str += ", ";
        }
    }

    // stringify the board state
    for (int y = 0; y < this->height; y++)
    {
        for (int x = 0; x < this->width; x++)
        {
            if (!(tiles[y][x].colour == ' ' && tiles[y][x].shape == 0))
            {

                std::cout << "coord" << y << x
                          << tiles[y][x].colour
                          << tiles[y][x].shape << std::endl;

                board_state_str += tiles[y][x].colour;
                board_state_str += std::to_string(tiles[y][x].shape);
                board_state_str += "@";
                board_state_str += (char)('A' + y);
                board_state_str += std::to_string(x);
            }
        }
    }
    
    //stringify bag 
    for(int i = 0; i < bag.getSize(); i++)
    {
        Tile* tile = bag.getAt(i);
        bag_str += tile->colour;
        bag_str += std::to_string(tile->shape); 

        if(i != bag.getSize()-1)
        {
            bag_str += ",";
        }
    }

    std::ofstream savefile;
    savefile.open(fileName);
    //savefile << printName(0) << "\n"
    //<< printScore(0) << "\n"
    savefile << p0_hand_str << "\n"
             //<< printName(1) << "\n"
             //<< printScore(1)<< "\n"
             << p1_hand_str << "\n"
             << height << "," << width << "\n"
             << board_state_str << "\n"
             << bag_str << "\n"; 
    //save current player name "\n";
    savefile.close();
}
