#include <QApplication>
#include "menu.h"
#include "gamewindow.h"

Menu::Menu(int width, int height, QWidget *parent):
    QWidget(parent), backgroundLabel{this}, ng_button{"New game", this},
    continue_button{"Continue", this}, exit_button{"Exit", this}
{
    resize(width,height);
    QPixmap backgroundImage("../BlackJack/images/background.jpg");
    backgroundLabel.resize(width,height);
    backgroundLabel.setPixmap(backgroundImage);
    layout.setAlignment(Qt::AlignCenter);
    layout.setSpacing(20);
    layout.addWidget(&ng_button);
    layout.addWidget(&continue_button);
    layout.addWidget(&exit_button);
    setLayout(&layout);

    connect(&ng_button,  &QPushButton::clicked, this, &Menu::onNewGameActionTriggered);
    connect(&continue_button,  &QPushButton::clicked, this, &Menu::onContinueActionTriggered);
    connect(&exit_button,  &QPushButton::clicked, this, &Menu::onExitActionTriggered);
}

void Menu::onNewGameActionTriggered()
{
    auto &gw_instance = GameWindow::getInstance();
    gw_instance.FullResetGame();
    hide();
    gw_instance.Init();
    gw_instance.show();
}

void Menu::onContinueActionTriggered()
{
    auto &gw_instance = GameWindow::getInstance();
    gw_instance.ResetCurrentGame();
    hide();
    gw_instance.show();
}

void Menu::onExitActionTriggered()
{
    QApplication::quit();
}
