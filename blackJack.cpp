#include "Header.h"

enum Card::Suit {
    HEARTS,
    DIAMONDS, 
    CLUBS, 
    SPADES 
};

enum Card::Value { 
    ACE = 1, 
    TWO, 
    THREE, 
    FOUR, 
    FIVE, 
    SIX,
    SEVEN, 
    EIGHT, 
    NINE, 
    TEN, 
    JACK, 
    QUEEN, 
    KING
};

void Card::Flip() {
    faceUp = !faceUp;
}

int Card::GetValue() const {

    if (!faceUp)
        return 0;

    if (value == JACK || value == QUEEN || value == KING)
        return 10;

    return value;
}

std::ostream& operator<<(std::ostream& output, const Card& card) {
    const std::string VALUES[] = { "-", "A", "2", "3", "4", "5", "6", "7", "8", "9","10", "J", "Q", "K" };
    const std::string SUITS[] = { "h", "d", "c", "s" };

    if (!card.faceUp)
    {
        output << "XX" ;
    }
    else
    {
        output << VALUES[card.value] << SUITS[card.suit] ;
    }
    return output;
}


void Hand::Add(Card* card) {
    cards.push_back(card);
}

void Hand::Clear() {
    std::vector<Card*>::iterator it;
    for (it = cards.begin(); it != cards.end(); it++) {
        delete* it;
        *it = 0;
    }
    cards.clear();
}

int Hand::GetTotal() const {
    int sum = 0;
    for (int i = 0; i < cards.size(); i++)
    {
        if (cards[i]->GetValue() == Card::ACE && (sum + 11) <= 21)
            sum += 11;
        else 
            sum += cards[i]->GetValue();
    }
    return sum;
}

bool GenericPlayer::isBoosted() const {
    return (GetTotal() > 21);
}
    
void GenericPlayer::Bust() const {
    std::cout << std::endl;
    std::cout << name << ", " << "your hand is boosted!" << std::endl;
}

std::ostream& operator<<(std::ostream& output, const GenericPlayer& player) {
    output << std::endl;
    output << player.name << ": ";
    if (player.cards.empty())
    {
        output << "Hand is empty!" << std::endl;
        return output;
    }
    else
    {
        std::vector<Card*>::const_iterator it;

        for (it = player.cards.begin(); it != player.cards.end(); it++)
        {
            output << **it << " ";
        }

        if (player.GetTotal() != 0)
            output << " sum: " << player.GetTotal();

    }
    return output;
}

bool Player::isHitting() const {
    char answer;

    if (GetTotal() != 21)
    {
        std::cout << std::endl;
        std::cout << name << ", do you need one more Card? Y/N" << std::endl;
        std::cin >> answer;

        return (answer == 'Y' || answer == 'y');
    }
    else
    {
        return false;
    }
}

void Player::Win() const {
    std::cout << std::endl;
    std::cout << name << ", congrats! You win!" << std::endl;
}

void Player::Lose() const {
    std::cout << std::endl;
    std::cout << name << ", sorry! You losed!" << std::endl;
}

void Player::Push() const {
    std::cout << std::endl;
    std::cout << name << "! You drew!" << std::endl;
}

bool House::isHitting() const {

    return (GetTotal() <= 16);

}

void House::FlipFirstCard() {
    if (cards.empty())
        std::cout << "Hand is empty!" << std::endl;
    else
        (**cards.begin()).Flip();
}

Deck::Deck() {
    Populate();
}

void Deck::Populate() {
    Clear();

    for (int s = Card::HEARTS; s <= Card::SPADES; s++)
    {
        for (int v = Card::ACE; v <= Card::KING; v++)
        {            
            Add(new Card(static_cast<Card::Suit>(s), static_cast<Card::Value>(v), 1));
        }
    }
}

void Deck::Shuffle() {
    random_shuffle(cards.begin(), cards.end());
}

void Deck::Deal(Hand& aHand) {
    if (!(cards.empty()))
    {
        aHand.Add(cards.back());
        cards.pop_back();
    }
    else
    {
        std::cout << "there are not cards on deck " << std::endl;
    }
}

void Deck::AdditionalCards(GenericPlayer& aGenericPlayer) {
    while (!(aGenericPlayer.isBoosted()) && aGenericPlayer.isHitting())
    {
        Deal(aGenericPlayer);
        std::cout << aGenericPlayer;

        if (aGenericPlayer.isBoosted())
        {
            aGenericPlayer.Bust();
        }
    }
}


Game::Game(const std::vector<std::string>& names) {
    std::vector<std::string>::const_iterator it;
    for (it = names.begin(); it != names.end(); it++)
    {
        players.push_back(Player(*it));
    }

    deck.Populate();
    srand(static_cast<unsigned int>(time(0))); //генератор случайных чисел
    deck.Shuffle();
}

void Game::Play() {
    std::vector<Player>::iterator it;

    for (int i = 0; i < 2; i++)
    {
        for (it = players.begin(); it != players.end(); it++)
        {
            deck.Deal(*it);
        }
        deck.Deal(dealer);
    }

    dealer.FlipFirstCard();
       
    for (it = players.begin(); it != players.end(); it++)
    {
        std::cout << *it;
    }

    std::cout << dealer;


    for (it = players.begin(); it != players.end(); it++)
    {
        deck.AdditionalCards(*it);
    }

    dealer.FlipFirstCard();
    std::cout << dealer;

    deck.AdditionalCards(dealer);

    if (dealer.isBoosted())
    {
        for (it = players.begin(); it != players.end(); it++)
        {
            if (!(it->isBoosted()))
            {
                it->Win();
            }
        }
    }
    else {
        for (it = players.begin(); it != players.end(); it++)
        {
            if (!(it->isBoosted()))
            {
                if (it->GetTotal() == dealer.GetTotal())
                    it->Push();
                else if (it->GetTotal() > dealer.GetTotal())
                    it->Win();
                else
                    it->Lose();
            }
        }
               
    }

    for (it = players.begin(); it != players.end(); it++)
    {
        it->Clear();
    }

    dealer.Clear();
}

int main()
{
    std::vector<std::string> players{"Ivan", "Saina"};
   
    char answer = 'Y';
    do {
        Game game(players);
        game.Play();
        std::cout << std::endl << "Do you want to play again? Y/N" << std::endl;
        std::cin >> answer;
    } while (answer == 'Y' || answer == 'y');

    return 0;
};
