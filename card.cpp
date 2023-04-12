#include "card.h"

#include <QGraphicsDropShadowEffect>

Card::Card(QWidget *parent)
{
    setAutoFillBackground(false);
}

Card::Card(Suit suit, Rank rank,QPoint pos, QWidget *parent) :
    QLabel(parent), m_suit(suit), m_rank(rank), m_faceUp(false)
{
    frontTexture = getCardImage(suit, rank);
    backTexture.load("../BlackJack/images/cards/backcard.png");
    backTexture= backTexture.scaled(backTexture.width() * 1.5, backTexture.height() * 1.5,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setPixmap(backTexture);
    card_width = pixmap().width();
    card_height = pixmap().height();
    move(pos);
    setStyleSheet("border: 1px solid grey");
    is_ace = rank==Rank::Ace?true:false;
    QWidget qw;

}

Card::Card(const Card &other)
{
    *this = other;
}

Card::Card(Card &&other)
{
    *this = other;
}

Card &Card::operator=(const Card &other)
{
    setParent(other.parentWidget());
    setText(other.text());
    m_suit=other.m_suit;
    m_rank = other.m_rank;
    m_faceUp = other.m_faceUp;
    frontTexture = other.frontTexture;
    backTexture = other.backTexture;
    setPixmap(backTexture);
    card_width= other.card_width;
    card_height=other.card_height;
    move(other.pos());
    is_ace=other.is_ace;
}

void Card::setSuit(Suit suit)
{
    m_suit = suit;
    frontTexture = getCardImage(m_suit, m_rank);
    setPixmap(frontTexture);
}

void Card::setRank(Rank rank)
{
    m_rank = rank;
    frontTexture= getCardImage(m_suit, m_rank);
    setPixmap(frontTexture);
}

void Card::setFaceUp(bool faceUp)
{
    if (!m_faceUp) {
        setPixmap(frontTexture);
    }
    else{
        setPixmap(backTexture);
    }
    m_faceUp = faceUp;
}

const QPixmap Card::getFrontTexturePixmap() const
{
    return frontTexture;
}

bool Card::isAce() const
{
    return is_ace;
}

QPixmap Card::getCardImage(Suit suit, Rank rank)
{
    QString suitStr;
    QString rankStr;
    //there is a name convention of cards: rank_suit.png so that to simplify way of loading pixmaps of images
    switch (suit) {
            case Suit::Clubs:
                suitStr = "c";
                break;
            case Suit::Diamonds:
                suitStr = "d";
                break;
            case Suit::Hearts:
                suitStr = "h";
                break;
            case Suit::Spades:
                suitStr = "s";
                break;
            default:
                std::cerr << "Invalid suit argument\n";
                break;
        }

        switch (rank) {
            case Rank::Ace:
                rankStr = "a";
                break;
            case Rank::Two:
                rankStr = "2";
                break;
            case Rank::Three:
                rankStr = "3";
                break;
            case Rank::Four:
                rankStr = "4";
                break;
            case Rank::Five:
                rankStr = "5";
                break;
            case Rank::Six:
                rankStr = "6";
                break;
            case Rank::Seven:
                rankStr = "7";
                break;
            case Rank::Eight:
                rankStr = "8";
                break;
            case Rank::Nine:
                rankStr = "9";
                break;
            case Rank::Ten:
                rankStr = "10";
                break;
            case Rank::Jack:
                rankStr = "j";
                break;
            case Rank::Queen:
                rankStr = "q";
                break;
            case Rank::King:
                rankStr = "k";
                break;
            default:
                std::cerr << "Invalid rank argument\n";
                break;
        }
    QString filename = "../BlackJack/images/cards/"+rankStr+"_"+suitStr+".png";
    QPixmap pixmap;
    pixmap.load(filename);
    pixmap = pixmap.scaled(pixmap.width() * 1.5, pixmap.height() * 1.5,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    return pixmap;
}

int Card::getCardWidth() const
{
    return card_width;
}

int Card::getCardHeight() const
{
    return card_height;
}

int Card::getCardValue() const
{
    if(is_ace){
        return 11;
    }
    if(static_cast<int>(m_rank) > static_cast<int>(Rank::Ten))
        return 10;
    return static_cast<int>(m_rank);    //else return rank value of numbers which starts from 1 in Rank enum class
}
