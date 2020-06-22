#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QTimer>

namespace Ui {
class ServerWidget;
}

class ServerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ServerWidget(QWidget *parent = 0);
    ~ServerWidget();

private slots:
    void on_button_select_clicked();

    void on_button_send_clicked();

    void sendData();

private:
    Ui::ServerWidget *ui;

    QTcpServer* tcpServer;
    QTcpSocket* tcpSocket;

    QFile file;
    QString fileName;
    qint64 fileSize;
    qint64 sendSize;

    QTimer timer;

};

#endif // SERVERWIDGET_H
