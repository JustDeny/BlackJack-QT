#include "dealer.h"

#include <qeventloop.h>

Dealer::Dealer(QWidget *parent, std::shared_ptr<Deck> deck):
    Player{parent,deck}
{
    taken_cards.reserve(52);
    animation->setPropertyName("pos");
}

void Dealer::hit()
{
    QPoint offset;
    if(taken_cards.isEmpty()){
        offset = dealer_deck_pos;
    }
    else{
        auto &prev_card = taken_cards.last();
        offset = prev_card.geometry().topRight();
        offset.setX(offset.x()-30);
    }

    taken_cards.append(common_deck->TakeCard());
    Card& target = taken_cards.last();
    target.show();

    animation->setTargetObject(&target);
    animation->setDuration(300);
    animation->setStartValue(target.pos());
    int shift = 30;

    animation->setEndValue(offset);
    QEventLoop loop;
    QObject::connect(animation.get(), &QPropertyAnimation::finished, &loop, &QEventLoop::quit);
    animation->start();

    loop.exec();
}

void Dealer::Init()
{
    Player::Init();
    taken_cards.last().setFaceUp(true);
    score = taken_cards.last().getCardValue();
}

void Dealer::RevealCard()
{
    taken_cards.first().setFaceUp(true);
    score+=taken_cards.first().getCardValue();
}

void Dealer::getAdditionalCards()
{
    while(score<17){
        hit();
        taken_cards.last().setFaceUp(true);
        score+=taken_cards.last().getCardValue();
    }
}
