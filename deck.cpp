#include "deck.h"

Deck::Deck(QWidget* parent)
{
    //filling deck wih cards
    for (int suit = 0; suit  < 4; ++suit ) {
        for (int rank = 0; rank < 13; ++rank) {
            cards.append(Card{static_cast<Suit>(suit),
                          static_cast<Rank>(rank),QPoint(562,6),parent});
        }
    }
}

void Deck::Draw(QPainter& qp)
{
    for (int i = 0; i < 52; ++i) {
        qp.drawPixmap(0+i*10,0,cards[i].getFrontTexturePixmap());
    }
}

Card Deck::TakeCard()
{
    if(!cards.empty())
        return cards.takeLast();
    return Card{nullptr};
}
