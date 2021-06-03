#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H
#define MAX_HAND_SIZE 6
#include "LinkedList.h"

class Player {

public:
    Player();
    Player(const Player& other);
    ~Player();
    
    std::string getName();
    int getScore();
    std::shared_ptr<LinkedList> getHand();
    void setName(std::string name);
    void setScore(int score);
    
private:
    std::string name;
    int score;
    std::shared_ptr<LinkedList> hand;
};

#endif // ASSIGN2_PLAYER_H