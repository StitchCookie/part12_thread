#include <QApplication>
#include "ctimerclient.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CTimerClient client;

    client.show();
    return a.exec();
}
