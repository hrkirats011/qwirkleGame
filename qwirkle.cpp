#include "Game.h"
#include "LinkedList.h"
#include <cstdlib>
#include <iostream>




#define EXIT_SUCCESS 0

using std::cin;
using std::cout;
using std::endl;
int menu();
int main(void)
{
   menu();

   return EXIT_SUCCESS;
}

int menu()
{
   int choice;

   do
   {
      cout << "Menu\n";
      cout << "---------\n";
      cout << "1. New Game \n";
      cout << "2. Load Game \n";
      cout << "3. Credits \n";
      cout << "4. Help \n";
      cout << "5. Quit \n";
      cin >> choice;
      if (choice == 1)
      {
         cout << "Please input the number of players: ";
         int count;
         cin >> count;
         cout << endl;
         cout << "Starting a New Game";
         std::shared_ptr<Game> game = std::make_shared<Game>();
         game->startNewGame(count);
         choice = 5;
      }
      else if (choice == 2)
      {
         std::cout << "Enter the filename from which load a game" << std::endl;
         std::cout << ">";
         std::string filename;
         cin >> filename;
         std::cout << std::endl;
         
         std::shared_ptr<Game> game = std::make_shared<Game>();
         game->loadGame(filename);
         choice = 5;
      }
      else if (choice == 3)
      {
         std::cout << "---------------------------------------------" << std::endl;

         std::cout << "Name: Harkirat Singh " << std::endl;
         std::cout << "Student ID: s3820700" << std::endl;
         std::cout << "Email: Student ID: s3820700@student.rmit.edu.au\n"
                   << std::endl;

         std::cout << "Name: Jatin Puri" << std::endl;
         std::cout << "Student ID: s3832666" << std::endl;
         std::cout << "Email: s3832666@student.rmit.edu.au\n"
                   << std::endl;

         std::cout << "Name: Manav Makkar" << std::endl;
         std::cout << "Student ID: s3815294" << std::endl;
         std::cout << "Email: s3815294@student.rmit.edu.au\n"
                   << std::endl;

         std::cout << "Name: Tiana Manetta" << std::endl;
         std::cout << "Student ID: s3832736" << std::endl;
         std::cout << "Email: s3832736@student.rmit.edu.au" << std::endl;

         std::cout << "---------------------------------------------\n"
                   << std::endl;
      }
      else if (choice == 4){
         // help menu
         while(1){
            // print helper menu
            cout << endl;
            cout << "---------------------------------------------\n";
            cout << "1.Setup.\n";
            cout << "2.Game Play.\n";
            cout << "3.Adding Tiles.\n";
            cout << "4.Trading Tiles.\n";
            cout << "5.Scoring.\n";
            cout << "6.End of the Game.\n";
            cout << "7.Exit Help.\n";
            cout << "---------------------------------------------\n";
            cout << "Please input option: ";
            int option;
            // input choice to show the helper menu
            cin >> option;
            cout << endl << endl;
            if (option == 1){
               // print setup helper menu
               cout << "   Setup.\n\n";
               cout << "You need a paper and pencil to keep the score.\n";
               cout << "Place all the tiles in the bag.\n";
               cout << "Each player draws 6 tiles and places them that no other player can see them.\n";
               cout << "This is your deck. Find the player with the most tiles sharing one characteristic.\n";
               cout << "That player plays those tiles in a row or column and the number of tiles is the score for that first turn.\n";
                        
            }else if (option == 2){
               // print game play helper menu
               cout << "   Game Play.\n\n";
               cout << "On your turn you can do one of the 3 actions:\n";
               cout << "   - Add one tile to the grid and draw a tile to bring your deck again to 6.\n";
               cout << "   - Add two or more tiles to the grid.\n";
               cout << "All tiles played must share one attribute (color or shape) and must be placed in the same line.\n";
               cout << "The tiles must not all have to touch each other.\n";
               cout << "Again, draw tiles until your deck has 6 tiles again.\n";
               cout << "Trade some or all of your tiles for different tiles.\n";
            }else if (option == 3){
               // print adding tiles helper menu
               cout << "   Adding Tiles.\n\n";
               cout << "All tiles must connect to the grid and form a line of two or more tiles.\n";
               cout << "A line is either all one shape or all one color.\n";
               cout << "Tiles that are added to a line must share the same attribute as the tiles that are already in that line.\n";
               cout << "You may play multiple tiles on your turn as long as all tiles played are\n";
               cout << "the same color or the same shape and are placed in the same line.\n";
               cout << "You cannot play two tiles that are exactly the same.\n";
               cout << "At least one of the tiles you play must touch a tile that has already been played and match the tile in color or shape.\n";
               cout << "Any tiles that touch each other are part of a line.\n";
               cout << "Lines are either all one shape or all one color, without any duplicates.\n";
            }else if (option == 4){
               // print trading tiles hlper menu
               cout << "   Trading Tiles.\n\n";
               cout << "If your are unable to add tiles to the grid on your turn, you must trade in some or all of your tiles.\n";
               cout << "Set aside the tiles you want to trade, then draw replacement tiles.\n";
               cout << "Finally, mix the tiles that you traded away back into the bag.\n";
            }else if (option == 5){
               // print scroing helper menu
               cout << "   Scoring.\n\n";
               cout << "When you create a line, you score one point for each tile in that line.\n";
               cout << "When a tile is part of two different lines, it will score 2 points.\n";
               cout << "You score 6 bonus points whenever you complete a line of 6 tiles, which is called a Qwirkle.\n";
            }else if (option == 6){
               // print end of the game helper menu
               cout << "   End of the Game.\n\n";
               cout << "When there are no more tiles left, the play continues as before but players don't replenish their decks at the end of their turns.\n";
               cout << "The first player who uses all of his tiles ends the game and gets a 6 points bonus.\n";
               cout << "The player with the highest score is the winner of the game.\n";
            }else if (option == 7)
               break;
         }
      }
      else if (choice == 5)
      {
         cout << "Good Bye \n";
      }
      else
      {
         cout << "The input is invalid. Please try again. \n";
      }

   } while (choice != 5);

   return 0;
}