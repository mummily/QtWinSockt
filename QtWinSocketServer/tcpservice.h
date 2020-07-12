/*!
*@file      tcpservice.h
*@author    wb
*@date      2020/07/12
*@remarks   ¼àÌý·þÎñ
*@version 1.0
*/
#ifndef TCPSERVICE_H
#define TCPSERVICE_H

#include <QObject>
#include <winsock2.h>
#include <ws2tcpip.h>

class TcpService : public QObject
{
    Q_OBJECT

public:
    explicit TcpService(QObject *parent = 0);
    virtual ~TcpService();
    bool listen(unsigned short port);
    bool setSendBufferSize(int len);
    bool setRecvBufferSize(int len);
    int recvData(char* buf,int len);
    int sendData(char* buf,int len);
    void close();
private:
    SOCKET m_listenSock;
    SOCKET m_dataSock;
};

#endif // TCPSERVICE_H
