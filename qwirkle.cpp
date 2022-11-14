#include <iostream>
#include <limits>

#include "LinkedList.h"
#include "Game.h"

void printOptions();

bool newGame(Game *game);

void loadGame(Game *game);

void printCredits();

int main(void)
{

     Game *game = new Game();

     //Menu
     std::cout << "Welcome to Quirkle!" << std::endl
               << "-------------------" << std::endl;

     int option;
     bool gameInstance = true;

     do
     {
          printOptions();

          std::cin >> option;

          //Check if 'cin' is an integer, Invalid Input otherwise.
          if (std::cin.fail())
          {
               std::cin.clear();
               std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

               std::cout << std::endl;
               std::cout << "Invalid Input: Enter Options: [1-4]" << std::endl;
               std::cout << std::endl;
          }

          //1. New game
          else if (option == 1)
          {
               //Closes game after winning or Quitting in-game
               gameInstance = newGame(game);
          }
          //2. Load Game
          else if (option == 2)
          {
               loadGame(game);
          }

          //3. Credits
          else if (option == 3)
          {
               printCredits();
          }

          //4. Quit
          else if (option == 4)
          {
               gameInstance = false;
          }

          else
          {
               std::cout << "Invalid Input" << std::endl;
          }

     } while (gameInstance == true);

     std::cout << '\n'
               << "Goodbye!" << std::endl;
     delete game;

     return EXIT_SUCCESS;
}

void printOptions()
{
     std::cout << "Menu" << std::endl
               << "----" << std::endl;
     std::cout << "1. New Game" << std::endl;
     std::cout << "2. Load Game" << std::endl;
     std::cout << "3. Credits (Show student information)" << std::endl;
     std::cout << "4. Quit" << std::endl;
     std::cout << "> ";
}

bool newGame(Game *game)
{
     bool gameStatus = false;

     std::cout << "Starting a New Game" << std::endl;

     bool playerOneValid = false;

     std::cout << "Enter a name for player 1 (uppercase characters only)"
               << std::endl;

     std::cout << "> ";

     std::string p0_name;
     std::cin >> p0_name;

     while (!playerOneValid)
     {
          if (game->checkValidName(p0_name))
          {
               game->setPlayerName(p0_name, PLAYER_ONE_ID);
               playerOneValid = true;
          }
          else if (game->checkValidName(p0_name) == false)
          {
               std::cout << "Invalid Name" << std::endl;
               std::cout << "Enter a name for player 1 " <<
                        "(uppercase characters only)"
                         << std::endl;
               p0_name.clear();
               std::cin >> p0_name;
          }
     }

     bool playerTwoValid = false;
     std::cout << "Enter a name for player 2 (uppercase characters only)" << std::endl;
     std::cout << "> ";
     std::string p1_name;
     std::cin >> p1_name;

     while (!playerTwoValid)
     {
          int nameCompare = p0_name.compare(p1_name);
          if (game->checkValidName(p1_name) && nameCompare != 0)
          {
               game->setPlayerName(p1_name, PLAYER_TWO_ID);
               playerTwoValid = true;
          }
          else if (game->checkValidName(p1_name) == false || nameCompare == 0)
          {
               std::cout << "Invalid Name" << std::endl;
               std::cout << "Enter a name for player 2 (uppercase characters only)" << std::endl;
               p1_name.clear();
               std::cin >> p1_name;
          }
     }

     game->newGame();

     return gameStatus;
}

void loadGame(Game *game)
{
     std::string fileName = "";
     std::ifstream loadTest;
     std::cout << "Enter the filename from which load a game" << std::endl;
     std::cin >> fileName;
     std::cout << "Loading: " << fileName << std::endl;
     loadTest.open(fileName);

     if (loadTest)
     {
          if (game->loadGame(fileName))
          {
               std::cout << "Qwirkle game successfully loaded" << std::endl;
               game->playGame();
          }
          else
          {
               std::cout << std::endl;

               std::cout << "Error loading file, please try again" << std::endl;
               std::cout << std::endl;
          }
     }
     else
     {
          std::cout << std::endl;
          std::cout << "File does not exist" << std::endl;
          std::cout << std::endl;
     }
     loadTest.close();
}

void printCredits()
{
     std::cout << std::endl;
     std::cout << "----------------------------------" << std::endl;
     std::cout << "Name: Chloe Holmes" << std::endl
               << "Student ID: s3782047" << std::endl
               << "Email: s3782047@student.rmit.edu.au" << std::endl
               << std::endl;
     std::cout << "Name: Noel Matthews" << std::endl
               << "Student ID: s3860249" << std::endl
               << "Email: s3860249@student.rmit.edu.au" << std::endl
               << std::endl;
     std::cout << "Name: Jeremy Chung" << std::endl
               << "Student ID: s3523988" << std::endl
               << "Email: s3523988@student.rmit.edu.au" << std::endl
               << std::endl;
     std::cout << "Name: Si Han Sue" << std::endl
               << "Student ID: s3743694" << std::endl
               << "Email: s3743694@student.rmit.edu.au" << std::endl;
     std::cout << "----------------------------------" << std::endl
               << std::endl;
}
