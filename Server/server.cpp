#include "server.h"
#include "ui_server.h"

#include <QTcpSocket>

Server::Server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);

    tcpServer = new QTcpServer(this);
    // 使用了IPv4的本地主机地址，等价于QHostAddress("127.0.0.1")
    if (!tcpServer->listen(QHostAddress::LocalHost, 6666)) {
        qDebug() << tcpServer->errorString();
        close();
    }

    connect(tcpServer, &QTcpServer::newConnection,
            this, &Server::slotnewConnection);

}

Server::~Server()
{
    delete ui;
}

void Server::slotnewConnection()
{
    qDebug() << "Server::sendMessage()";
    // 用于暂存要发送的数据
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    // 设置数据流的版本，客户端和服务器端使用的版本要相同
    out.setVersion(QDataStream::Qt_5_6);
    out << (quint16)0;
    out << tr("hello TCP!!!");
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    // 获取已经建立的连接的套接字
    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
    connect(clientConnection, &QTcpSocket::disconnected,
            clientConnection, &QTcpSocket::deleteLater);
    clientConnection->write(block);

    //发送完数据后断开连接
//    clientConnection->disconnectFromHost();

    // 发送数据成功后，显示提示
    qDebug() << "发送数据成功!!!";
}
