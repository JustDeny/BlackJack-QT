#ifndef CARD_H
#define CARD_H

#include <QLabel>
#include <iostream>

enum class Suit:int { Clubs, Diamonds, Hearts, Spades };
enum class Rank: int { Ace, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King };

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

       const QPixmap getFrontTexturePixmap()const;

       Suit suit() const;
       Rank rank() const;
       bool isFaceUp() const;

       static QPixmap getCardImage(Suit suit, Rank rank);

       int getCardWidth() const;
       int getCardHeight() const;

private:
       Suit m_suit;
       Rank m_rank;
       bool m_faceUp;
       QPixmap frontTexture;
       int card_width;
       int card_height;
       //QPixmap BackTexture;
};

#endif // CARD_H
