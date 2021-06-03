#ifndef ASSIGN2_GAME_H
#define ASSIGN2_GAME_H

#define MAX_BOARD_SIZE  26
#define MAX_HAND_SIZE 6

#include <vector>
#include <string>
#include <fstream> 
#include <cctype>
#include "Board.h"
#include "Player.h"
#include "TileBag.h"

using std::vector;
using std::string;

class Game {

public:
    Game();
    ~Game();
    Game(Game& other);

    std::shared_ptr<Board> getBoard();
    std::shared_ptr<Player> getPlayer(int i);    

    void startNewGame(int cnt);
    void loadGame(std::string filename);
    void readTiles(std::string str, std::shared_ptr<LinkedList> list);
    void readBoard(std::string str);
    void playGame();
    bool save(std::string filename,std::shared_ptr<TileBag> tile_bag);
    bool stopCondition();
    void endMessage();


    void inputPlayerName(std::shared_ptr<Player> p, int z);
    void setUpHand(std::shared_ptr<Player> p);
    void drawTile(std::shared_ptr<Player> p);
    bool placeTile(std::string tile, std::string pos, 
                   std::shared_ptr<Player> p);
    bool replaceTile(std::string tile, std::shared_ptr<Player> p);

    std::string getCommand();
    bool processCommand(std::string command, std::shared_ptr<Player> p);
    void switchPlayer(); 


    bool validatePlayerName(std::string s); 
    bool validatePosition(std::string s); 
    bool validateTile(std::string str);

    bool validMove(std::string tile, std::string pos);
    bool validateHorizontal(int row, int col, std::string tile);
    bool validateVertical(int row, int col, std::string tile);

    bool validColour(Colour colour);
    bool validShape(Shape shape);    
    
    bool isNumeric(std::string s);
    int charToInt(char c);
    int shapeInt(char c);
    vector<string> splitString(string str);

    bool allUnique(vector<char> v);
    bool allSame(vector<char> v);
    bool hasNeighbour(int row, int col);
    int updateScore(std::string pos, std::shared_ptr<Player> p);

    void printGameInfo(std::shared_ptr<Player> current_player);
    

    
    
    

private:
    std::shared_ptr<Board> board;
    std::shared_ptr<TileBag> tile_bag;    
    std::shared_ptr<Player> p_turn; 
    std::shared_ptr<Player> *p;
    int count;
};

#endif // ASSIGN2_GAME_H