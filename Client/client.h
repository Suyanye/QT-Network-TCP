#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>

#include <QTcpSocket>

namespace Ui {
class Client;
}

class Client : public QWidget
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = 0);
    ~Client();

private:
    Ui::Client *ui;

    QTcpSocket *tcpSocket;
    QString message;
    // 用来存放数据的大小信息
    quint16 blockSize;

private slots:
    void newConnect();
    void readMessage();
    void displayError(QAbstractSocket::SocketError);

};

#endif // CLIENT_H
