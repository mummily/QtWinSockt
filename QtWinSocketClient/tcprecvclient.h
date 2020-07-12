#ifndef TCPRECVCLIENT_H
#define TCPRECVCLIENT_H

#include <QThread>

class TcpRecvClient : public QThread
{
    Q_OBJECT
public:
    explicit TcpRecvClient(QString addr,quint16 port,QObject *parent = nullptr);
    void terminate();

private:
    virtual void run();

signals:
    void speed(qreal);

public slots:

private:
    quint16 m_nPort;
    QString m_sAddr;
    bool    m_bQuit;
    char    m_buff[1048576]; // 1M
};

#endif // TCPRECVCLIENT_H
