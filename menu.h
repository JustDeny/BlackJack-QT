#ifndef MENU_H
#define MENU_H

#include <QVBoxLayout>
#include <qlabel.h>
#include <qpushbutton.h>



class Menu : public QWidget {
    Q_OBJECT
private:
    QLabel backgroundLabel;
    QVBoxLayout layout;
    QPushButton ng_button;
    QPushButton continue_button;
    QPushButton exit_button;
    QPixmap backgroundPixmap;
    void loadTextures();
public:
    explicit Menu(int width, int height, QWidget *parent = nullptr);
public slots:
    void onNewGameActionTriggered();
    void onContinueActionTriggered();
    void onExitActionTriggered();
};

#endif // MENU_H
