#include "player.h"

#include <QEventLoop>


Player::Player(QWidget* parent, std::shared_ptr<Deck> deck):
    score{0}, balance{1500}, ace_count{0}, common_deck{deck},
    animation{std::make_unique<QPropertyAnimation>()}
{
    taken_cards.reserve(52);
    animation->setPropertyName("pos");
}

void Player::hit()
{
    QPoint offset;
    QPoint prev_card_pos{0,0};
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
    target.show();

    animation->setTargetObject(&target);
    animation->setDuration(300);
    animation->setStartValue(target.pos());
    animation->setEndValue(offset);

    QEventLoop loop;
    QObject::connect(animation.get(), &QPropertyAnimation::finished, &loop, &QEventLoop::quit);
    animation->start();
    loop.exec();
}

void Player::Init()
{
    hit();
    hit();
}

