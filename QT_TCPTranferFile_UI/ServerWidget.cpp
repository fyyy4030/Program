#include "ServerWidget.h"
#include "ui_ServerWidget.h"
#include <QFileDialog>
#include <QDebug>
#include <QFileInfo>

ServerWidget::ServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWidget)
{
    ui->setupUi(this);

    tcpServer = new QTcpServer();

    tcpServer->listen(QHostAddress::Any, 8888);
    setWindowTitle("Server Port: 8888");

    ui->button_select->setEnabled(false);
    ui->button_send->setEnabled(false);

    connect(tcpServer, &QTcpServer::newConnection,
            [=]()
            {
                tcpSocket = tcpServer->nextPendingConnection();

                QString ip = tcpSocket->peerAddress().toString();
                quint16 port = tcpSocket->peerPort();

                QString str = QString("[%1:%2] : connect success")
                        .arg(ip)
                        .arg(port);

                qDebug() << str;
                ui->textEdit_2->setText(str);

                ui->button_select->setEnabled(true);

                connect(tcpSocket, &QTcpSocket::readyRead,
                        [=]()
                        {
                          QByteArray buf = tcpSocket->readAll();
                          qDebug() << " server buf: "<< buf;
                          if (QString(buf) == "file done")
                          {
                              ui->textEdit_2->append("file send finished");
                              file.close();

                              tcpSocket->disconnectFromHost();
                              tcpSocket->close();
                          }
                        }
                        );

            }
    );

    connect(&timer, &QTimer::timeout,
            [=]()
            {
                timer.stop();
                sendData();
            }
            );

}

ServerWidget::~ServerWidget()
{
    delete ui;
}

void ServerWidget::on_button_select_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "open", "../");
    if (false == filePath.isEmpty())
    {
        fileName.clear();
        fileSize = 0;

        QFileInfo info(filePath);
        fileName = info.fileName();
        fileSize = info.size();

        sendSize = 0;

        file.setFileName(filePath);

        bool isOk = file.open(QIODevice::ReadOnly);
        if (false == isOk)
        {
            qDebug() << "open file with the way read only error";
        }

        ui->textEdit_2->append(filePath);
        ui->button_select->setEnabled(false);
        ui->button_send->setEnabled(true);
    }
    else
    {
        qDebug() << "select file path error";
    }

}

void ServerWidget::on_button_send_clicked()
{
    ui->button_send->setEnabled(false);

    QString head = QString("%1##%2").arg(fileName).arg(fileSize);
    qint64 len = tcpSocket->write(head.toUtf8());
    qDebug() << "server on_button_send_clicked";
    if (len > 0)
    {
        timer.start(20);
    }
    else
    {
        qDebug() << "head infomation send error";
        file.close();
        ui->button_select->setEnabled(true);
        ui->button_send->setEnabled(false);
    }
}

void ServerWidget::sendData()
{
    ui->textEdit_2->append("sending file...");
    qDebug() << "server sendData";
    qint64 len = 0;

    do
    {
        char buf[4*1024] = {0};
        len = 0;
        len = file.read(buf, sizeof(buf));
        len = tcpSocket->write(buf, len);

        sendSize += len;
    }while (len > 0);

//    if (sendSize == file)
//    {
//        ui->textEdit_2->append("send file success");
//        file.close();

//        tcpSocket->disconnectFromHost();
//        tcpSocket->close();
//    }
}
