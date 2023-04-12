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
    void Shuffle();
    QPoint getDeck_pos() const;
    void AddCard(Card card);
private:
    QList<Card> cards;
    const QPoint deck_pos = QPoint(562,6);
};

#endif // DECK_H
