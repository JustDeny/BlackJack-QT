#ifndef DECK_H
#define DECK_H

#include<QPainter>
#include "card.h"

class Deck
{
public:
    Deck(QWidget* parent = nullptr);
    void Draw(QPainter& qp);
    Card TakeCard();
private:
    QList<Card> cards;
};

#endif // DECK_H
