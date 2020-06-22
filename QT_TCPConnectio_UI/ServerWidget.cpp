#include "ServerWidget.h"
#include "ui_ServerWidget.h"

ServerWidget::ServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWidget)
{
    ui->setupUi(this);

    tcpServer = NULL;
    tcpSocket = NULL;

    tcpServer = new QTcpServer(this);

    tcpServer->listen(QHostAddress::Any, 8888);

    setWindowTitle("server: 8888");
    connect(tcpServer, &QTcpServer::newConnection,
            [=]()
            {
                tcpSocket = tcpServer->nextPendingConnection();

                QString ip = tcpSocket->peerAddress().toString();
                qint16 port = tcpSocket->peerPort();
                QString temp = QString("[%1:%2]: connect success")
                        .arg(ip)
                        .arg(port);

                ui->testEditRead->setText(temp);

                connect(tcpSocket, &QTcpSocket::readyRead,
                        [=]()
                        {
                            QByteArray array = tcpSocket->readAll();
                            QString serverIP = tcpSocket->peerAddress().toString();
                            qint16 serverPort = tcpSocket->peerPort();
                            QString context = QString("[%1:%2] : ").arg(serverIP).arg(serverPort) + array;
                            ui->testEditRead->append(context);
                        }
                        );
            }
            );

}

ServerWidget::~ServerWidget()
{
    delete ui;
}

void ServerWidget::on_buttonSend_clicked()
{
    if (NULL == tcpSocket)
    {
        return ;
    }
    QString str = ui->testEditWrite->toPlainText();
    tcpSocket->write(str.toUtf8().data());
}

void ServerWidget::on_button_close_clicked()
{
    if (NULL == tcpSocket)
    {
        return;
    }
    tcpSocket->disconnectFromHost();
    tcpSocket->close();

    tcpSocket = NULL;

    close();
}
