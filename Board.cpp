#include "Board.h"


Board::Board() {
    
}

Board::~Board() {
}

void Board::buildEmptyBoard() {

    for (int y = 0; y < this->height; ++y) {
        std::vector<Tile> curRow;
        for(int x = 0; x < this->width; ++x) {
            curRow.push_back(Tile());
        }
        tiles.push_back(curRow);
    }

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

Tile* Board::getAtCoord(int x, char y) {
    return &(this->tiles[y][x]);
}

void Board::placeTile(int x, char y, Tile tile) {
    int yInt = (int)(y - 'A');
    this->tiles[yInt][x] = tile;
}

void Board::resize(int x, int y) {
    //check left and right
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
    //check top and bottom
    std::vector<Tile> emptyRow;
    for(int i = 0; i < this->width; ++i) {
        emptyRow.push_back(Tile());
    }

     if (y == 0) {
         this->tiles.insert(this->tiles.begin(), emptyRow);
         ++this->height;
     } else if (y == this->height - 1) {
         this->tiles.push_back(emptyRow);
         ++this->height;
     }
}

int Board::isLegalMove(int x, int y, Tile tile) {
    bool legal = true;
    bool immediatelyTouchingNeighbour = false;
    //check if immediately touching
    //U-D-L-R
    if(y != 0) {
        if(this->tiles[y-1][x].colour == tile.colour
        || this->tiles[y-1][x].shape == tile.shape) {
            immediatelyTouchingNeighbour = true;
        }
    }
    if(y != this->height - 1) {
        if(this->tiles[y+1][x].colour == tile.colour
        || this->tiles[y+1][x].shape == tile.shape) {
            immediatelyTouchingNeighbour = true;
        }
    }
    if(x != 0) {
        if(this->tiles[y][x-1].colour == tile.colour
        || this->tiles[y][x-1].shape == tile.shape) {
            immediatelyTouchingNeighbour = true;
        }
    }
    if(x != this->width - 1) {
        if(this->tiles[y][x+1].colour == tile.colour
        || this->tiles[y][x+1].shape == tile.shape) {
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
        if(curY < 0) {
            //at top
            running = false;
        } else {
            if(this->tiles[curY][x].colour == ' '
            && this->tiles[curY][x].shape == 0) {
                //end of the line
                running = false;
            } else {
                if(this->tiles[curY][x].colour == tile.colour
                && this->tiles[curY][x].shape == tile.shape) {
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
    //down
    curY = y;
    curX = x;
    running = true;
    while(running) {
        ++curY;
        if(curY >= this->height) {
            //at top
            running = false;
        } else {
            if(this->tiles[curY][x].colour == ' '
            && this->tiles[curY][x].shape == 0) {
                //end of the line
                running = false;
            } else {
                if(this->tiles[curY][x].colour == tile.colour
                && this->tiles[curY][x].shape == tile.shape) {
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
    //left
    curY = y;
    curX = x;
    running = true;
    while(running) {
        --curX;
        if(curX < 0) {
            //at top
            running = false;
        } else {
            if(this->tiles[y][curX].colour == ' '
            && this->tiles[y][curX].shape == 0) {
                //end of the line
                running = false;
            } else {
                if(this->tiles[y][curX].colour == tile.colour
                && this->tiles[y][curX].shape == tile.shape) {
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
    //right
    curY = y;
    curX = x;
    running = true;
    while(running) {
        ++curX;
        if(curX >= this->width) {
            //at top
            running = false;
        } else {
            if(this->tiles[y][curX].colour == ' '
            && this->tiles[y][curX].shape == 0) {
                //end of the line
                running = false;
            } else {
                if(this->tiles[y][curX].colour == tile.colour
                && this->tiles[y][curX].shape == tile.shape) {
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

    if(legal && immediatelyTouchingNeighbour
    && (vertLength <= 6) && (horzLength <= 6)) {
        //get score
        int bonus = 0;
        if(vertLength == 6 || horzLength == 6) {
            std::cout << std::endl << "Qwirkle!" << std::endl;
            bonus = 6;
        }
        return vertLength + horzLength + bonus;
    } else {
        return 0;
    }
}

int Board::getHeight() {
    return this->height;
}

int Board::getWidth() {
    return this->width;
}

std::string Board::getBoardState(int y, int x) {
    
    std::string board_state_str;

    if (!(this->tiles[y][x].colour == ' ' && this->tiles[y][x].shape == 0))
            {

                std::cout << "coord" << y << x
                          << this->tiles[y][x].colour
                          << this->tiles[y][x].shape << std::endl;

                board_state_str += tiles[y][x].colour;
                board_state_str += std::to_string(tiles[y][x].shape);
                board_state_str += "@";
                board_state_str += (char)('A' + y);
                board_state_str += std::to_string(x);
            }

    return board_state_str;

}

void Board::setWidth(int width) {
    this->width = width;
}

void Board::setHeight(int height) {
    this->height = height;
}

bool Board::isEmpty() {
    bool empty = true;
    for(int y = 0; y < this->height; y++) {
        for(int x = 0; x < this->width; x++) {
            if(this->getAtCoord(x, y)->shape != 0) {
                empty = false;
            }
        }
    }
    return empty;
}
