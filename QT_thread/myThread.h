#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QImage>

class myThread : public QObject
{
    Q_OBJECT
public:
    explicit myThread(QObject *parent = 0);

    void drawImage();

signals:

    void updateImage(QImage temp);

public slots:
};

#endif // MYTHREAD_H
