#ifndef QTWINSOCKETSERVER_H
#define QTWINSOCKETSERVER_H

#include <QtWidgets/QMainWindow>
#include "tcprecvserver.h"
#include "tcpsendserver.h"

class QtWinSocketServer : public QMainWindow
{
    Q_OBJECT

public:
    QtWinSocketServer(QWidget *parent = 0);
    ~QtWinSocketServer();

private:
    TcpRecvServer *m_pRecvServer;
    TcpSendServer *m_pSendServer;
};

#endif // QTWINSOCKETSERVER_H
