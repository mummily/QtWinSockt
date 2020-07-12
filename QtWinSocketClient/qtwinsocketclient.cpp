#include "qtwinsocketclient.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include ".\..\include\constdef.h"

QtWinSocketClient::QtWinSocketClient(QWidget *parent)
    : QMainWindow(parent)
{
    initUI();
}

QtWinSocketClient::~QtWinSocketClient()
{

}

/*****************************************************************************
* @brief   : 初始化UI
* @author  : wb
* @date    : 2020/07/12
* @param:  : 
*****************************************************************************/
void QtWinSocketClient::initUI()
{
    QLabel *addrLabel = new QLabel("", this);
    addrLabel->setText("Server IP: 127.0.0.1");
    m_pSendSpeedLabel = new QLabel("", this);
    m_pRecvSpeedLabel = new QLabel("", this);
    m_pSendBtn = new QPushButton("Send", this);
    m_pRecvBtn = new QPushButton("Recv", this);

    QVBoxLayout *vBoxLayout = new QVBoxLayout();
    vBoxLayout->addWidget(addrLabel);
    vBoxLayout->addWidget(m_pSendSpeedLabel);
    vBoxLayout->addWidget(m_pRecvSpeedLabel);
    vBoxLayout->addWidget(m_pSendBtn);
    vBoxLayout->addWidget(m_pRecvBtn);

    QWidget* pCenterWidget = new QWidget();
    setCentralWidget(pCenterWidget);
    pCenterWidget->setLayout(vBoxLayout);

    connect(m_pSendBtn, SIGNAL(clicked()), this, SLOT(slotSend()));
    connect(m_pRecvBtn, SIGNAL(clicked()), this, SLOT(slotRecv()));
}

/*****************************************************************************
* @brief   : 发送
* @author  : wb
* @date    : 2020/07/12
* @param:  : 
*****************************************************************************/
void QtWinSocketClient::slotSend()
{
    m_pSendBtn->setEnabled(false);

    QString addr = "127.0.0.1";
    m_pSendTask = new TcpSendClient(addr, CLIENT_SOCKET_SEND_PORT);

    connect(m_pSendTask,SIGNAL(speed(qreal)),this,SLOT(slotSendSpeed(qreal)),Qt::QueuedConnection);
    m_pSendTask->start();
}

/*****************************************************************************
* @brief   : 接收
* @author  : wb
* @date    : 2020/07/12
* @param:  : 
*****************************************************************************/
void QtWinSocketClient::slotRecv()
{
    m_pRecvBtn->setEnabled(false);

    QString addr = "127.0.0.1";
    m_pRecvTask = new TcpRecvClient(addr, CLIENT_SOCKET_RECV_PORT);

    connect(m_pRecvTask,SIGNAL(speed(qreal)),this,SLOT(slotRecvSpeed(qreal)),Qt::QueuedConnection);
    m_pRecvTask->start();
}

/*****************************************************************************
* @brief   : 发送速度
* @author  : wb
* @date    : 2020/07/12
* @param:  : 
*****************************************************************************/
void QtWinSocketClient::slotSendSpeed(qreal val)
{
    m_pSendSpeedLabel->setText(tr("Send Speed: %1 M/s").arg(val));
}

/*****************************************************************************
* @brief   : 接收速度
* @author  : wb
* @date    : 2020/07/12
* @param:  : 
*****************************************************************************/
void QtWinSocketClient::slotRecvSpeed(qreal val)
{
    m_pRecvSpeedLabel->setText(tr("Recv Speed: %1 M/s").arg(val));
}
