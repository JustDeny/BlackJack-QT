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
    virtual void hit();
    virtual ~Player() = default;
    void Init();
    int getScore();
    void addScore(const Card& card);
    int getBalance() const;
    void Reset();
    void setBalance(int newBalance);

protected:
    QList<Card> taken_cards;
    int score;
    int balance;
    int ace_count=0;
    std::shared_ptr<Deck> common_deck;
    std::unique_ptr<QPropertyAnimation> animation;
private:
    const QPoint player_deck_pos = QPoint(200,300); //it's where first card will be placed and acordingly next ones will be in line
};

#endif // PLAYER_H
