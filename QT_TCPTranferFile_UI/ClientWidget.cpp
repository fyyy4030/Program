#include "ClientWidget.h"
#include "ui_ClientWidget.h"
#include <QDebug>
#include <QMessageBox>
#include <QHostAddress>

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);

    tcpSocket = new QTcpSocket(this);

    isStart = true;

    //ui->progressBar->setValue(0);

    setWindowTitle("Client");

    connect(tcpSocket, &QTcpSocket::readyRead,
            [=]()
            {
                QByteArray buf = tcpSocket->readAll();
                if (true == isStart)
                {
                    isStart = false;

                    QString temp = QString(buf).toUtf8();
                    qDebug() << "temp : " << temp;
                    fileName = temp.section("##", 0, 0);
                    fileSize = temp.section("##", 1, 1).toInt();

                    qDebug() << "client fileName" << fileName << "fileSize" << fileSize;

                    recvSize = 0;

                    file.setFileName(fileName);

                    bool isOk = file.open(QIODevice::WriteOnly);
                    if (false == isOk)
                    {
                        qDebug() << "WriteOnly error ";

                        tcpSocket->disconnectFromHost();
                        tcpSocket->close();

                        return;
                    }

                    QString str = QString("Receive file: [%1: %2kb]")
                            .arg(fileName)
                            .arg(fileSize/1024);
                   // QMessageBox::information(this, "FileInfo", str);

//                    ui->progressBar->setMinimum(0);

//                    ui->progressBar->setMaximum(fileSize/1024);
//                    ui->progressBar->setValue(0);

                }
                else
                {
                    qint64 len = file.write(buf);

                    if(len > 0)
                    {
                        recvSize += len;
                        qDebug() << "client" << len << "recvSize" << recvSize;
                    }

                    //ui->progressBar->setValue(recvSize/1024);

                    if (recvSize == fileSize)
                    {

                        qDebug() << "file done recvSize : " << recvSize;

                        tcpSocket->write("file done");

                        QMessageBox::information(this, "Finished", "File transfer over");

                        file.close();

                        tcpSocket->disconnectFromHost();
                        tcpSocket->close();

                    }
                }
            }

            );

}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_button_connect_clicked()
{
    QString ip = ui->lineEdit_serverIp->text();
    qint16 port = ui->lineEdit_serverPort->text().toInt();

    tcpSocket->connectToHost(QHostAddress(ip), port);

    isStart = true;
    //ui->progressBar->setValue(0);
}
