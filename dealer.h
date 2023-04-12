#ifndef DEALER_H
#define DEALER_H

#include "player.h"



class Dealer: public Player
{
public:
    Dealer(QWidget* parent, std::shared_ptr<Deck> deck);
    void hit() override;
    void Init();
    void RevealCard();
    void getAdditionalCards();
private:
    const QPoint dealer_deck_pos = QPoint{900,300};
};

#endif // DEALER_H
