//
// Created by Harry Moore
//
#include <iostream>
#include <string>
#include <vector>
#include "Card.h"

#ifndef THEACTUALFINALPROJECTBLACKJACK_GAME_H
#define THEACTUALFINALPROJECTBLACKJACK_GAME_H

class Game{
public:
    //Input the names of players
    //stores names in vector
    Game(const std::vector<std::string>& names);
    void PlayBlackJack();
    ~Game();
private:
    DeckOfCards _DeckOnTheTable;
    Dealer _House;
    std::vector<Player> _Players;
    bool noBet = false;
    Sydney _SydneyOnTheTable;
    Alex _AlexOnTheTable;
};


#endif //THEACTUALFINALPROJECTBLACKJACK_GAME_H
