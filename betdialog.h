#ifndef BETDIALOG_H
#define BETDIALOG_H


#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include<QMessageBox>
#include <qeventloop.h>

class BetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BetDialog(QWidget *parent = nullptr);
    int getBetAmount();
    void changeLayout();
private slots:
    void onOkButtonClicked();

private:
    QLabel m_label;
    QLineEdit m_lineEdit;
    QPushButton m_okButton;
    QVBoxLayout m_layout;
    QEventLoop event_loop;
    int m_betAmount;
};



#endif // BETDIALOG_H
