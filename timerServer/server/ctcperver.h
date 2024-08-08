#ifndef CTCPERVER_H
#define CTCPERVER_H

#include <QTcpServer>

class MainWindow;
class CTcperver : public QTcpServer
{
    Q_OBJECT
public:
    explicit CTcperver(QObject *parent = nullptr);
protected:
    void incomingConnection(qintptr handle);
private:
    MainWindow *dlg;

signals:
};

#endif // CTCPERVER_H
