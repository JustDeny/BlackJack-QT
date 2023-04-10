#ifndef PLAYER_H
#define PLAYER_H


#include <QGridLayout>
#include <QTimer>
#include "deck.h"
#include "card.h"
#include <QPropertyAnimation>


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
    const QPoint player_deck_pos = QPoint(80,300); //it's where first card will be placed and acordingly next ones will be in line
    std::shared_ptr<Deck> common_deck;
    QPropertyAnimation* animation;
    bool in_progress = false;
};

#endif // PLAYER_H
