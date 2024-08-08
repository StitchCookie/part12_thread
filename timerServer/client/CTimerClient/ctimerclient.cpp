#include "ctimerclient.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDateTime>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QDateTimeEdit>
#include <QTcpSocket>


CTimerClient::CTimerClient(QWidget * parent):QDialog(parent)
{
    setWindowTitle(tr("多线程时间服务客户端"));

    // [0] 构造服务器连接信息,及布局
    m_serverNameLabel = new QLabel(tr("服务器名: "));
    m_serverLineEdit = new QLineEdit("Localhost");
    m_portLabel      = new QLabel(tr("端口"));
    m_portLineEdit   = new QLineEdit;



    QGridLayout *layout = new QGridLayout;
    layout->addWidget(m_serverNameLabel,0,0);
    layout->addWidget(m_serverLineEdit,0,1);
    layout->addWidget(m_portLabel,1,0);
    layout->addWidget(m_portLineEdit,1,1);
    // [0] 构造服务器连接信息,及布局 [本块结束]

    // [1] 构造控制 按钮及提示信息的对象和布局
    m_stateLabel     = new QLabel(tr("请首先运行时间服务器!"));
    m_getBtn         = new QPushButton(tr("获取时间"));
    m_quitBtn        = new QPushButton(tr("退出"));
    m_dateTimeEdit   = new QDateTimeEdit;

    QHBoxLayout *hLayout_1 = new QHBoxLayout;
    hLayout_1->addStretch();
    hLayout_1->addWidget(m_getBtn);
    hLayout_1->addWidget(m_quitBtn);
    // [1] 构造控制 按钮及提示信息的对象和布局 [本块结束]

    // [2] 最终布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(layout);
    mainLayout->addWidget(m_dateTimeEdit);
    mainLayout->addWidget(m_stateLabel);
    mainLayout->addLayout(hLayout_1);
    // [2] 最终布局 [本块结束]

    // [3] 设置控件的默认属性
    m_portLineEdit->setFocus();
    m_getBtn->setDefault(true);
    m_getBtn->setEnabled(false);
    // [3] 设置控件的默认属性 [本块结束]

    connect(m_serverLineEdit,&QLineEdit::textChanged,this,&CTimerClient::enableGetBtn);
    connect(m_portLineEdit,&QLineEdit::textChanged,this,&CTimerClient::enableGetBtn);
    connect(m_getBtn,&QPushButton::clicked,this,&CTimerClient::getTime);
    connect(m_quitBtn,&QPushButton::clicked,this,&CTimerClient::close);

    m_tcpSocket = new QTcpSocket(this);
    using ErrorSignal = void (QTcpSocket::*)(QAbstractSocket::SocketError);
    connect(m_tcpSocket,&QTcpSocket::readyRead,this,&CTimerClient::readTime);
    connect(m_tcpSocket, static_cast<ErrorSignal>(&QTcpSocket::error),this,&CTimerClient::slot_Error);
}

CTimerClient::~CTimerClient()
{

}

void CTimerClient::enableGetBtn()
{
    m_getBtn->setEnabled(!m_serverLineEdit->text().isEmpty() && !m_portLineEdit->text().isEmpty());
}

void CTimerClient::getTime()
{
    m_getBtn->setEnabled(false);
    m_tcpSocket->abort();
    m_tcpSocket->connectToHost(m_serverLineEdit->text(),m_portLineEdit->text().toInt());
}

void CTimerClient::readTime()
{
    // 将socket作为其设备（device）。这意味着 QDataStream 将从这个套接字中读取数据。
    QDataStream in(m_tcpSocket);
    in.setVersion(QDataStream::Qt_5_12);

    if(m_tcpSocket->bytesAvailable() <(int)sizeof(uint))
        return;
    in >> time2u;
    m_dateTimeEdit->setDateTime(QDateTime::fromTime_t(time2u));
    m_getBtn->setEnabled(true);
}

void CTimerClient::slot_Error(QAbstractSocket::SocketError error)
{
    switch (error) {
    case QAbstractSocket::RemoteHostClosedError:

        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this,tr("时间服务器"),tr("主机不可达"));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this,tr("时间服务器"),tr("连接被拒绝"));
        break;
    default:
        QMessageBox::information(this,tr("时间服务器"),tr("产生如下错误").arg(m_tcpSocket->errorString()));
        break;
    }
}
