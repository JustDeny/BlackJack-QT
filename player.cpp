#include "player.h"

#include <QEventLoop>


Player::Player(QWidget* parent, std::shared_ptr<Deck> deck):
    score{0}, balance{1500}, ace_count{0}, common_deck{deck},
    animation{std::make_unique<QPropertyAnimation>()}
{
    taken_cards.reserve(10);
    animation->setPropertyName("pos");
}

void Player::hit()
{
    QPoint offset;
    if(taken_cards.isEmpty())
    {
        offset = player_deck_pos;
    }
    else{
        offset = taken_cards.last().geometry().topRight();
    }
    int shift = 30;
    offset.setX(offset.x()-shift);

    taken_cards.append(common_deck->TakeCard());
    Card& target = taken_cards.last();
    addScore(target);
    target.show();

    animation->setTargetObject(&target);
    animation->setDuration(300);
    animation->setStartValue(target.pos());
    animation->setEndValue(offset);

    QEventLoop loop;
    QObject::connect(animation.get(), &QPropertyAnimation::finished, &loop, &QEventLoop::quit);
    animation->start();
    loop.exec();
    target.setFaceUp(true);
}

void Player::Init()
{
    hit();
    hit();
}

int Player::getScore()
{
    return score;
}

void Player::addScore(const Card& card)
{
    if (card.isAce())
    {
        ace_count++;
        if (ace_count == 1)
        {
            if ((score + card.getCardValue()) > 21)
            {
                score++;
                ace_count = 0;
            }
            else
                score += card.getCardValue();
        }
        else if (ace_count > 1)
            score++;
    }
    else
    {
        if (ace_count >= 1 && ((score + card.getCardValue()) > 21))
        {
            score += card.getCardValue() - 10;
            ace_count = 0;
        }
        else
            score += card.getCardValue();
    }
}

int Player::getBalance() const
{
    return balance;
}

void Player::Reset()
{
    score = 0;
    ace_count=0;
    for (int i = 0; i<taken_cards.count();i++) {
        taken_cards[i].setFaceUp(false);
        taken_cards[i].move(common_deck->getDeck_pos());
        //taken_cards[i].hide();
        common_deck->AddCard(taken_cards[i]);
    }
    taken_cards.clear();
}

void Player::setBalance(int new_balance)
{
    balance = new_balance;
}

