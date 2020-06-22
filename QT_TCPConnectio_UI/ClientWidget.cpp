#include "ClientWidget.h"
#include "ui_ClientWidget.h"
#include <QHostAddress>

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);

    tcpSocket = NULL;
    tcpSocket = new QTcpSocket(this);

    setWindowTitle("Client");

    connect(tcpSocket, &QTcpSocket::connected,
            [=]()
            {
                QString serverIP = tcpSocket->peerAddress().toString();
                qint16 serverPort = tcpSocket->peerPort();
                QString context = QString("[%1:%2] : Success to build connection with server").arg(serverIP).arg(serverPort);
                ui->textEditRead->setText(context);
            }
            );

    connect(tcpSocket, &QTcpSocket::readyRead,
            [=]()
            {
                QByteArray array = tcpSocket->readAll();
                QString serverIP = tcpSocket->peerAddress().toString();
                qint16 serverPort = tcpSocket->peerPort();
                QString context = QString("[%1:%2] : ").arg(serverIP).arg(serverPort) + array;
                ui->textEditRead->append(context);
            }
            );
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_buttonConnect_clicked()
{
    QString IP = ui->lineEditIP->text();
    qint16 Port = ui->lineEditPort->text().toInt();

    tcpSocket->connectToHost(QHostAddress(IP), Port);

//    QString str = "The connection is established";
//    tcpSocket->write(str.toUtf8().data());
}

void ClientWidget::on_buttonSend_clicked()
{
    QString str = ui->textEditWrite->toPlainText();
    tcpSocket->write(str.toUtf8().data());
}

void ClientWidget::on_buttonClose_clicked()
{
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
    QString str = "The connection is close";
    ui->textEditRead->setText(str);
}
