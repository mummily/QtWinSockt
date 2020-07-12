#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <QObject>

class TcpClient : public QObject
{
    Q_OBJECT

public:
    explicit TcpClient(QObject *parent = 0);
    virtual ~TcpClient();

    bool connectToHost(const char* addr,unsigned short port);
    bool setSendBufferSize(int len);
    bool setRecvBufferSize(int len);
    int recvData(char* buf,int len);
    int sendData(char* buf,int len);
    void close();

private:
    SOCKET mDataSock;
};

#endif // TCPCLIENT_H
