#include "tcpsendserver.h"
#include "..\include\constdef.h"
#include "tcpservice.h"

TcpSendServer::TcpSendServer(quint16 port,QObject *parent)
    :QThread(parent),m_nPort(port),m_bQuit(false)
{
}

void TcpSendServer::terminate()
{
    m_bQuit = true;
    if(this->isRunning())
        wait(3000);
    
    QThread::terminate();
}

void TcpSendServer::run()
{
#if 0//linux
    QTcpServer mTcpServer;
    mTcpServer.listen(QHostAddress::Any,m_nPort);

    do{
        if(mTcpServer.waitForNewConnection(20000))
        {
            //FILE *fp = fopen("data.dat","wb");

            mStream.flushInput();

            qint64 bufsize = 0;
            int  nRcvBuf = 1024*1024*16;
            QTcpSocket *socket = mTcpServer.nextPendingConnection();
            //½ÓÊÕ»º´æÇø
            socket->setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption,nRcvBuf);

            do{
                if(m_bQuit)
                {
                    mTcpServer.close();
                    socket->close();
                    m_bQuit = false;
                    return ;
                }

                unsigned size = mStream.freeSpase();
                if(size < FRAME_SIZE)
                {
                    mStream.compactParseBuffer();
                    if(size == mStream.freeSpase())
                        mStream.flushInput();
                    continue;
                }

                socket->waitForReadyRead(10);
                bufsize = socket->read((char*)&mStream.fBuffer[mStream.fDataEnd],size);
                if(bufsize > 0)
                {

                    mStream.pushPacket(&mStream.fBuffer[mStream.fDataEnd],bufsize);
                }

            }while(bufsize >= 0);

        }
    }while(!m_bQuit);

    mTcpServer.close();
#else
    TcpService sendService;
    do
    {
        memset(m_buff,0x55,sizeof(m_buff));
        if(sendService.listen(m_nPort))
        {
            sendService.setSendBufferSize(SOCKET_SEND_BUFF);

            while (!m_bQuit)
            {
                int ret = sendService.sendData(m_buff,sizeof(m_buff));
                //usleep(1);
                if(ret <= 0 )
                    break;
            }
            sendService.close();
        }
    }while (!m_bQuit);
#endif
}
