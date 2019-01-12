#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QTcpServer>

namespace Ui {
class Server;
}

class Server : public QWidget
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = 0);
    ~Server();

private:
    Ui::Server *ui;

    QTcpServer *tcpServer;

private slots:
      void slotnewConnection();

};

#endif // SERVER_H
