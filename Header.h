#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

class Card {
public:
    enum Suit;
    enum Value;

    Card(Suit inSuit, Value inValue, bool inFaceUp) : suit(inSuit), value(inValue), faceUp(inFaceUp) {};
    void Flip();
    int GetValue() const;
    friend std::ostream& operator<<(std::ostream& output, const Card& card);

private:
    Suit suit;
    Value value;
    bool faceUp; // 1 - лицом вверх, 0 - лицом вниз
};

class Hand {
protected:
    std::vector<Card*> cards;

public:
    Hand() {};
    Hand(std::vector<Card*>& inCards) : cards(inCards) {};
    void Add(Card* card);

    void Clear();

    int GetTotal() const;
};

class GenericPlayer : public Hand {
protected:
    std::string name;
public:
    GenericPlayer(std::string inName) : name(inName) {}
    virtual bool isHitting() const = 0;
    bool isBoosted() const;
    void Bust() const;
    friend std::ostream& operator<<(std::ostream& output, const GenericPlayer& player);
};

class Player : public GenericPlayer {
public:
    Player(std::string inName) : GenericPlayer(inName) {}
    virtual bool isHitting() const;
    void Win() const;
    void Lose() const;
    void Push() const;
};

class House : public GenericPlayer {
public:
    House(std::string inName = "House") : GenericPlayer(inName) {}
    virtual bool isHitting() const;
    void FlipFirstCard();
};

class Deck : public Hand {
public:
    Deck();

    void Populate();

    void Shuffle();

    void Deal(Hand& aHand);

    void AdditionalCards(GenericPlayer& aGenericPlayer);
};

class Game {
private:
    Deck deck;
    House dealer;
    std::vector<Player> players;
public:
    Game(const std::vector<std::string>& names);

    void Play();
};