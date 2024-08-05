#ifndef CTIMETHREAD_H
#define CTIMETHREAD_H

#include <QThread>
#include <QTcpSocket>

class CTimeThread : public QThread
{
    Q_OBJECT
public:
    explicit CTimeThread(int socketDescriptor,QObject *parent = nullptr);
protected:
    void run() override;

signals:
    void error(QTcpSocket::SocketError errStr);

private:
    int m_sockerIntptr;
};

#endif // CTIMETHREAD_H
