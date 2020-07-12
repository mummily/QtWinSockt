#include "qtwinsocketclient.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QHostAddress>
#include "constdef.h"

QtWinSocketClient::QtWinSocketClient(QWidget *parent)
    : QMainWindow(parent)
{
    initUI();
}

QtWinSocketClient::~QtWinSocketClient()
{

}

/*****************************************************************************
* @brief   : ��ʼ��UI
* @author  : wb
* @date    : 2020/07/12
* @param:  : 
*****************************************************************************/
void QtWinSocketClient::initUI()
{
    QHostAddress addr = QHostAddress::LocalHost;

    QLabel *addrLabel = new QLabel("", this);
    addrLabel->setText("Server IP: " + addr.toString());
    speedLabel = new QLabel("", this);
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

/*****************************************************************************
* @brief   : ����
* @author  : wb
* @date    : 2020/07/12
* @param:  : 
*****************************************************************************/
void QtWinSocketClient::slotSend()
{
    sendBtn->setEnabled(false);

    QHostAddress addr = QHostAddress::LocalHost;
    mpTask = new TcpTask(addr.toString(), SOCKET_SEND_PORT);

    connect(mpTask,SIGNAL(speed(qreal)),this,SLOT(onSpeed(qreal)),Qt::QueuedConnection);
    mpTask->start();
}

/*****************************************************************************
* @brief   : �����ٶ�
* @author  : wb
* @date    : 2020/07/12
* @param:  : 
*****************************************************************************/
void QtWinSocketClient::onSpeed(qreal val)
{
    speedLabel->setText(tr("Speed: %1 M/s").arg(val));
}
