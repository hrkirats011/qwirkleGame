
#include "Player.h"

Player::Player(){
    name = "";
    score = 0;
    hand = std::make_shared<LinkedList>();
}


Player::~Player(){
    
}

std::string Player::getName(){
    return name;
}

int Player::getScore(){
    return score;
}

std::shared_ptr<LinkedList> Player::getHand(){
    return hand;
}

void Player::setName(std::string name){
    this->name = name;
}

void Player::setScore(int score){
    this->score = score;
}  
    