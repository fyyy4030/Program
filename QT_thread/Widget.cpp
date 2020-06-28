#include "Widget.h"
#include "ui_Widget.h"

#include<QPainter>
#include<QThread>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    myT = new myThread;
    thread = new QThread(this);

    myT->moveToThread(thread);

    thread->start();

    connect(ui->drawImage, &QPushButton::pressed, myT, &myThread::drawImage);

    connect(myT, &myThread::updateImage, this, &Widget::getImage);

    connect(this, &Widget::destroyed, this, &Widget::dealClose);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::getImage(QImage temp)
{
    image = temp;
    update();
}

void Widget::dealClose()
{
    thread->quit();
    thread->wait();
    delete myT;
}

void Widget:: paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawImage(50, 50, image);
}

