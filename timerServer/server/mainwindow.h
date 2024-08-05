#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>

class CTcperver;
class QLabel;
class QPushButton;
class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QDialog *parent = nullptr);
    ~MainWindow();
public slots:
    void slotShow();

private:
    QLabel *m_label1;    // 显示监听端口
    QLabel *m_label2;    // 显示请求次数
    QPushButton *m_btn;  // 退出按钮
    CTcperver *m_server; // 服务器server
    int        m_count;  // 请求次数
};
#endif // MAINWINDOW_H
