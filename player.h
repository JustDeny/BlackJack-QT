#ifndef PLAYER_H
#define PLAYER_H


#include <QGridLayout>
#include <deck.h>
#include "card.h"


class Player
{
public:
    Player(QWidget* parent, std::shared_ptr<Deck> deck);
    void hit();
private:
    QList<Card> taken_cards;
    int score;
    int balance;
    int ace_count;
    QWidget grid_widget;
    QGridLayout card_grid;
    std::shared_ptr<Deck> common_deck;
};

#endif // PLAYER_H
