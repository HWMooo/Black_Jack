//
// Created by Harry Moore
//
#include <iostream>
#include "Card.h"

Card::Card(TheCardsValue ValueIs, SuitOfTheCard SuitIs, bool IfTheCardIsFacingUp): _Value(ValueIs), _Suit(SuitIs), TheCardIsFacingUp(IfTheCardIsFacingUp){
}

int Card::GetValue() const{
    int value = 0;
    if (TheCardIsFacingUp){
        value = _Value;
        if (value > 10) value = 10;
    }
    return value;
}

void Card::FlipCardOver(){
    TheCardIsFacingUp = !(TheCardIsFacingUp);
}

HandOfCards::HandOfCards(){
    _CardsInHand.reserve(5);
}

HandOfCards::~HandOfCards(){
    ClearHand();
}

void HandOfCards::AddACardToHand(Card *CardInDeck){
    _CardsInHand.push_back(CardInDeck);
}

void HandOfCards::ClearHand(){
    std::vector <Card*>::iterator iter;
    for (iter = _CardsInHand.begin(); iter != _CardsInHand.end(); ++iter){
        delete *iter;
        *iter = 0;
    }
    _CardsInHand.clear();
}

int HandOfCards::TotalValue() const{
    if (_CardsInHand.empty()) {
        return 0;
    }
    if (_CardsInHand[0]->GetValue() == 0) {
        return 0;
    }

    int TotalSum = 0;
    std::vector<Card*>::const_iterator iter;
    for (iter = _CardsInHand.begin(); iter != _CardsInHand.end(); ++iter) {
        TotalSum += (*iter)->GetValue();
    }

    bool HandContainsAnAce = false;
    for (iter = _CardsInHand.begin(); iter != _CardsInHand.end(); ++iter) {
        if ((*iter)->GetValue() == Card::Ace) {
            HandContainsAnAce = true;
        }
    }

    if (HandContainsAnAce && TotalSum <= 11){
        TotalSum += 10;
    }

    return TotalSum;
}

GenericPlayer::GenericPlayer(const std::string& NameOfPlayer): _Name(NameOfPlayer) {
}


bool GenericPlayer::IsBust() const{
    return (TotalValue() > 21);
}

void GenericPlayer::Bust(){
    if(_Name == "Dealer" || _Name == "All in Alex" || _Name == "Safe Sydney"){
        std::cout << _Name << " busts." << std::endl;
    }
    else {
        BankRoll -= _bet;
        std::cout << _Name << " busts, new BankRoll £" << BankRoll << std::endl;
    }
}

GenericPlayer::~GenericPlayer() {
}

bool GenericPlayer::IsBlackJack() const {
    return (TotalValue() == 21);
}


Player::Player(const std::string& NameOfPlayer): GenericPlayer(NameOfPlayer) {
}

bool Player::DoesHit() const{
    std::cout << _Name << ", would you like to hit? (Y/N) :";
    char response;
    std::cin >> response;
    return (response == 'y' || response == 'Y');
}


Player::~Player() {}

void Player::Bet(float wager){
    _bet = wager;
    BankRoll -= _bet;

}

void Player::winsBet() {
    BankRoll += _bet * 2;
    std::cout << _Name << " Wins, new bankRoll £" << BankRoll << std::endl;


}

void Player::ShowBankRoll() {
    std::cout << _Name << ", Has £" << BankRoll << " in the bank" << std::endl;

}

bool Player::BetCorrect(float wager){
    if(BankRoll < 5){
        std::cout << _Name << " you are out of money " << std::endl;
        exit(0);
    }
    if(wager < 5 || wager > BankRoll){
        return false;
    }

    else{
        return true;
    }

}

void Player::Betup() {
    std::cout << _Name << ", Please place a bet (Minimum £5) : £";
}

void Player::losesBet() {
    std::cout << _Name << " Loses, new bankRoll £" << BankRoll << std::endl;

}

void Player::tieBet() {
    BankRoll += _bet;
    std::cout << _Name << " Ties, new bankRoll £" << BankRoll << std::endl;

}

void Player::BlackJackWin() {
    BankRoll += (_bet*2)+(_bet/2);
    std::cout << _Name << ", got Black Jack, new bankRoll £" << BankRoll << std::endl;
}


Dealer::Dealer(const std::string& NameOfPlayer): GenericPlayer(NameOfPlayer) {
}

bool Dealer::DoesHit() const{
    return (TotalValue() <= 16);
}

void Dealer::FlipFirstCard(){
    if (!_CardsInHand.empty()) {
        _CardsInHand[0]->FlipCardOver();
    }
    else {
        std::cout << "No card to flip!\n";
    }
}

Dealer::~Dealer() {
}

DeckOfCards::DeckOfCards(){
    _CardsInHand.reserve(52);
    FillTheDeck();
}

DeckOfCards::~DeckOfCards(){
}

void DeckOfCards::FillTheDeck(){
    ClearHand();

    for (int suit = Card::Clubs; suit <= Card::Spades; ++suit){
        for (int value = Card::Ace; value <= Card::King; ++value){
            AddACardToHand(new Card(static_cast <Card::TheCardsValue >(value),static_cast <Card::SuitOfTheCard >(suit)));
        }
    }
}

void DeckOfCards::Shuffle(){
    random_shuffle(_CardsInHand.begin(), _CardsInHand.end());
}

void DeckOfCards::DealACard(HandOfCards& AHandInPlay){
    if (!_CardsInHand.empty()){
        AHandInPlay.AddACardToHand(_CardsInHand.back());
        _CardsInHand.pop_back();
    }
    else{
        std::cout << "New deck on the table." << std::endl;

        for (int suit = Card::Clubs; suit <= Card::Spades; ++suit){
            for (int value = Card::Ace; value <= Card::King; ++value){
                AddACardToHand(new Card(static_cast <Card::TheCardsValue >(value),static_cast <Card::SuitOfTheCard >(suit)));
            }
        }
        Shuffle();
    }
}

void DeckOfCards::ContinueToDeal(GenericPlayer &aGenericPlayer){
    std::cout << std::endl;
    while (!(aGenericPlayer.IsBust()) && aGenericPlayer.DoesHit()){
        DealACard(aGenericPlayer);
        std::cout << aGenericPlayer << std::endl;

        if (aGenericPlayer.IsBust()) {
            aGenericPlayer.Bust();
        }

    }
}

Sydney::Sydney(const std::string &name) : GenericPlayer(name) {

}

bool Sydney::DoesHit() const {
    return (TotalValue() <= 11);
}


Sydney::~Sydney() {

}

void Sydney::ShowBotOneBet() {
    _BotOneBankRoll -= _BotOneBet;
    std::cout << _Name << " bets £" << _BotOneBet << std::endl;

}

void Sydney::ShowBotOneBankRoll() {
    std::cout << _Name << " Has £" << _BotOneBankRoll << std::endl;

}

void Sydney::BotOneWins() {
    _BotOneBankRoll += 2*_BotOneBet;
    std::cout << _Name << ", wins! new bankroll £" << _BotOneBankRoll << std::endl;

}

void Sydney::BotOneBlackJack() {
    _BotOneBankRoll += (2*_BotOneBet)+5;
    std::cout << _Name << ", black jack! new bankroll £" << _BotOneBankRoll << std::endl;

}

void Sydney::BotOneLoses() {
    _BotOneBankRoll -= _BotOneBet;
    std::cout << _Name << ", loses! new bankroll £" << _BotOneBankRoll << std::endl;
}

void Sydney::BotOneTies() {
    _BotOneBankRoll += _BotOneBet;
    std::cout << _Name << ", ties! new bankroll £" << _BotOneBankRoll << std::endl;

}


Alex::Alex(const std::string &name) : GenericPlayer(name) {

}

Alex::~Alex() {

}

bool Alex::DoesHit() const {
    return (TotalValue() < 21);
}

void Alex::ShowBotTwoBet() {
    _BotTwoBankRoll -= _BotTwoBet;
    std::cout << _Name << " bets £" << _BotTwoBet << std::endl;

}

void Alex::ShowBotTwoBankRoll() {
    std::cout << _Name << " Has £" << _BotTwoBankRoll << std::endl;
}

void Alex::BotTwoTies() {
    _BotTwoBankRoll += _BotTwoBet;
    std::cout << _Name << ", loses! new bankroll £" << _BotTwoBankRoll << std::endl;


}

void Alex::BotTwoLoses() {
    _BotTwoBankRoll -= _BotTwoBet;
    std::cout << _Name << ", loses! new bankroll £" << _BotTwoBankRoll << std::endl;

}

void Alex::BotTwoBlackJack() {
    _BotTwoBankRoll += (2*_BotTwoBet)+5;
    std::cout << _Name << ", black jack! new bankroll £" << _BotTwoBankRoll << std::endl;

}

void Alex::BotTwoWins() {
    _BotTwoBankRoll += 2*_BotTwoBet;
    std::cout << _Name << ", wins! new bankroll £" << _BotTwoBankRoll << std::endl;
}



