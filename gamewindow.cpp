#include "gamewindow.h"
#include <QMouseEvent>
#include <QDebug>
#include <QPainter>
#include <qeventloop.h>

int GameWindow::getWidth() const
{
    return W_WIDTH;
}

int GameWindow::getHeight() const
{
    return W_HEIGHT;
}

Player &GameWindow::getPlayer()
{
    return player;
}

void GameWindow::setCurrentBet(int bet)
{
    current_bet = bet;
}

void GameWindow::loadResources()
{
    m_background_pixmap.load("../BlackJack/images/background.jpg");
    background_sound.setSource(QUrl::fromLocalFile("../BlackJack/sounds/background_sound.wav"));
    button_sound.setSource(QUrl::fromLocalFile("../BlackJack/sounds/button_sound.wav"));
}

QSoundEffect &GameWindow::getButtonSound()
{
    return button_sound;
}

GameWindow::GameWindow(QWidget *parent)
    : QWidget{parent}, m_background(this), deck{std::make_shared<Deck>(this)},
      hit_button{"Hit",this}, stand_button{"Stand", this}, player_score_label{this}, dealer_score_label{this},
      result_label{this}, player_balance{this}, player{this,deck}, dealer{this,deck},menu{W_WIDTH,W_HEIGHT,this}
{
    resize(W_WIDTH,W_HEIGHT);
    m_background.resize(W_WIDTH,W_HEIGHT);
    loadResources();
    m_background.setPixmap(m_background_pixmap);
    //m_background.show();
    hit_button.setFixedSize(BUTTON_WIDTH,BUTTON_HEIGHT);
    hit_button.move(HIT_BUTTON_POS);
    stand_button.setFixedSize(BUTTON_WIDTH,BUTTON_HEIGHT);
    stand_button.move(STAND_BUTTON_POS);

    timer.setInterval(500); //0.5sec delay for buttons

    background_sound.setLoopCount(QSoundEffect::Infinite);
    background_sound.setVolume(0.1f);
    background_sound.play();
    background_sound.setVolume(0.25f);


    connect(&hit_button, &QPushButton::clicked, this, &GameWindow::onHitButtonClicked);
    connect(&stand_button, &QPushButton::clicked, this, &GameWindow::onStandButtonClicked);
    connect(&timer, &QTimer::timeout, this, &GameWindow::timerTimeout);
}

void GameWindow::waitUserClick()
{
    QEventLoop m_eventLoop;
    connect(this, &GameWindow::mSignalTriggered, &m_eventLoop, &QEventLoop::quit);
    m_eventLoop.exec();
}

void GameWindow::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    emit mSignalTriggered();
}

GameWindow &GameWindow::getInstance()
{
    static GameWindow instance;
    return instance;
}

void GameWindow::Init()
{
    player_score_label.move(PLAYER_SCORE_LABEL_POS);
    dealer_score_label.move(DEALER_SCORE_LABEL_POS);
    player_balance.move(BALANCE_POS);
    player_score_label.setFixedSize(30,30);
    dealer_score_label.setFixedSize(30,30);
    player_balance.setFixedSize(200,50);

    InitUI();

    player.Init();
    dealer.Dealer::Init();
    updateUI();

    if(player.getScore()>=21)
        DetermineWinner();
}

void GameWindow::updateUI()
{
    player_score_label.setText(QString::number(player.getScore()));
    dealer_score_label.setText(QString::number(dealer.getScore()));
    player_balance.setText("Balance: "+QString::number(player.getBalance())+"$;\
 Current bet: "+QString::number(current_bet)+"$");
}

void GameWindow::InitUI()
{
    QFont font("Century Gothic",12);
    font.setBold(true);
    player_score_label.setFont(font);
    player_score_label.setStyleSheet("QLabel { color: white; }");
    dealer_score_label.setFont(font);
    dealer_score_label.setStyleSheet("QLabel { color: white; }");

    hit_button.setStyleSheet("QPushButton {""background-color: transparent; border: 4px solid white; border-radius: 5px; \
    color: white;} QPushButton:hover { background-color: rgba(255, 255, 255, 0.2); }QPushButton:pressed {\
    background-color: rgba(255, 255, 255, 0.4);}");
    hit_button.setFont(font);

    stand_button.setStyleSheet(hit_button.styleSheet());
    stand_button.setFont(font);

    result_label.setAlignment(Qt::AlignCenter);

    int labelX = (width() - 300) / 2;
    int labelY = (height()) / 2;
    result_label.setGeometry(labelX, labelY, 300, 50);
    font.setPixelSize(25);
    result_label.setFont(font);
    result_label.setStyleSheet("QLabel { color: white; }");
}

void GameWindow::DetermineWinner()
{
    dealer.RevealCard();
    dealer.getAdditionalCards();
    updateUI();
    int player_score = player.getScore();
    int dealer_score = dealer.getScore();
    bool isPlayerWon = false;
    if(player_score == dealer_score){
        result_label.setText("Draw");
        player.setBalance(player.getBalance()+current_bet);
    }
    else if(player_score == 21){
        result_label.setText("Win");
        isPlayerWon = true;
    }
    else if (dealer_score == 21){
        result_label.setText("Loose");
    }
    else if(player_score > 21)
    {
        result_label.setText("Loose");
    }
    else if (dealer_score > 21) {
        result_label.setText("Win");
        isPlayerWon = true;
    }
    else if(player_score < 21 && dealer_score<21&& player_score < dealer_score )    //dealer closer to 21
    {
        result_label.setText("Loose");
    }
    else if (player_score < 21 && dealer_score<21&&player_score >dealer_score)      //player closer to 21
    {
        result_label.setText("Win");
        isPlayerWon = true;
    }
    if(isPlayerWon)
        player.setBalance(player.getBalance()+current_bet*2);
    waitUserClick();
    ResetCurrentGame();
    menu.show();
}

void GameWindow::ResetCurrentGame()
{
    player.Reset();
    dealer.Reset();
    current_bet = 0;
    result_label.clear();
    updateUI();
    deck->Shuffle();
}

void GameWindow::FullResetGame()
{
    ResetCurrentGame();
    player.setBalance(DEFAULT_BALANCE);

}

void GameWindow::onHitButtonClicked()
{
    button_sound.play();
    timer.start();
}

void GameWindow::onStandButtonClicked()
{
    button_sound.play();
    updateUI();
    DetermineWinner();
}

void GameWindow::timerTimeout()
{
   player.hit();
   timer.stop();
   updateUI();
   if(player.getScore() >= 21)
       DetermineWinner();
}
