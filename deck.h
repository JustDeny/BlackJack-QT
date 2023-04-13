#ifndef DECK_H
#define DECK_H

#include "card.h"

class Deck
{
public:
    Deck(QWidget* parent = nullptr);
    Card TakeCard();
    void Shuffle();
    QPoint getDeckPos() const;
    void AddCard(Card card);
private:
    QList<Card> cards;
    const QPoint deck_pos = QPoint(562,6);
};

#endif // DECK_H
