#ifndef CARD_H
#define CARD_H

#include <QLabel>

enum class Suit:int { Clubs, Diamonds, Hearts, Spades };
enum class Rank: int { Ace=1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King };

class Card : public QLabel
{
    Q_OBJECT
   public:
       explicit Card(QWidget* parent);
       explicit Card(Suit suit, Rank rank, QPoint pos, QWidget *parent = nullptr);
       Card(const Card& other);
       Card(Card&& other);
       Card& operator=(const Card& card);

       void setSuit(Suit suit);
       void setRank(Rank rank);
       void setFaceUp(bool faceUp);

       Suit suit() const;
       Rank rank() const;
       bool isFaceUp() const;
       bool isAce()const;

       static QPixmap getCardImage(Suit suit, Rank rank);

       int getCardWidth() const;
       int getCardHeight() const;
       int getCardValue() const;

private:
       Suit m_suit;
       Rank m_rank;
       bool m_faceUp;
       QPixmap frontTexture;
       QPixmap backTexture;
       int card_width;
       int card_height;
       bool is_ace;
       void loadTextures();
};

#endif // CARD_H
