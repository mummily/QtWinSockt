#include "tcpclient.h"

TcpClient::TcpClient(QObject *parent)
    : QObject(parent), m_dataSock(INVALID_SOCKET)
{
    int iResult;
    WSADATA wsaData;
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0)
    {
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

    m_dataSock = INVALID_SOCKET;
    m_dataSock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if (m_dataSock == INVALID_SOCKET)
    {
        printf("socket function failed with error = %d\n", WSAGetLastError() );

        return false;
    }

    if(::connect( m_dataSock, (SOCKADDR*) &clientService, sizeof(clientService)) == SOCKET_ERROR)
    {
        printf( "Failed to connect.\n" );
        WSACleanup();

        return false;
    }

    return true;
}

bool TcpClient::setSendBufferSize(int len)
{
    if (m_dataSock == INVALID_SOCKET)
        return false;

    int iResult = ::setsockopt(m_dataSock, SOL_SOCKET, SO_SNDBUF, (char*)&len, sizeof(int));
    if (iResult == SOCKET_ERROR)
    {
        printf("set SO_SNDBUF failed: %d\n", WSAGetLastError());
        return false;
    }

    return true;
}

bool TcpClient::setRecvBufferSize(int len)
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

int TcpClient::recvData(char* buf,int len)
{
    if (m_dataSock == INVALID_SOCKET)
        return SOCKET_ERROR;

    return recv(m_dataSock, buf, len, 0);
}

int TcpClient::sendData(char* buf,int len)
{
    if (m_dataSock == INVALID_SOCKET)
        return SOCKET_ERROR;

    return send(m_dataSock, buf, len, 0);
}

void TcpClient::close()
{
    if (m_dataSock == INVALID_SOCKET)
    {
        closesocket(m_dataSock);
        m_dataSock = INVALID_SOCKET;
    }
}