#ifndef PLAYER_H
#define PLAYER_H


#include <QTimer>
#include <QGridLayout>
#include <QSoundEffect>
#include <QPropertyAnimation>
#include "deck.h"
#include "card.h"


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
    int score;
    int balance;
    int ace_count;
    QList<Card> taken_cards;
    std::shared_ptr<Deck> common_deck;
    std::unique_ptr<QPropertyAnimation> animation;
    QSoundEffect card_sound;
private:
    const QPoint player_deck_pos = QPoint(200,300); //it's where first card will be placed and acordingly next ones will be in line
};

#endif // PLAYER_H
