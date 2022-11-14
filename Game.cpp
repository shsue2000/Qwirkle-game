#include "Game.h"

Game::Game()
{
    //game setup
    board = new Board();
    bag = new LinkedList();
    buildPlayers();
}

Game::~Game()
{
    delete board;
    delete bag;

    this->players[PLAYER_ONE_ID].deleteHand();
    this->players[PLAYER_TWO_ID].deleteHand();
}

void Game::newGame()
{
    this->board->setWidth(INIT_SIZE);
    this->board->setHeight(INIT_SIZE);
    this->board->buildEmptyBoard();
    setBag();
    setPlayerHands();
    setCurrentPlayer(PLAYER_ONE_ID);
    playGame();
}

void Game::buildPlayers()
{

    for (int i = 0; i < NUM_PLAYERS; ++i)
    {
        this->players.push_back(Player());
    }
}

void Game::setPlayerName(std::string name, int playerID)
{

    this->players.at(playerID).setName(name);
}

void Game::setBag()
{
    std::vector<Tile> tempTilesVector;
    std::vector<Tile>::iterator iter, end;

    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto rng = std::default_random_engine{seed};

    //TODO randomise bag
    for (char c : colours)
    {
        for (int s : shapes)
        {
            for (int i = 0; i < 2; ++i)
            {
                Tile tempTile = Tile(c, s);
                tempTilesVector.push_back(tempTile);
            }
        }
    }

    std::shuffle(std::begin(tempTilesVector), std::end(tempTilesVector), rng);

    for(iter=tempTilesVector.begin(),end=tempTilesVector.end();iter!=end;++iter)
    {
        Colour colour = iter->colour;
        Shape shape = iter->shape;
        bag->addBack(new Tile(colour, shape));
    }

}


void Game::setPlayerHands()
{
    //hand setup
    for (int i = 0; i < NUM_PLAYERS; ++i)
    {
        for (int j = 0; j < MAX_HAND_SIZE; j++)
        {
            this->players[i].giveTile(this->bag->pop());
        }
    }
}

void Game::printHand(int playerID)
{
    this->players[playerID].printHand();
}

LinkedList *Game::getPlayerHand(int playerID)
{
    return this->players.at(playerID).getHand();
}

void Game::playGame()
{

    bool gameover = false;

    do
    {
        Player player1 = this->players[PLAYER_ONE_ID];
        Player player2 = this->players[PLAYER_TWO_ID];
        std::cout << this->players[currentPlayer].getName() ;
        std::cout << ", it's your turn" << std::endl;
        std::cout << "Score for " << player1.getName() << ": "
                  << player1.getScore() << std::endl;
        std::cout << "Score for " << player2.getName() << ": "
                  << player2.getScore() << std::endl;
        this->board->printBoard();
        std::cout << "Your hand is" << std::endl;
        
        //Print player hand
        this->printHand(currentPlayer);
        std::cout << "> ";

        std::string userInput;
        std::cin >> userInput;

        if(userInput == "replace") {
            std::string tileString;
            std::cin >> tileString;
            char color = tileString.at(0);
            char getShape = tileString.at(1);
            int shape = getShape - '0';

            Tile replaceTile(color, shape);
            if (this->replace(replaceTile))
            {
                //next player turn
                if (currentPlayer == PLAYER_ONE_ID)
                {
                    currentPlayer = PLAYER_TWO_ID;
                }
                else
                {
                    currentPlayer = PLAYER_ONE_ID;
                }
            }
            else
            {
                std::cout << "Failed to replace Tile" << std::endl;
            }
        } else if(userInput == "place") {
            std::string tileString;
            std::cin >> tileString;
            Tile newTile(tileString.at(0), tileString.at(1) - '0');
            std::string placeWord2;
            std::cin >> placeWord2;
            if(placeWord2 == "at") {
                std::string coord;
                std::cin >> coord;
                char yval = coord.at(0);
                int xval = coord.at(1) - '0';
                if (this->placeTile(xval, yval, currentPlayer, newTile))
                {
                    //placed tile
                    if (currentPlayer == PLAYER_ONE_ID)
                    {
                        currentPlayer = PLAYER_TWO_ID;
                    }
                    else
                    {
                        currentPlayer = PLAYER_ONE_ID;
                    }
                }
                else
                {
                    std::cout << "Failed to place tile" << std::endl;
                }

            } else {
                std::cout << "Invalid Input" << std::endl;
            }
        } else if(userInput == "quit") {
            gameover = true;
        } else if(userInput == "save") {
            std::string fileName;
            std::cin >> fileName;
            saveGame(fileName);
            std::cout << "Game successfully saved" << std::endl;
        }
        else
        {
            std::cout << "Invalid Input" << std::endl;
        }

        //gameover checking
        if (this->players[PLAYER_ONE_ID].getHand()->getSize() == 0 ||
            this->players[PLAYER_TWO_ID].getHand()->getSize() == 0 ||
            this->bag->getSize() == 0)
        {
            if(this->players[PLAYER_ONE_ID].getHand()->getSize() == 0) {
                this->players[PLAYER_ONE_ID].addScore(6);
            } else {
                this->players[PLAYER_TWO_ID].addScore(6);
            }
            //gameover
            Player playerOne = players[PLAYER_ONE_ID];
            Player playerTwo = players[PLAYER_TWO_ID];
            std::cout << "Game over" << std::endl;
            std::cout << "Score for " << playerOne.getName();
            std::cout << ": " << playerOne.getScore() << std::endl;

            std::cout << "Score for " << playerTwo.getName();
            std::cout << ": " << playerTwo.getScore() << std::endl;
            std::cout << "Player ";
            if (playerOne.getScore() > playerTwo.getScore())
            {
                std::cout << playerOne.getName();
            }
            else
            {
                std::cout << playerTwo.getName();
            }
            std::cout << " won!" << std::endl
                      << std::endl;
            std::cout << "Goodbye" << std::endl;
            gameover = true;
        }

    } while (!gameover);
}

bool Game::loadGame(std::string fileName)
{

    bool loadCompleteStatus = false;
    bool loadSuccess = true;

    // load in file
    std::ifstream loadFile(fileName);

    //size already known so can use array
    std::string readLines[MAX_FILE_LINES];

    while (!loadCompleteStatus)
    {

        // check file exists
        if (loadFile.good() == false)
        {
            loadSuccess = false;
        }
        else
        {
            std::string line;
            int count = 0;

            while (std::getline(loadFile, line) && count < MAX_FILE_LINES)
            {

                readLines[count] = line;
                count++;
            }
        }

        //GET INFO FROM FILE
        // GET PLAYER 1 INFO
        std::string p0_Name = readLines[0];
        int p0_Score = std::stoi(readLines[1]);
        std::string p0_Hand = readLines[2];
        std::vector<std::string> p0_SplitTiles = splitString(p0_Hand, ',');

        // SET PLAYER 1 INFO
        this->players[PLAYER_ONE_ID].setName(p0_Name);
        this->players[PLAYER_ONE_ID].setScore(p0_Score);
        setPlayerHand(p0_SplitTiles, PLAYER_ONE_ID);

        // GET PLAYER 2 INFO
        std::string p1_Name = readLines[3];
        int p1_Score = std::stoi(readLines[4]);
        std::string p1_Hand = readLines[5];
        std::vector<std::string> p1_splitTiles = splitString(p1_Hand, ',');

        // SET PLAYER 2 INFO
        this->players[PLAYER_TWO_ID].setName(p1_Name);
        this->players[PLAYER_TWO_ID].setScore(p1_Score);
        setPlayerHand(p1_splitTiles, PLAYER_TWO_ID);

        // GET BOARD SHAPE
        int boardWidth;
        int boardHeight;
        std::string boardShape = readLines[6];
        std::vector<std::string> splitShape = splitString(boardShape, ',');
        boardWidth = std::stoi(splitShape.at(0));
        boardHeight = std::stoi(splitShape.at(1));

        // SET BOARD SHAPE & BUILD
        this->board->setWidth(boardWidth);
        this->board->setHeight(boardHeight);
        this->board->buildEmptyBoard();

        // GET CURRENT BOARD STATE line 6, index 7
        std::string boardState = readLines[7];
        std::vector<std::string> splitState = splitString(boardState, ',');
        for (std::size_t i = 0; i < splitState.size(); ++i)
        {
            // remove spaces
            if (splitState.at(i)[0] == ' ')
            {
                splitState.at(i).erase(0, 1);
            }
        }

        // SET BOARD STATE
        // split each string at '@' - tile@position
        // first element is tile, secod element is position on the board
        // add this to the board
        for (std::size_t i = 0; i < splitState.size(); ++i)
        {
            stringVec tileAndPosition = splitString(splitState.at(i), '@');
            std::string tile = tileAndPosition.at(0);
            std::string position = tileAndPosition.at(1);

            // Colour
            Colour c = tile[0];   
            // Shape     
            Shape s = tile[1] - '0';   
            // height
            char y = position[0];      
            // width
            int x = position[1] - '0'; 

            Tile *tempTile = new Tile(c, s);
            this->board->placeTile(x, y, *tempTile);
        }

        // GET TILE BAG CONTENTS
        std::string tempBag = readLines[8];
        std::vector<std::string> splitBagTiles = splitString(tempBag, ',');

        // SET BAG CONTENTS
        Colour c;
        Shape s;
        for (std::size_t i = 0; i < splitBagTiles.size(); ++i)
        {

            std::string tile = splitBagTiles.at(i);

            //colour is first char in string, shape is second char in string
            c = tile[0];
            //char to int convert, '0' ascii equiv to 48
            s = tile[1] - '0'; 

            //add tile to bag
            this->bag->addBack(new Tile(c, s));

        }


        // GET CURRENT PLAYER NAME
        std::string currentPlayerName = readLines[9];

        // SET CURRENT PLAYER NAME
        if (currentPlayerName.compare(p0_Name) == 0)
        {
            setCurrentPlayer(PLAYER_ONE_ID);
        }
        else if (currentPlayerName.compare(p1_Name) == 0)
        {
            setCurrentPlayer(PLAYER_TWO_ID);
        }
        else
        {
            loadSuccess = false;
        }
        // finish load sequence
        loadCompleteStatus = true; 
    }

    this->players.at(PLAYER_ONE_ID).getName();


    return loadSuccess; 
}

void Game::setPlayerHand(std::vector<std::string> tiles, int playerID)
{

    char c;
    int s;
    for (std::size_t i = 0; i < tiles.size(); ++i)
    {

        std::string tile = tiles.at(i);

        //colour is first char in string, shape is second char in string
        c = tile[0];
        //char to int convert, '0' ascii equiv to 48
        s = tile[1] - '0'; 

        //add tile to vector of tiles
        Tile *tempTile = new Tile(c, s);
        this->players[playerID].giveTile(*tempTile);
    }
}

stringVec Game::splitString(std::string inputString, char delimiter)
{

    std::vector<std::string> outputVector;

    std::stringstream ss(inputString);
    std::string splitString;
    while (getline(ss, splitString, delimiter))
    {
        outputVector.push_back(splitString);
    }

    return outputVector;
}

void Game::setCurrentPlayer(int currentPlayerID)
{
    this->currentPlayer = currentPlayerID;
}

void Game::saveGame(std::string fileName)
{
    std::string p0_hand_str;
    std::string p1_hand_str;
    std::string board_state_str;
    std::string bag_str;
    std::string player0_name;
    std::string player1_name;
    std::string current_player;
    int player0_score;
    int player1_score;

    LinkedList *p0_hand = getPlayerHand(0);
    LinkedList *p1_hand = getPlayerHand(1);


    player0_name = this->players[0].getName();
    player1_name = this->players[1].getName();

    player0_score = this->players[0].getScore();
    player1_score = this->players[1].getScore();

    current_player = this->players[currentPlayer].getName();


    // stringify the player hand (tiles)
    for (int i = 0; i < p0_hand->getSize(); i++)
    {
        Tile *tile = p0_hand->getAt(i);
        p0_hand_str += tile->colour;
        p0_hand_str += std::to_string(tile->shape);

        if (i != p0_hand->getSize() - 1)
        {
            p0_hand_str += ",";
        }
    }
    for (int i = 0; i < p1_hand->getSize(); i++)
    {
        Tile *tile = p1_hand->getAt(i);
        p1_hand_str += tile->colour;
        p1_hand_str += std::to_string(tile->shape);

        if (i != p1_hand->getSize() - 1)
        {
            p1_hand_str += ",";
        }
    }

    bool hasFenceposted = false;
    for (int y = 0; y < this->board->getHeight(); y++)
    {
        for (int x = 0; x < this->board->getWidth(); x++)
        {   
            if(this->board->getBoardState(y,x) != "")
            {
                if (hasFenceposted) {
                    board_state_str += ", ";  
                } else {
                    hasFenceposted = true;
                }
                board_state_str += this->board->getBoardState(y, x);
            }
        }
    }

    //stringify bag
    for (int i = 0; i < this->bag->getSize(); i++)
    {
        Tile *tile = this->bag->getAt(i);
        bag_str += tile->colour;
        bag_str += std::to_string(tile->shape);

        if (i != this->bag->getSize() - 1)
        {
            bag_str += ",";
        }
    }

    std::ofstream savefile;
    savefile.open(fileName);
    savefile << player0_name << "\n"
             << player0_score << "\n"
             << p0_hand_str << "\n"
             << player1_name << "\n"
             << player1_score << "\n"
             << p1_hand_str << "\n"
             << board->getHeight() << "," << board->getWidth() << "\n"
             << board_state_str << "\n"
             << bag_str << "\n"
             << current_player;
    savefile.close();
}

bool Game::checkValidName(std::string name)
{
    bool validName = false;
    bool returnStatus = true;
    if (!name.empty())
    {
        for (size_t i = 0; i < name.length(); i++)
        {
            if (isupper(static_cast<unsigned char>(name[i])))
            {
                validName = true;
            }
            else
            {
                validName = false;
            }
            if (validName == false)
            {
                returnStatus = false;
            }
        }
    }
    return returnStatus;
}

bool Game::placeTile(int x, char y, int playerID, Tile tile) {
    int yInt = (int)(y - 'A');
    bool out = false;
    if(players[playerID].hasTile(tile)) {
        //player has tile
        if(board->getAtCoord(x, yInt)->shape == 0) {
            if (board->isEmpty()) {
                board->placeTile(x, y, tile);
                players[playerID].removeTile(tile);
                players[playerID].giveTile(bag->pop());
                board->resize(x, yInt);
                out = true;
            } else {
                int potentialScore = board->isLegalMove(x, yInt, tile);
                if (potentialScore == 0) {
                    out = false;
                } else {
                    this->board->placeTile(x, y, tile);
                    this->players[playerID].addScore(potentialScore);
                    this->players[playerID].removeTile(tile);
                    this->players[playerID].giveTile(bag->pop());
                    this->board->resize(x, yInt);
                    out = true;
                }
            }
        } else {
            out = false;
        }
    }
    return out;
}

bool Game::replace(Tile tile) {
    //does user have tile
    bool out = false;
    if(this->players[currentPlayer].hasTile(tile)) {
        players[currentPlayer].removeTile(tile);
        bag->addBack(new Tile(tile.shape, tile.colour));
        players[currentPlayer].giveTile(bag->pop());
        out = true;
    } else {
        out = false;
    }
    return out;
}
