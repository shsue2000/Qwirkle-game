
#include "LinkedList.h"

LinkedList::LinkedList()
{
    head = nullptr;
}

LinkedList::~LinkedList()
{
    clearList();
}


int LinkedList::getSize()
{
    int count = 0;
    Node *current = head;
    while (current != nullptr)
    {
        ++count;
        current = current->next;
    }

    return count;
}

void LinkedList::clearList()
{
    while (head != nullptr)
    {
        clearHelper();
    }
}


void LinkedList::clearHelper(){
    Node *current = head->next;
    delete head;
    head = current;
}


void LinkedList::addFront(Tile *tile)
{
    Node *addFront = new Node(tile, nullptr);

    if (head == nullptr)
    {
        head = addFront;
    }
    else
    {
        addFront->next = head;
        head = addFront;
    }
}

void LinkedList::addBack(Tile *tile)
{

    Node *addBack = new Node(tile, nullptr);
    if (head == nullptr)
    {
        head = addBack;
    }
    else
    {
        Node *current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = addBack;
    }
}


Tile LinkedList::deleteFront()
{
    Node *current = head->next;
    Tile returnTile = Tile();
    if (current != nullptr)
    {
        Colour currColour = current->tile->colour;
        Shape currShape = current->tile->shape;
        returnTile = Tile(currColour, currShape);
    }
    delete head;
    head = current;
    return returnTile;
}

Tile LinkedList::deleteBack()
{
    Tile returnTile = Tile();
    if (head != nullptr)
    {
        if (head->next == nullptr)
        {
            returnTile = deleteFront();
        }
        else
        {
            Node *previous = nullptr;
            Node *current = head;

            while (current->next != nullptr)
            {
                previous = current;
                current = current->next;
            }
            Colour currColour = current->tile->colour;
            Shape currShape = current->tile->shape;
            returnTile = Tile(currColour, currShape);
            previous->next = current->next;
            delete current;
        }
    }
    return returnTile;
}

void LinkedList::print()
{
    for (int i = 0; i < this->getSize(); ++i)
    {
        Tile *thisTile = this->getAt(i);
        std::cout << thisTile->getColour() << thisTile->getShape() << std::endl;
    }
}

Tile LinkedList::pop()
{
    Tile returnTile = Tile();
    if (head != nullptr)
    {
        Node *current = head->next;

        if (current != nullptr)
        {
            Colour currColour = current->tile->colour;
            Shape currShape = current->tile->shape;
            returnTile = Tile(currColour, currShape);
        }
        delete head;
        head = current;
    }
    return returnTile;
}

Tile *LinkedList::get(int index)
{
    int count = 0;
    Node *current = head;
    Tile *returnTile;
    if (index >= 0 && index < getSize())
    {
        while (count < index)
        {
            ++count;
            current = current->next;
        }
        returnTile = current->tile;
    }
    else
    {
        throw std::out_of_range("Linked List get - index out of range");
    }
    return returnTile;
}

Tile *LinkedList::getAt(int index)
{
    if (index >= getSize() || index < 0)
    {
        throw std::out_of_range("Linked List get - index out of range");
    }
    Node *current = head;
    Tile *returnTile = nullptr;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }
    returnTile = current->tile;
    return returnTile;
}

Tile *LinkedList::getHead()
{
    Tile *returnTile = head->tile;
    return returnTile;
}

void LinkedList::deleteAt(int index)
{
    if (index >= 0 && index < getSize())
    {
        if (head != nullptr)
        {
            int counter = 0;
            Node *current = head;
            Node *prev = nullptr;

            while (counter != index)
            {
                ++counter;
                prev = current;
                current = current->next;
            }

            if (prev == nullptr)
            {
                head = current->next;
            }
            else
            {
                prev->next = current->next;
            }

            delete current;
        }
    }
}
