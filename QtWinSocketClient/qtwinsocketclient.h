#ifndef QTWINSOCKETCLIENT_H
#define QTWINSOCKETCLIENT_H

#include <QtWidgets/QMainWindow>
#include "tcptask.h"

class QLabel;
class QPushButton;
class QtWinSocketClient : public QMainWindow
{
    Q_OBJECT

public:
    QtWinSocketClient(QWidget *parent = 0);
    ~QtWinSocketClient();

private slots:
    void slotSend();
    void onSpeed(qreal val);

private:
    void initUI();

private:
    TcpTask *mpTask;
    QLabel *speedLabel;
    QPushButton *sendBtn;
};

#endif // QTWINSOCKETCLIENT_H
