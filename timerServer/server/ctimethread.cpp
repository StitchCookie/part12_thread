#include "ctimethread.h"
#include <QDateTime>
#include <QDataStream>

CTimeThread::CTimeThread(qintptr socketDescriptor,QObject *parent)
    :QThread(parent),m_sockerIntptr(socketDescriptor)
{}

void CTimeThread::run()
{
    QTcpSocket tcpSocket;
    if(!tcpSocket.setSocketDescriptor(m_sockerIntptr))
    {
        emit error(tcpSocket.error());
            return;
    }
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    uint time = QDateTime::currentDateTime().toSecsSinceEpoch();
    out<<time;
    tcpSocket.write(block);  // 将获取的当前时间传回客户端
    tcpSocket.disconnectFromHost(); // 断开连接
    tcpSocket.waitForDisconnected(); // 等待返回
}
