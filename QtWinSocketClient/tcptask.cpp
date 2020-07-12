#include "tcptask.h"
#include <QDateTime>
#include "tcpclient.h"
#include "..\include\constdef.h"

TcpTask::TcpTask(QString addr,quint16 port,QObject *parent)
    : QThread(parent), m_nPort(port), m_sAddr(addr), m_bQuit(false)
{
}

/*****************************************************************************
* @brief   : 发送|接收任务中断
* @author  : wb
* @date    : 2020/07/12
* @param:  : 
*****************************************************************************/
void TcpTask::terminate()
{
    m_bQuit = true;
    if(this->isRunning())
        wait(3000);

    QThread::terminate();
}

/*****************************************************************************
* @brief   : 任务执行
* @author  : wb
* @date    : 2020/07/12
* @param:  : 
*****************************************************************************/
void TcpTask::run()
{
    TcpClient client;
    if(!client.connectToHost(m_sAddr.toStdString().c_str(),m_nPort))
        return;

    QDateTime dtLast = QDateTime::currentDateTime();
    QDateTime dtCurrent = dtLast;

    quint64 sumsize = 0;
    if (CLIENT_SOCKET_SEND_PORT == m_nPort) // 发送
    {
        client.setSendBufferSize(SOCKET_SEND_BUFF);
        memset(m_buff,0xAA,sizeof(m_buff));
        while (!m_bQuit)
        {
            int ret = client.sendData(m_buff,sizeof(m_buff));
            if(ret <= 0 )
                break;

            sumsize += ret;
            dtCurrent = QDateTime::currentDateTime();
            qint32 secs = dtLast.secsTo(dtCurrent);
            if(secs >= 5) //每5s算下平均速度
            {
                emit speed(sumsize /(secs*1024*1024));
                dtLast = dtCurrent;
                sumsize = 0;
            }
        }
    }
    else if (CLIENT_SOCKET_RECV_PORT == m_nPort) // 接收
    {
        client.setRecvBufferSize(SOCKET_RECV_BUFF);
        while (!m_bQuit)
        {
            int ret = client.recvData(m_buff,sizeof(m_buff));
            if(ret <= 0 )
                break;

            sumsize += ret;
            dtCurrent = QDateTime::currentDateTime();
            qint32 secs = dtLast.secsTo(dtCurrent);
            if(secs >= 5)
            {
                emit speed(sumsize /(secs*1024*1024));
                dtLast = dtCurrent;
                sumsize = 0;
            }
        }
    }

    client.close();
}