#ifndef QTWINSOCKETCLIENT_H
#define QTWINSOCKETCLIENT_H

#include <QtWidgets/QMainWindow>
#include "tcpsendclient.h"
#include "tcprecvclient.h"

class QLabel;
class QPushButton;
class QtWinSocketClient : public QMainWindow
{
    Q_OBJECT

public:
    QtWinSocketClient(QWidget *parent = 0);
    ~QtWinSocketClient();

private slots:
    void slotSend();
    void slotRecv();
    void slotSendSpeed(qreal val);
    void slotRecvSpeed(qreal val);

private:
    void initUI();

private:
    TcpSendClient *m_pSendTask;
    TcpRecvClient *m_pRecvTask;
    QLabel      *m_pSendSpeedLabel,*m_pRecvSpeedLabel;
    QPushButton *m_pSendBtn,*m_pRecvBtn;
};

#endif // QTWINSOCKETCLIENT_H
