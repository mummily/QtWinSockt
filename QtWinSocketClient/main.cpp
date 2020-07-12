#include "qtwinsocketclient.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QtWinSocketClient w;
    w.show();

    return a.exec();
}
