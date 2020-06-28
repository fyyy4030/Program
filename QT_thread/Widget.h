#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "myThread.h"
#include<QThread>
#include <QImage>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void paintEvent(QPaintEvent *);

    void getImage(QImage);
    void dealClose();


private:
    Ui::Widget *ui;

    QImage image;
    myThread *myT;
    QThread *thread;
};

#endif // WIDGET_H
