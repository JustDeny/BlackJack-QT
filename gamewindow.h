#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QGraphicsOpacityEffect>
#include <QMainWindow>
#include <QPalette>
#include <QPushButton>
#include <QApplication>
#include <QMediaPlayer>
#include <QSoundEffect>
#include "dealer.h"
#include "deck.h"
#include "menu.h"
#include "player.h"



class GameWindow : public QWidget
{
    Q_OBJECT
private:

    const int W_WIDTH = 1200;
    const int W_HEIGHT = 600;
    const int DEFAULT_BALANCE = 1500;
    const int BUTTON_WIDTH = 70;
    const int BUTTON_HEIGHT = 30;

    const QPoint HIT_BUTTON_POS={520,250};
    const QPoint STAND_BUTTON_POS={610,250};
    const QPoint PLAYER_SCORE_LABEL_POS={170,270};
    const QPoint DEALER_SCORE_LABEL_POS={900,270};
    const QPoint BALANCE_POS={170,400};
    QLabel m_background;
    int current_bet =0;
    std::shared_ptr<Deck> deck;
    QPushButton hit_button;
    QPushButton stand_button;
    QTimer timer;

    QLabel player_score_label;
    QLabel dealer_score_label;
    QLabel result_label;
    QLabel player_balance;

    QPixmap m_background_pixmap;
    QSoundEffect background_sound;
    QSoundEffect button_sound;

    Player player;
    Dealer dealer;
    Menu menu;

    GameWindow(QWidget *parent = nullptr);
    void waitUserClick();
    void loadResources();
    bool initGame();
public:
    static GameWindow& getInstance();
    void Init();
    //void Draw();
    void updateUI();
    void InitUI();
    void DetermineWinner();
    void ResetCurrentGame();
    void FullResetGame();
    int getWidth() const;
    int getHeight() const;
    Player& getPlayer();
    void setCurrentBet(int bet);
    QSoundEffect &getButtonSound();
public slots:
    void onHitButtonClicked();
    void onStandButtonClicked();
    void timerTimeout();
signals:
    void mSignalTriggered();
protected:
    //void paintEvent(QPaintEvent *e) override;
    void mousePressEvent(QMouseEvent *event) override;
};



#endif // GAMEWINDOW_H
