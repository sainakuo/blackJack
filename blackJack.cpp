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
    ACE = 1,
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
    KING = 10
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

    int GetValue() const {

        if (!faceUp)
            return 0;

        return value;
    }

    friend ostream& operator<<(ostream& output, const Card card);

};

ostream& operator<<(ostream& output, const Card card) {
    const string VALUES[] = { "-", "A", "2", "3", "4", "5", "6", "7", "8", "9","10", "J", "Q", "K" };
    const string SUITS[] = { "h", "d", "c", "s" };

    if (!card.faceUp)
    {
        output << "XX";
    }
    else
    {
        output << VALUES[card.value] << SUITS[card.suit] << endl;
    }
    return output;
}

class Hand {
protected:
    vector<Card*> cards;
public:
    Hand() {};
    Hand(vector<Card*> inCards) : cards(inCards) {};
    void Add(Card* card) {
        cards.push_back(card);
    }

    void Clear() {
        vector<Card*>::iterator it;
        for (it = cards.begin(); it != cards.end(); it++) {
            delete* it;
            *it = 0;
        }
        cards.clear();
    }

    int GetTotal() const {
        int sum = 0;
        for (int i = 0; i < cards.size(); i++)
        {
            if (cards[i]->GetValue() == ACE && (sum + 11) <= 21)
                sum += 11;
            else
                sum += cards[i]->GetValue();
        }
        return sum;
    }
};

class GenericPlayer : public Hand {
protected:
    string name;
public: 
    GenericPlayer(string inName) : name(inName) {}
    virtual bool isHitting() const = 0;
    bool isBoosted() const {
        return (GetTotal() > 21);
    }
    

    void Bust() {
            cout << name << ", " << "your hand is boosted!" << endl;
    }

    friend ostream& operator<<(ostream& output, const GenericPlayer& player);
};

ostream& operator<<(ostream& output, const GenericPlayer& player) {
    output << player.name << ": ";
    if (player.cards.empty())
    {
        output << "Hand is empty!" << endl;
        return output;
    }
    else
    {
        vector<Card*>::const_iterator it;

        for (it = player.cards.begin(); it != player.cards.end(); it++)
        {
            output << **it << " ";
        }

        if (player.GetTotal() != 0)
            output << " sum: " << player.GetTotal() << endl;

    }

    return output;
}

class Player : public GenericPlayer {
public: 
    Player(string inName): GenericPlayer(inName) {}

    virtual bool isHitting() const {
        char answer;
        cout << "Do you need one more Card? Y/N" << endl;
        cin >> answer;

        return (answer == 'Y' || answer == 'y');
    }

    void Win() const {
        cout << name << ", congrats! You win!" << endl;
    }

    void Lose() const {
        cout << name << ", sorry! You losed!" << endl;
    }

    void Push() const {
        cout << name << "! You drew!" << endl;
    }

};

class House : public GenericPlayer {
public: 
    House(string inName): GenericPlayer(inName) {}
    virtual bool isHitting() const {

        return (GetTotal() <= 16);

    }

    void FlipFirstCard() {
        if (cards.empty())
            cout << "Hand is empty!" << endl;
        else
            (**cards.begin()).Flip();
    }
};

int main()
{
    Card card1(HEARTS, NINE, 0);
    Card card2(CLUBS, TWO, 0);
    Card card3(HEARTS, ACE, 1);

    Card* pCard1 = &card1;
    Card* pCard2 = &card2;
    Card* pCard3 = &card3;

    Hand hand;

    hand.Add(pCard1);
    hand.Add(pCard2);
    hand.Add(pCard3);

    cout << card1 << " " << card2 << " " << card3;

    cout << "sum of cards: " << hand.GetTotal() << endl;
};
