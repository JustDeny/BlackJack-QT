#include "player.h"

#include <QEventLoop>
#include <thread>

using namespace std::chrono_literals;





Player::Player(QWidget* parent, std::shared_ptr<Deck> deck):
    score{0}, balance{1500}, ace_count{0}, common_deck{deck},
    animation{new QPropertyAnimation()}
{
    taken_cards.reserve(52);
    animation->setPropertyName("pos");
    hit();
    hit();
}

void Player::hit()
{
    QPoint prev_card_pos{0,0};
    if(!taken_cards.empty())
        prev_card_pos = taken_cards.last().geometry().topLeft();

    taken_cards.append(common_deck->TakeCard());
    Card& target = taken_cards.last();
    target.show();

    animation->setTargetObject(&target);
    animation->setDuration(300);
    animation->setStartValue(target.pos());
    int shift = 30;
    QPoint offset = QPoint(prev_card_pos.x()-shift,0)+player_deck_pos;
    animation->setEndValue(offset);
    QObject::connect(animation, &QPropertyAnimation::finished, [&](){
        animation->stop();
    });
    QEventLoop loop;
    QObject::connect(animation, &QPropertyAnimation::finished, &loop, &QEventLoop::quit);
    animation->start();

    loop.exec();

    //std::this_thread::sleep_for(500ms);
}

