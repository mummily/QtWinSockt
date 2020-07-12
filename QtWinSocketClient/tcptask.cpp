#include "tcptask.h"
#include <QDateTime>
#include "tcpclient.h"

#define MAX_BUFF_SIZE (1024*1024*4); // 4M

TcpTask::TcpTask(QString addr,quint16 port,QObject *parent):QThread(parent)
    ,mPort(port)
    ,mAddr(addr)
    ,mQuit(false)
{

}
void TcpTask::terminate()
{
    mQuit = true;
    if(this->isRunning())
        wait(3000);

    QThread::terminate();
}
void TcpTask::run()
{
    int len = MAX_BUFF_SIZE;
    TcpClient client;
    QDateTime last_tm = QDateTime::currentDateTime();
    QDateTime curr_tm = last_tm;
    quint64 sum_size = 0;
    qint32 secs = 1;
    if(client.connectToHost(mAddr.toStdString().c_str(),mPort))
    {
        switch(mPort)
        {
        case 9007:
            {
                client.setSendBufferSize(len);
                memset(buff,0xAA,sizeof(buff));
                while (!mQuit)
                {
                    int ret = client.sendData(buff,sizeof(buff));

                    if(ret <= 0 )break;

                    sum_size += ret;
                    curr_tm = QDateTime::currentDateTime();
                    secs = last_tm.secsTo(curr_tm);
                    if(secs >= 5)
                    {
                        emit speed(sum_size /(secs*1024*1024));
                        last_tm = curr_tm;
                        sum_size = 0;
                    }

                }
                break;
            }
        case 9008:
            {
                client.setRecvBufferSize(len);
                while (!mQuit)
                {
                    int ret = client.recvData(buff,sizeof(buff));

                    if(ret <= 0 )break;
                    sum_size += ret;
                    curr_tm = QDateTime::currentDateTime();
                    secs = last_tm.secsTo(curr_tm);
                    if(secs >= 5)
                    {
                        emit speed(sum_size /(secs*1000*1000.0));
                        last_tm = curr_tm;
                        sum_size = 0;
                    }
                }
                break;
            }
        }

        client.close();
    }
}