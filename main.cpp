#include <QApplication>
#include "gamewindow.h"



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    auto& gw_instance = GameWindow::getInstance();
    gw_instance.show();
    return app.exec();
}
