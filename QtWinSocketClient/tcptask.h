#ifndef TCPTASK_H
#define TCPTASK_H

#include <QThread>

class TcpTask : public QThread
{
    Q_OBJECT
public:
    explicit TcpTask(QString addr,quint16 port,QObject *parent = nullptr);
    void terminate();

private:
    virtual void run();

signals:
    void speed(qreal);

public slots:

private:
    quint16 mPort;
    QString mAddr;
    bool mQuit;
    char buff[1048576];
};

#endif // TCPTASK_H
