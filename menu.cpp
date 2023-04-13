#include <QApplication>
#include "menu.h"
#include "gamewindow.h"
#include "betdialog.h"

void Menu::loadTextures()
{
    backgroundPixmap.load("../BlackJack/images/background.jpg");

}

Menu::Menu(int width, int height, QWidget *parent):
    QWidget(parent), backgroundLabel{this}, ng_button{"New game", this},
    continue_button{"Continue", this}, exit_button{"Exit", this}
{
    resize(width,height);
    backgroundLabel.resize(width,height);
    loadTextures();
    backgroundLabel.setPixmap(backgroundPixmap);

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
    gw_instance.getButtonSound().play();
    gw_instance.FullResetGame();
    hide();
    BetDialog bet_dialog{&gw_instance};
    bet_dialog.show();
    int money_to_bet = bet_dialog.getBetAmount();
    auto &player = gw_instance.getPlayer();
    if(player.getBalance() >= money_to_bet){
        player.setBalance(player.getBalance()-money_to_bet);
        gw_instance.setCurrentBet(money_to_bet);
        gw_instance.Init();
        gw_instance.show();
    }
    else{
        //again show menu
        show();
    }
}

void Menu::onContinueActionTriggered()
{
    auto &gw_instance = GameWindow::getInstance();
    gw_instance.getButtonSound().play();
    gw_instance.ResetCurrentGame();
    hide();
    BetDialog bet_dialog{&gw_instance};
    bet_dialog.show();
    int money_to_bet = bet_dialog.getBetAmount();
    auto &player = gw_instance.getPlayer();
    if(player.getBalance() >= money_to_bet){
        player.setBalance(player.getBalance()-money_to_bet);
        gw_instance.setCurrentBet(money_to_bet);
        gw_instance.Init();
        gw_instance.show();
    }
    else{
        show();
    }

}

void Menu::onExitActionTriggered()
{
    GameWindow::getInstance().getButtonSound().play();
    QApplication::quit();
}
