#include "ctcperver.h"
#include "ctimethread.h"
#include "mainwindow.h"

CTcperver::CTcperver(QObject *parent)
    : QTcpServer(parent)
{
    dlg = (MainWindow *)parent;
}

void CTcperver::incomingConnection(qintptr handle)
{
    CTimeThread *thread = new CTimeThread(handle);
    connect(thread,&CTimeThread::finished,dlg,&MainWindow::slotShow);
    connect(thread,&CTimeThread::finished,thread,&CTimeThread::deleteLater,Qt::DirectConnection);
    thread->start();
}

