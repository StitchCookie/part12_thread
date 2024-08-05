#include "mainwindow.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include "ctcperver.h"
#include <QMessageBox>

MainWindow::MainWindow(QDialog *parent)
    : QDialog(parent)
{
    setWindowTitle("多线程时间服务器");
    m_label1 = new QLabel(tr("服务器端口"));
    m_label2 = new QLabel;
    m_btn    =  new QPushButton(tr("退出"));
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addStretch(1);
    hLayout->addWidget(m_btn);
    hLayout->addStretch(1);
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->addWidget(m_label1);
    vLayout->addWidget(m_label2);
    vLayout->addLayout(hLayout);
    connect(m_btn,&QPushButton::clicked,this,&MainWindow::close);

    m_count = 0;
    m_server = new CTcperver(this);
    if(!m_server->listen())
    {
        QMessageBox::critical(this,tr("多线程时间服务器"),tr("无法启动服务器: %1").arg(m_server->errorString()));
        close();
        return;
    }
    m_label1->setText(tr("服务器端口: %1").arg(m_server->serverPort()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::slotShow()
{
    m_label2->setText(tr("第%1次请求完毕").arg(++m_count));
}
