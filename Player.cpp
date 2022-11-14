#include "Player.h"

Player::Player()
{
    this->score = 0;
    this->hand = LinkedList();
}

void Player::giveTile(Tile tile)
{
    this->hand.addBack(new Tile(tile.getColour(), tile.getShape()));
}

void Player::printHand()
{
    for (int i = 0; i < hand.getSize(); ++i)
    {
        if (i == 0)
        {
            std::cout << hand.get(i)->getColour() << hand.get(i)->getShape();

        }
        else
        {
            std::cout << ",";
            std::cout << hand.get(i)->getColour() << hand.get(i)->getShape();
        }
    }
    std::cout << std::endl;
}

LinkedList *Player::getHand()
{
    return &this->hand;
}

bool Player::hasTile(Tile tile)
{
    bool found = false;
    for (int i = 0; i < hand.getSize(); ++i)
    {
        Tile *curTile = hand.get(i);
        if (curTile->shape == tile.shape && curTile->colour == tile.colour)
        {
            found = true;
        }
    }
    return found;
}

void Player::addScore(int i)
{
    this->score += i;
}

void Player::setScore(int i)
{
    this->score = i;
}

int Player::getScore()
{
    return this->score;
}

void Player::removeTile(Tile tile)
{
    for (int i = 0; i < hand.getSize(); ++i)
    {
        Tile *curTile = hand.get(i);
        if (curTile->shape == tile.shape && curTile->colour == tile.colour)
        {
            this->hand.deleteAt(i);
        }
    }
}

void Player::setName(std::string name)
{
    this->name = name;
}

std::string Player::getName()
{
    return this->name;
}

void Player::deleteHand() {
    delete &this->hand;

}

