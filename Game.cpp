//
// Created by Harry Moore
//
#include <iostream>
#include <vector>
#include "Game.h"
#include "Card.h"


Game::Game(const std::vector<std::string>& names)
{
    std::vector<std::string>::const_iterator ThePlayerNames;
    for (ThePlayerNames = names.begin(); ThePlayerNames != names.end(); ++ThePlayerNames)
        _Players.emplace_back(Player(*ThePlayerNames));
    srand(time(NULL));
    _DeckOnTheTable.FillTheDeck();
    _DeckOnTheTable.Shuffle();
}

//Actual game
//user input required
//deals with outcomes
//clears hands and decks and re shuffles
void Game::PlayBlackJack(){
    // Shuffles multiple decks to avoid repetition.
    int random = rand() % 10000;
    for(int i = 0; i < random; i++){
        _DeckOnTheTable.Shuffle();
    }
    std::vector<Player>::iterator PeoplePlayers;
    float input = 0;
    std::string AddABot;
    int AddAnotherBot = 0;
    std::cout << "Would like to add a bot (y/n) ?";
    std::cin >> AddABot;
    if(AddABot == "Y" || AddABot == "y") {
        std::cout << "How Many would you like to add? (1/2)";
        std::cin >> AddAnotherBot;
    }


    while(!noBet) {

        if(AddAnotherBot == 1){
            _SydneyOnTheTable.ShowBotOneBankRoll();
            _SydneyOnTheTable.ShowBotOneBet();

        }
        if(AddAnotherBot == 2){
            _SydneyOnTheTable.ShowBotOneBankRoll();
            _SydneyOnTheTable.ShowBotOneBet();
            _AlexOnTheTable.ShowBotTwoBankRoll();
            _AlexOnTheTable.ShowBotTwoBet();

        }
        for (PeoplePlayers = _Players.begin(); PeoplePlayers != _Players.end(); ++PeoplePlayers) {
            PeoplePlayers->ShowBankRoll();
            PeoplePlayers->Betup();
            std::cin >> input;
            while(std::cin.fail()){
                std::cout << "Error, please try again : £";
                std::cin.clear();
                std::cin.ignore(256, '\n');
                std::cin >> input;
            }
            PeoplePlayers->Bet(input);
            if(PeoplePlayers->BetCorrect(input)) {
                noBet = true;
            }
            else if(!PeoplePlayers->BetCorrect(input)) {;
                noBet = false;
            }


        }
    }
    if(noBet == true) {
        for (int i = 0; i < 2; ++i) {
            for (PeoplePlayers = _Players.begin(); PeoplePlayers != _Players.end(); ++PeoplePlayers) {
                _DeckOnTheTable.Shuffle();
                _DeckOnTheTable.DealACard(*PeoplePlayers);

            }
            _DeckOnTheTable.DealACard(_House);
        }
        _House.FlipFirstCard();

        for (PeoplePlayers = _Players.begin(); PeoplePlayers != _Players.end(); ++PeoplePlayers) {
            std::cout << *PeoplePlayers << std::endl;


        }
        if (AddAnotherBot == 1) {
            for (int i = 0; i < 2; ++i) {
                _DeckOnTheTable.DealACard(_SydneyOnTheTable);
            }
            std::cout << _SydneyOnTheTable << std::endl;
            _DeckOnTheTable.ContinueToDeal(_SydneyOnTheTable);
        }
        if (AddAnotherBot == 2) {
            for (int i = 0; i < 2; ++i) {
                _DeckOnTheTable.DealACard(_SydneyOnTheTable);
                _DeckOnTheTable.DealACard(_AlexOnTheTable);
            }
            std::cout << _SydneyOnTheTable << std::endl;
            std::cout << _AlexOnTheTable << std::endl;
            _DeckOnTheTable.ContinueToDeal(_SydneyOnTheTable);
            _DeckOnTheTable.ContinueToDeal(_AlexOnTheTable);

        }
        std::cout << _House << std::endl;


        for (PeoplePlayers = _Players.begin(); PeoplePlayers != _Players.end(); ++PeoplePlayers) {
            _DeckOnTheTable.ContinueToDeal(*PeoplePlayers);

        }

        _House.FlipFirstCard();
        std::cout << std::endl << _House;
        _DeckOnTheTable.ContinueToDeal(_House);


        if (_House.IsBust()) {
            if (!_SydneyOnTheTable.IsBust() || !_AlexOnTheTable.IsBust()) {
                if (AddAnotherBot == 1 || _SydneyOnTheTable.TotalValue() <= 20) {
                    _SydneyOnTheTable.BotOneWins();
                } else if (AddAnotherBot == 2 && _AlexOnTheTable.TotalValue() <= 20) {
                    _AlexOnTheTable.BotTwoWins();
                } else if (AddAnotherBot == 1 || _SydneyOnTheTable.TotalValue() == 21) {
                    _SydneyOnTheTable.BotOneBlackJack();
                } else if (AddAnotherBot == 2 && _AlexOnTheTable.TotalValue() == 21) {
                    _AlexOnTheTable.BotTwoBlackJack();
                }
            }
            for (PeoplePlayers = _Players.begin(); PeoplePlayers != _Players.end(); ++PeoplePlayers) {
                if (!PeoplePlayers->IsBust() && PeoplePlayers->TotalValue() <= 20) {
                    PeoplePlayers->winsBet();

                }
                if (PeoplePlayers->IsBlackJack()) {
                    PeoplePlayers->BlackJackWin();
                }
            }
        } else if (!_House.IsBust()) {
            if (AddAnotherBot == 1 || _SydneyOnTheTable.IsBlackJack() && _House.IsBlackJack()) {
                _SydneyOnTheTable.BotOneTies();
            } else if (AddAnotherBot == 2 && _AlexOnTheTable.IsBlackJack() && _House.IsBlackJack()) {
                _AlexOnTheTable.BotTwoTies();
            }
            if (AddAnotherBot == 1 || _SydneyOnTheTable.IsBlackJack() && !_House.IsBlackJack()) {
                _SydneyOnTheTable.BotOneBlackJack();
            } else if (AddAnotherBot == 2 && _AlexOnTheTable.IsBlackJack() && !_House.IsBlackJack()) {
                _AlexOnTheTable.BotTwoBlackJack();
            }
            if (AddAnotherBot == 1 || _SydneyOnTheTable.TotalValue() > _House.TotalValue() && !_SydneyOnTheTable.IsBust() && !_SydneyOnTheTable.IsBlackJack()) {
                _SydneyOnTheTable.BotOneWins();
            } else if (AddAnotherBot == 2 && _AlexOnTheTable.TotalValue() > _House.TotalValue() && !_AlexOnTheTable.IsBust() && !_AlexOnTheTable.IsBlackJack()) {
                _AlexOnTheTable.BotTwoWins();
            }
            if (AddAnotherBot == 1 || _SydneyOnTheTable.TotalValue() < _House.TotalValue()) {
                _SydneyOnTheTable.BotOneLoses();
            } else if (AddAnotherBot == 2 && _AlexOnTheTable.TotalValue() < _House.TotalValue()) {
                _AlexOnTheTable.BotTwoLoses();
            }
            if(AddAnotherBot == 1 || _SydneyOnTheTable.IsBust()){
                _SydneyOnTheTable.BotOneLoses();
            }else if(AddAnotherBot == 2 && _AlexOnTheTable.IsBust()){
                _AlexOnTheTable.BotTwoLoses();
            }
            if (AddAnotherBot == 1 || _SydneyOnTheTable.TotalValue() == _House.TotalValue()) {
                _SydneyOnTheTable.BotOneTies();
            } else if (AddAnotherBot == 2 && _AlexOnTheTable.TotalValue() == _House.TotalValue()) {
                _AlexOnTheTable.BotTwoTies();
            }




            for (PeoplePlayers = _Players.begin(); PeoplePlayers != _Players.end(); ++PeoplePlayers) {
                if (!PeoplePlayers->IsBust()) {
                    if (PeoplePlayers->IsBlackJack()) {
                        PeoplePlayers->BlackJackWin();
                    } else if (PeoplePlayers->IsBlackJack() && _House.IsBlackJack()) {
                        PeoplePlayers->tieBet();
                    } else if (PeoplePlayers->TotalValue() > _House.TotalValue()) {
                        PeoplePlayers->winsBet();
                    } else if (PeoplePlayers->TotalValue() < _House.TotalValue()) {
                        PeoplePlayers->losesBet();
                    } else {
                        PeoplePlayers->tieBet();
                    }
                }

            }
        }

    }
    for (PeoplePlayers = _Players.begin(); PeoplePlayers != _Players.end(); ++PeoplePlayers) {
        PeoplePlayers->ClearHand();
    }
    AddAnotherBot = 0;
    _House.ClearHand();
    _SydneyOnTheTable.ClearHand();
    _AlexOnTheTable.ClearHand();
    noBet = false;

}

Game::~Game() = default;


