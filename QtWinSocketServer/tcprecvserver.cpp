#include "tcprecvserver.h"
#include "tcpservice.h"
#include "..\include\constdef.h"

TcpRecvServer::TcpRecvServer(quint16 port,QObject *parent)
    : QThread(parent),m_nPort(port),m_bQuit(false)
{
}

void TcpRecvServer::terminate()
{
    m_bQuit = true;
    if(this->isRunning())
        wait(3000);

    QThread::terminate();
}

void TcpRecvServer::run()
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
    TcpService recvService;
    do
    {
        if(recvService.listen(m_nPort))
        {
            recvService.setRecvBufferSize(SOCKET_RECV_BUFF);

            while (!m_bQuit)
            {
                int ret = recvService.recvData(m_buff,sizeof(m_buff));
                if(ret <= 0)
                    break;
            }
            recvService.close();
        }
    } while (!m_bQuit);
#endif
}