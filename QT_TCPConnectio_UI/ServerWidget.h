#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

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
    void on_buttonSend_clicked();

    void on_button_close_clicked();

private:
    Ui::ServerWidget *ui;
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;
};

#endif // SERVERWIDGET_H
