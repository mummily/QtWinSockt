#include "qtwinsocketserver.h"
#include "..\include\constdef.h"

QtWinSocketServer::QtWinSocketServer(QWidget *parent)
    : QMainWindow(parent)
{
    m_pRecvServer = new TcpRecvServer((quint16)SERVER_SOCKET_RECV_PORT);
    m_pSendServer = new TcpSendServer((quint16)SERVER_SOCKET_SEND_PORT);
    m_pRecvServer->start();
    m_pSendServer->start();
}

QtWinSocketServer::~QtWinSocketServer()
{
    m_pRecvServer->terminate();
    m_pSendServer->terminate();
    m_pRecvServer->deleteLater();
    m_pSendServer->deleteLater();
}
