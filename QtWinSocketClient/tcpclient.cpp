#include "tcpclient.h"


TcpClient::TcpClient(QObject *parent)
    : QObject(parent), mDataSock(INVALID_SOCKET)
{
    int iResult;
    WSADATA wsaData;
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return ;
    }
}

TcpClient::~TcpClient()
{
    close();
    WSACleanup();
}

bool TcpClient::connectToHost(const char* addr,unsigned short port)
{
    struct sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr(addr);
    clientService.sin_port = htons(port);

    mDataSock = INVALID_SOCKET;
    mDataSock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if (mDataSock == INVALID_SOCKET)
    {
        printf("socket function failed with error = %d\n", WSAGetLastError() );

        return false;
    }
    if(::connect( mDataSock, (SOCKADDR*) &clientService, sizeof(clientService)) == SOCKET_ERROR) {
        printf( "Failed to connect.\n" );
        WSACleanup();
        return false;
    }
    return true;

}

bool TcpClient::setSendBufferSize(int len)
{
    if (mDataSock == INVALID_SOCKET)return false;

    int iResult = ::setsockopt(mDataSock, SOL_SOCKET, SO_SNDBUF, (char*)&len, sizeof(int));
    if (iResult == SOCKET_ERROR) {
        printf("set SO_SNDBUF failed: %d\n", WSAGetLastError());
        return false;
    }
    return true;
}

bool TcpClient::setRecvBufferSize(int len)
{
    if (mDataSock == INVALID_SOCKET)return false;

    int iResult = ::setsockopt(mDataSock, SOL_SOCKET, SO_RCVBUF, (char*)&len, sizeof(int));
    if (iResult == SOCKET_ERROR) {
        printf("set SO_RCVBUF failed: %d\n", WSAGetLastError());
        return false;
    }
    return true;
}

int TcpClient::recvData(char* buf,int len)
{
    if (mDataSock == INVALID_SOCKET)return SOCKET_ERROR;

    return recv(mDataSock, buf, len, 0);
}

int TcpClient::sendData(char* buf,int len)
{
    if (mDataSock == INVALID_SOCKET)return SOCKET_ERROR;

    return send(mDataSock, buf, len, 0);
}

void TcpClient::close()
{
    if (mDataSock == INVALID_SOCKET)
    {
        closesocket(mDataSock);
        mDataSock = INVALID_SOCKET;
    }
}