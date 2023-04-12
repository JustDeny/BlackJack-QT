#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QGraphicsOpacityEffect>
#include <QMainWindow>
#include <QPalette>
#include <QPushButton>
#include <QApplication>
#include "dealer.h"
#include "deck.h"
#include "menu.h"
#include "player.h"



class GameWindow : public QWidget
{
    Q_OBJECT
private:
    QEventLoop m_eventLoop;
    const int W_WIDTH = 1200;
    const int W_HEIGHT = 600;
    const int DEFAULT_BALANCE = 1500;
    QImage m_backgroundImage;
    void loadImages();
    bool initGame();
    std::shared_ptr<Deck> deck;
    Player player;
    Dealer dealer;
    QPushButton hit_button;
    QPushButton stand_button;
    QLabel player_score_label;
    QLabel dealer_score_label;
    QLabel result_label;
    QTimer timer;
    Menu menu;
    GameWindow(QWidget *parent = nullptr);
    void waitUserClick();
public:
    static GameWindow& getInstance();
    void Init();
    void Draw();
    void updateUI();
    void InitUI();
    void DetermineWinner();
    void ResetCurrentGame();
    void FullResetGame();
    void showMenu();
    void hideMenu();
    int getWidth() const;
    int getHeight() const;
    void setMenu(Menu& menu);
public slots:
    void onHitButtonClicked();
    void onStandButtonClicked();
    void timerTimeout();
signals:
    void mSignalTriggered();
protected:
    void paintEvent(QPaintEvent *e) override;
    void mousePressEvent(QMouseEvent *event) override;
};



#endif // GAMEWINDOW_H
