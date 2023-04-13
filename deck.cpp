#include "deck.h"

#include <QTime>
#include <random>

Deck::Deck(QWidget* parent)
{
    //filling deck wih cards
    for (int suit = 0; suit  < 4; ++suit ) {
        for (int rank = 0; rank < 13; ++rank) {
            cards.append(Card{static_cast<Suit>(suit),
                          static_cast<Rank>(rank+1),deck_pos,parent});
        }
    }
    Shuffle();
}

Card Deck::TakeCard()
{
    return cards.takeLast();
}

void Deck::Shuffle()
{
      std::random_device rd;
      std::mt19937 rng(rd());

      int n = cards.size();
      for (int i = n - 1; i > 0; --i)
      {
          std::uniform_int_distribution<int> uni(0, i);
          int j = uni(rng);

          Card temp = cards[i];
          cards[i] = cards[j];
          cards[j] = temp;
      }
}

QPoint Deck::getDeckPos() const
{
    return deck_pos;
}

void Deck::AddCard(Card card)
{
    cards.append(card);
}
