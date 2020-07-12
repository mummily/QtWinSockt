/*!
*@file      tcprecvserver.h
*@author    wb
*@date      2020/07/12
*@remarks   接收服务
*@version 1.0
*/

#ifndef TCPRECVSERVER_H
#define TCPRECVSERVER_H

#include <QThread>

class TcpRecvServer : public QThread
{
    Q_OBJECT
public:
    explicit TcpRecvServer(quint16 port,QObject *parent = nullptr);
    void terminate();

private:
    virtual void run();

signals:

public slots:

private:
    quint16 m_nPort;
    bool    m_bQuit;
    char    m_buff[8192]; // 8K
};

#endif // TCPRECVSERVER_H
