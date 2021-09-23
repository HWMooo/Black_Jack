#include <iostream>
#include <string>
#include <vector>
#include "Card.h"
#include "Game.h"

std::ostream& operator<<(std::ostream& os, const Card& ACard);
std::ostream& operator<<(std::ostream& os, const GenericPlayer& AGenericPlayer);

int main(){
    std::string InstructionsInput;
    std::cout << "Welcome to Blackjack!, would you like to know the instructions? " << std::endl;
    std::cin >> InstructionsInput;
    if(InstructionsInput == "Y" || InstructionsInput == "y"){
        std::cout << "The aim of the game is to reach a score of 21, or as close as possible to the value" << std::endl;
        std::cout << "Before each round the players must place a bet" << std::endl;
        std::cout << "Once the bet has been placed, each player recieves two cards along with the dealer" << std::endl;
        std::cout << "The player can then choose to hit(add a card to there hand) or stick (keep the cards he has)" << std::endl;
        std::cout << "A player wins if the total value of there cards is greater than the dealer, but not above 21" << std::endl;
        std::cout << "If the player wins, twice the initial bet is returned " << std::endl;
        std::cout << "If the player loses, they lose there bet" << std::endl;
        std::cout << "If the player ties with the dealer, there original bet is returned" << std::endl;
        std::cout << "If the player starts with a blackjack hand(21) the bet is returned in a ratio 3:2" << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;

    int NumberOfPlayers = 0;
    while (NumberOfPlayers < 1 || NumberOfPlayers > 7)
    {
        std::cout << "How many human players would you like to add? (max 7) : ";
        std::cin  >> NumberOfPlayers;
        while(std::cin.fail()){
            std::cout << "Error, please try again :" << std::endl;
            std::cin.clear();
            std::cin.ignore(256, '\n');
            std::cin >> NumberOfPlayers;

        }
    }
    std::vector <std::string> PlayersNames;
    std::string name;
    for (int i = 0; i < NumberOfPlayers; ++i){
        std::cout << "Enter player " << i << " name :" << std::endl;
        std::cin  >> name;
        PlayersNames.push_back(name);

    }
    std::cout << std::endl;
    Game aGame(PlayersNames);
    std::string again = "y";
    while (again != "n" && again != "N"){
        aGame.PlayBlackJack();
        std::cout << "Would you like to play again? (Y/N): ";
        std::cin  >> again;
    }

    return 0;
}


std::ostream& operator<<(std::ostream& os, const Card& aCard){
    const std::string CardValue[] = {"0", "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    const std::string CardSuit[] = {" of clubs", " of diamonds", " of hearts", " of spades"};
    if (aCard.TheCardIsFacingUp)
        os << CardValue[aCard._Value] << CardSuit[aCard._Suit];
    else
        os << "XX";
    return os;
}

std::ostream& operator <<(std::ostream& os, const GenericPlayer& aGenericPlayer){
    os << aGenericPlayer._Name << ": ";
    std::vector <Card*>::const_iterator PlayerCard;
    if (!aGenericPlayer._CardsInHand.empty()){
        for (PlayerCard = aGenericPlayer._CardsInHand.begin();
             PlayerCard != aGenericPlayer._CardsInHand.end(); ++PlayerCard)
            os << *(*PlayerCard) << "";
        if (aGenericPlayer.TotalValue() != 0) {
            std::cout << "(" << aGenericPlayer.TotalValue() << ")";
        }
    }
    else {
        os << "<empty>";
    }
    return os;
}

