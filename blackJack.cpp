#include <iostream>

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

int main()
{
    Card card(HEARTS, ACE, 0);
    cout << card.GetValue() << endl;
};
