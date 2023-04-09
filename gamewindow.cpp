#include "gamewindow.h"
#include <QPainter>

void GameWindow::loadImages()
{
    m_backgroundImage.load("../BlackJack/images/background.jpg");

}

GameWindow::GameWindow(QWidget *parent)
    : QWidget{parent}, deck{std::make_shared<Deck>(this)}, player{this,deck}
{
    resize(W_WIDTH,W_HEIGHT);
    loadImages();

}

void GameWindow::Draw()
{
    QPainter qp(this);          // I'd like to make it as shared_ptr but it must be created only in this event func
    qp.drawImage(0,0,m_backgroundImage);
    //deck->Draw(qp);

}

void GameWindow::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

     Draw();
}
