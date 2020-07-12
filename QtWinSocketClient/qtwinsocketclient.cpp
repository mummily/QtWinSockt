#include "qtwinsocketclient.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

QtWinSocketClient::QtWinSocketClient(QWidget *parent)
    : QMainWindow(parent)
{
    initUI();
}

QtWinSocketClient::~QtWinSocketClient()
{

}

void QtWinSocketClient::initUI()
{
    QLabel *addrLabel = new QLabel("Addr", this);
    speedLabel = new QLabel("Speed", this);
    sendBtn = new QPushButton("Send", this);

    QVBoxLayout *vBoxLayout = new QVBoxLayout();
    vBoxLayout->addWidget(addrLabel);
    vBoxLayout->addWidget(speedLabel);
    vBoxLayout->addWidget(sendBtn);

    QWidget* pCenterWidget = new QWidget();
    setCentralWidget(pCenterWidget);
    pCenterWidget->setLayout(vBoxLayout);

    connect(sendBtn, SIGNAL(clicked()), this, SLOT(slotSend()));
}

void QtWinSocketClient::slotSend()
{
    QString sAddr = "192.168.0.107";
    mpTask = new TcpTask(sAddr, 9007);
    connect(mpTask,SIGNAL(speed(qreal)),this,SLOT(onSpeed(qreal)),Qt::QueuedConnection);
    mpTask->start();

    sendBtn->setEnabled(false);
}

void QtWinSocketClient::onSpeed(qreal val)
{
    speedLabel->setText(tr("%1").arg(val));
}
