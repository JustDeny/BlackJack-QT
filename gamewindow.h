#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "card.h"
#include "deck.h"
#include "player.h"

class GameWindow : public QWidget
{
    Q_OBJECT
private:
    const int W_WIDTH = 1200;
    const int W_HEIGHT = 600;

    QImage m_backgroundImage;
    void loadImages();
    bool initGame();
    std::shared_ptr<Deck> deck;
    Player player;
    QPushButton hitButton;
    QPushButton standButton;
public:
    explicit GameWindow(QWidget *parent = nullptr);
    void Draw();
public slots:
    void onHitButtonClicked();
protected:
    void paintEvent(QPaintEvent *e) override;

};

#endif // GAMEWINDOW_H
