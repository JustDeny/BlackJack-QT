#include "gamewindow.h"
#include <QPainter>

void GameWindow::loadImages()
{
    m_backgroundImage.load("../BlackJack/images/background.jpg");

}

GameWindow::GameWindow(QWidget *parent)
    : QWidget{parent}, deck{std::make_shared<Deck>(this)}, player{this,deck},
      dealer{this,deck}, hitButton{"Hit",this}, standButton{"Stand", this}
{
    resize(W_WIDTH,W_HEIGHT);
    loadImages();
    hitButton.setFixedSize(70,30);
    hitButton.move(520,250);
    standButton.setFixedSize(70,30);
    standButton.move(610,250);
    timer.setInterval(500);
    connect(&hitButton, &QPushButton::clicked, this, &GameWindow::onHitButtonClicked);
    connect(&timer, &QTimer::timeout, this, &GameWindow::timerTimeout);
}

void GameWindow::Init()
{
    player.Init();
    dealer.Init();
}

void GameWindow::Draw()
{
    QPainter qp(this);          // I'd like to make it as shared_ptr but it must be created only in this event func
    qp.drawImage(0,0,m_backgroundImage);
    //deck->Draw(qp);

}

void GameWindow::onHitButtonClicked()
{
    timer.start();
}

void GameWindow::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

     Draw();
}

void  GameWindow::timerTimeout()
{
   player.hit();
   timer.stop();
}
