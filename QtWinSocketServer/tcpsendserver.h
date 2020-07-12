/*!
*@file      tcpsendserver.h
*@author    wb
*@date      2020/07/12
*@remarks   ·¢ËÍ·þÎñ
*@version 1.0
*/

#ifndef TCPSENDSERVER_H
#define TCPSENDSERVER_H

#include <QThread>

class TcpSendServer : public QThread
{
    Q_OBJECT
public:
    explicit TcpSendServer(quint16 port,QObject *parent = nullptr);
    void terminate();
private:
    virtual void run();
signals:
public slots:

private:
    quint16 m_nPort;
    bool    m_bQuit;
    char    m_buff[1024];
};

#endif // TCPSENDSERVER_H
