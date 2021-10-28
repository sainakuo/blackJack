#include <iostream>
#include <vector>

using namespace std;

enum Suit {
    HEARTS, //червы
    DIAMONDS, //бубны
    CLUBS, //трефы 
    SPADES //пики
};

enum Value {
    TWO = 2,
    THREE = 3,
    FOUR = 4,
    FIVE = 5,
    SIX = 6,
    SEVEN = 7,
    EIGHT = 8,
    NINE = 9,
    TEN = 10,
    JACK = 10,
    QUEEN = 10,
    KING = 10,
    ACE = 1
};

class Card {
private:
    Suit suit;
    Value value;
    bool faceUp; // 1 - лицом вверх, 0 - лицом вниз

public: 
    Card(Suit inSuit, Value inValue, bool inFaceUp) : suit(inSuit), value(inValue), faceUp(inFaceUp) {};

    void Flip() {
        faceUp = !faceUp;
    }

    Value GetValue() const {
        return value;
    }

};

class Hand {
private:
    vector<Card*> cards;
public:
    Hand() {};
    Hand(vector<Card*> inCards) : cards(inCards) {};
    void Add(Card* card) {
        cards.push_back(card);
    }

    void Clear() {
        cards.clear();
    }

    int GetValue() const {
        int sum = 0;
        for (int i = 0; i < cards.size(); i++)
        {
            sum = sum + cards[i]->GetValue();
        }
        return sum;
    }


};

int main()
{
    Card card1(HEARTS, NINE, 0);
    Card card2(CLUBS, TWO, 0);
    Card card3(HEARTS, THREE, 1);

    Card* pCard1 = &card1;
    Card* pCard2 = &card2;
    Card* pCard3 = &card3;

    Hand hand;

    hand.Add(pCard1);
    hand.Add(pCard2);
    hand.Add(pCard3);

    cout << "sum of cards: " << hand.GetValue() << endl;
};
