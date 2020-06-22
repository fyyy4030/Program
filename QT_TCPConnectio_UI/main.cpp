#include "ServerWidget.h"
#include "ClientWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServerWidget w;
    w.show();

    ClientWidget w2;
    w2.show();

    return a.exec();
}
