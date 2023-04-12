#include <QApplication>
#include "gamewindow.h"



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    auto& gw_instance = GameWindow::getInstance();
    //Menu menu{gw_instance.getWidth(),gw_instance.getHeight(),&gw_instance};
    //gw_instance.setMenu(menu);
    gw_instance.show();
    //menu.show();
    return app.exec();
}
