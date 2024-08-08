#ifndef CTIMERCLIENT_H
#define CTIMERCLIENT_H
#include <QDialog>
#include <QAbstractSocket>

class QLabel;
class QLineEdit;
class QDateTimeEdit;
class QPushButton;
class QTcpSocket;

class CTimerClient : public QDialog
{
    Q_OBJECT
public:
    CTimerClient(QWidget * parent = nullptr);
    ~CTimerClient();
public slots:
    void enableGetBtn();
    void getTime();
    void readTime();
    void slot_Error(QAbstractSocket::SocketError);


private:
    QLabel          *m_serverNameLabel;
    QLineEdit       *m_serverLineEdit;
    QLabel          *m_portLabel;
    QLineEdit       *m_portLineEdit;
    QDateTimeEdit   *m_dateTimeEdit;
    QLabel          *m_stateLabel;
    QPushButton     *m_getBtn;
    QPushButton     *m_quitBtn;
    uint             time2u;
    QTcpSocket      *m_tcpSocket;
};

#endif // CTIMERCLIENT_H
