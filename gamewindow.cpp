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

void GameWindow::setMenu(Menu &menu)
{
}

void GameWindow::loadImages()
{
    m_backgroundImage.load("../BlackJack/images/background.jpg");

}

GameWindow::GameWindow(QWidget *parent)
    : QWidget{parent}, deck{std::make_shared<Deck>(this)}, player{this,deck},
      dealer{this,deck}, hit_button{"Hit",this}, stand_button{"Stand", this}, player_score_label{this},
      dealer_score_label{this}, result_label{this}, menu{W_WIDTH,W_HEIGHT,this}
{
    resize(W_WIDTH,W_HEIGHT);
    loadImages();
    hit_button.setFixedSize(70,30);
    hit_button.move(520,250);
    stand_button.setFixedSize(70,30);
    stand_button.move(610,250);
    timer.setInterval(500);

    connect(&hit_button, &QPushButton::clicked, this, &GameWindow::onHitButtonClicked);
    connect(&stand_button, &QPushButton::clicked, this, &GameWindow::onStandButtonClicked);
    connect(&timer, &QTimer::timeout, this, &GameWindow::timerTimeout);
}

void GameWindow::waitUserClick()
{
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

void GameWindow::showMenu() {
    this->hide();
}
void GameWindow::hideMenu() {
    this->show();
}

void GameWindow::Init()
{
    player_score_label.move(170,270);
    dealer_score_label.move(900,270);
    player_score_label.setFixedSize(30,30);
    dealer_score_label.setFixedSize(30,30);
    InitUI();
    player.Init();
    dealer.Dealer::Init();
    player_score_label.setText(QString::number(player.getScore()));
    dealer_score_label.setText(QString::number(dealer.getScore()));
    if(player.getScore()>=21)
        DetermineWinner();
}

void GameWindow::Draw()
{
    QPainter qp(this);          // I'd like to make it as shared_ptr but it must be created only in this event func
    qp.drawImage(0,0,m_backgroundImage);
    //deck->Draw(qp);

}

void GameWindow::updateUI()
{
    player_score_label.setText(QString::number(player.getScore()));
    dealer_score_label.setText(QString::number(dealer.getScore()));
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
    stand_button.setStyleSheet("QPushButton {""background-color: transparent; border: 4px solid white; border-radius: 5px; \
    color: white;} QPushButton:hover { background-color: rgba(255, 255, 255, 0.2); }QPushButton:pressed {\
    background-color: rgba(255, 255, 255, 0.4);}");
    stand_button.setFont(font);
    result_label.setAlignment(Qt::AlignCenter);

    int labelX = (width() - 100) / 2;
    int labelY = (height()) / 2;
    result_label.setGeometry(labelX, labelY, 100, 50);
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
    if(player_score == dealer_score){
        result_label.setText("Draw");
    }
    else if(player_score == 21){
        result_label.setText("Win");
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
    }
    else if(player_score < 21 && dealer_score<21&& player_score < dealer_score )    //dealer closer to 21
    {
        result_label.setText("Loose");
    }
    else if (player_score < 21 && dealer_score<21&&player_score >dealer_score)      //player closer to 21
    {
        result_label.setText("Win");
    }
    waitUserClick();
    ResetCurrentGame();
    menu.show();
}

void GameWindow::ResetCurrentGame()
{
    player.Reset();
    dealer.Reset();
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
    timer.start();
}

void GameWindow::onStandButtonClicked()
{
    updateUI();
    DetermineWinner();
}

void GameWindow::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    Draw();
}

void GameWindow::timerTimeout()
{
   player.hit();
   timer.stop();
   updateUI();
   if(player.getScore() >= 21)
       DetermineWinner();
}
