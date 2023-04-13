#include "betdialog.h"

BetDialog::BetDialog(QWidget *parent)
    : QDialog(parent),m_label("Input bet:"), m_okButton("Ok")
{
    m_layout.addWidget(&m_label);
    m_layout.addWidget(&m_lineEdit);
    m_layout.addWidget(&m_okButton);

    setLayout(&m_layout);

    connect(&m_okButton, &QPushButton::clicked, this, &BetDialog::onOkButtonClicked);
}

int BetDialog::getBetAmount()
{
    event_loop.exec();
    return m_betAmount;
}


void BetDialog::onOkButtonClicked()
{
    bool ok;
    int bet = m_lineEdit.text().toInt(&ok);

    if (ok && bet > 0) {
        m_betAmount = bet;
        accept();
        event_loop.quit();
    } else {
        QMessageBox::warning(this, "Error", "Input correct amount of money");
    }
}
