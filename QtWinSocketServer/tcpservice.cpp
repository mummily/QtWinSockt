#include "tcpservice.h"

TcpService::TcpService(QObject *parent)
    :QObject(parent),m_listenSock(INVALID_SOCKET)
{
    int iResult;
    WSADATA wsaData;
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0)
    {
        printf("WSAStartup failed: %d\n", iResult);
        return;
    }
}

TcpService::~TcpService()
{
    close();
    WSACleanup();
}

bool TcpService::listen(unsigned short port)
{
    struct sockaddr_in saServer;

    m_dataSock = INVALID_SOCKET;
    m_listenSock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if (m_listenSock == INVALID_SOCKET)
    {
        printf("socket function failed with error = %d\n", WSAGetLastError());
        return false;
    }

    // Setup the TCP listening socket
    saServer.sin_family = AF_INET;
    saServer.sin_addr.s_addr = htonl(INADDR_ANY);
    saServer.sin_port = htons(port);
    int iResult = bind(m_listenSock, (SOCKADDR*)&saServer, sizeof(saServer));
    if (iResult == SOCKET_ERROR)
    {
        printf("bind failed: %d\n", WSAGetLastError());
        closesocket(m_listenSock);
        m_listenSock = INVALID_SOCKET;
        return false;
    }

    if (::listen( m_listenSock,SOMAXCONN ) == SOCKET_ERROR )
    {
        printf( "Error at bind(): %ld\n", WSAGetLastError() );
        closesocket(m_listenSock);
        m_listenSock = INVALID_SOCKET;
        return false;
    }

    // Accept a client socket
    m_dataSock = accept(m_listenSock, NULL, NULL);
    if (m_dataSock == INVALID_SOCKET)
    {
        printf("accept failed: %d\n", WSAGetLastError());
        closesocket(m_listenSock);
        m_listenSock = INVALID_SOCKET;
        return false;
    }
    closesocket(m_listenSock);
    m_listenSock = INVALID_SOCKET;
    return true;
}

bool TcpService::setSendBufferSize(int len)
{
    if (m_dataSock == INVALID_SOCKET)
        return false;

    int iResult = ::setsockopt(m_dataSock, SOL_SOCKET, SO_SNDBUF, (char*)&len, sizeof(int));
    if (iResult == SOCKET_ERROR)
    {
        printf("set SO_SNDBUF failed: %d\n", WSAGetLastError());
        return false;
    }

    // ::getsockopt(mDataSock,IPX_MAXSIZE, TCP_MAXSEG, (char*)&len, sizeof(int));
    return true;
}

bool TcpService::setRecvBufferSize(int len)
{
    if (m_dataSock == INVALID_SOCKET)
        return false;

    int iResult = ::setsockopt(m_dataSock, SOL_SOCKET, SO_RCVBUF, (char*)&len, sizeof(int));
    if (iResult == SOCKET_ERROR)
    {
        printf("set SO_RCVBUF failed: %d\n", WSAGetLastError());
        return false;
    }

    return true;
}

int TcpService::recvData(char* buf,int len)
{
    if (m_dataSock == INVALID_SOCKET)
        return SOCKET_ERROR;

    return recv(m_dataSock, buf, len, 0);
}

int TcpService::sendData(char* buf,int len)
{
    if (m_dataSock == INVALID_SOCKET)
        return SOCKET_ERROR;

    return send(m_dataSock, buf, len, 0);
}

void TcpService::close()
{
    if (m_listenSock == INVALID_SOCKET)
    {
        closesocket(m_listenSock);
        m_listenSock = INVALID_SOCKET;
    }

    if (m_dataSock == INVALID_SOCKET)
    {
        closesocket(m_dataSock);
        m_dataSock = INVALID_SOCKET;
    }
}