//
// Created by Harry Moore
//
#include <iostream>
#include<vector>

#ifndef THEACTUALFINALPROJECTBLACKJACK_CARD_H
#define THEACTUALFINALPROJECTBLACKJACK_CARD_H

class Card{
public:
    //enum to keep value of cards and suit constant
    enum TheCardsValue {Ace = 1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King};
    enum SuitOfTheCard {Clubs, Hearts, Diamonds, Spades};
    // Function overloaded in main friend function as it is needed in other classes.
    friend std::ostream& operator<<(std::ostream& os, const Card& aCard);
    // Card initialising constructor.
    Card(TheCardsValue ValueIs = Ace, SuitOfTheCard SuitIs = Spades, bool IfTheCardIsFacingUp = true);
    //set value of cards, if TheCardsValue > 10 then == 10 (for jack queen and king value)
    int GetValue() const;
    //flip card for dealer to hide one or expose the hidden card
    void FlipCardOver();

private:
    TheCardsValue _Value;
    SuitOfTheCard _Suit;
    bool TheCardIsFacingUp;
};

class HandOfCards: public Card{
public:
    //reserves 5 spaces for cards in vector _CardsInHand
    HandOfCards();
    //pushes card into _CardsInHand
    void AddACardToHand(Card* CardInDeck);
    //Deletes cards in hand using iterator
    void ClearHand();
    //returns total values if the hand is < 11 ace is 11.
    int TotalValue() const;
    virtual ~HandOfCards();

protected:
    std::vector <Card*> _CardsInHand;
};


class GenericPlayer : public HandOfCards{
    friend std::ostream& operator<<(std::ostream& os, const GenericPlayer& aGenericPlayer);
public:
    //Give the player a name
    GenericPlayer(const std::string& NameOfPlayer = "");
    virtual bool DoesHit() const = 0;
    //Returns true if TotalValue > 21
    bool IsBust() const;
    //Returns true if TotalValue == 21
    bool IsBlackJack() const;
    // out put _ Name bust name is player name from input
    void Bust();
    virtual ~GenericPlayer();


protected:
    std::string _Name;
    float BankRoll = 1000;
    float _bet = 0;





};

class Player : public GenericPlayer{
public:
    Player(const std::string& NameOfPlayer = "");
    virtual bool DoesHit() const;
    //Minus bet from bankroll
    void Bet(float wager);
    //Prompts user for bet
    void Betup();
    //Win bet gets 2*initial bet
    void winsBet();
    //returns 2*bet + bet/2
    void BlackJackWin();
    //bankroll does not change from void bet function
    void losesBet();
    //returns original bet
    void tieBet();
    //shows bank roll
    void ShowBankRoll();
    //checks if player bet more than 5, less than bank roll returns 0 if no money.
    bool BetCorrect(float bet);
    virtual ~Player();

};

class Dealer : public GenericPlayer{
public:
    Dealer(const std::string& name = "Dealer");
    //Dealer hits if above TotalValue <= 16
    virtual bool DoesHit() const;
    //Hides the dealer card
    void FlipFirstCard();
    virtual ~Dealer();
};

class Sydney : public GenericPlayer{
public:
    Sydney(const std::string& name = "Safe Sydney");
    //Hits if totalvalue is <= 11
    virtual bool DoesHit() const;
    //same as player but for bot (Repetitive code)
    void BotOneWins();
    void BotOneBlackJack();
    void BotOneLoses();
    void BotOneTies();
    void ShowBotOneBankRoll();
    void ShowBotOneBet();
    virtual ~Sydney();
protected:
    int _BotOneBankRoll = 1000;
    int _BotOneBet = 10;

};

class Alex : public GenericPlayer{
public:
    Alex(const std::string& name = "All in Alex");
    //Hits if TotalValue != 21
    virtual bool DoesHit() const;
    //same as player but for bot (Repetitive code)
    void BotTwoWins();
    void BotTwoBlackJack();
    void BotTwoLoses();
    void BotTwoTies();
    void ShowBotTwoBankRoll();
    void ShowBotTwoBet();
    virtual ~Alex();
protected:
    int _BotTwoBankRoll = 1000;
    int _BotTwoBet = 10;

};

class DeckOfCards : public HandOfCards
{
public:
    //reserves 52 spaces for cards
    DeckOfCards();
    //pushes card into deck
    void FillTheDeck();
    //shuffles deck using random_shuffle
    void Shuffle();
    //deals cards and refills deck if the deck is empty
    void DealACard(HandOfCards& AHandInPlay);
    // if the player is not bust continue to deal
    //uses bust statement if the player goes but outputs bust
    void ContinueToDeal(GenericPlayer& aGenericPlayer);
    virtual ~DeckOfCards();
};


#endif //THEACTUALFINALPROJECTBLACKJACK_CARD_H
