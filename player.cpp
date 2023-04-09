#include "player.h"



Player::Player(QWidget* parent, std::shared_ptr<Deck> deck):
    score{0}, balance{1500}, ace_count{0},grid_widget{parent},
    common_deck{deck}
{

    taken_cards.append(common_deck->TakeCard());
    taken_cards.append(common_deck->TakeCard());
    card_grid.setContentsMargins(0, 0, 0, 0);
    int spacing = 2;
    card_grid.setSpacing(spacing);
    card_grid.addWidget(&taken_cards[0],0,0);
    card_grid.addWidget(&taken_cards[1],0,1);

    const int widget_width = taken_cards.constFirst().getFrontTexturePixmap().width()+spacing;
    const int widget_height= taken_cards.constFirst().getFrontTexturePixmap().height();
    std::cout << widget_width << " " << widget_height << std::endl;
    grid_widget.setFixedSize(widget_width*taken_cards.size(),widget_height);
    grid_widget.setStyleSheet("border: 1px solid red;");
    grid_widget.move(200,300);
    grid_widget.setLayout(&card_grid);
}

void Player::hit()
{
    taken_cards.append(common_deck->TakeCard());
    card_grid.addWidget(&taken_cards.last(),0,2);
}
