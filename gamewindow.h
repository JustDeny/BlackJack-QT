#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>

class GameWindow : public QWidget
{
    Q_OBJECT
private:
    const int W_WIDTH = 1200;
    const int W_HEIGHT = 600;
public:
    explicit GameWindow(QWidget *parent = nullptr);

};

#endif // GAMEWINDOW_H
