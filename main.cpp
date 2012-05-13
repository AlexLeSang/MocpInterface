#include <QApplication>
#include "InterfaceWidget.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InterfaceWidget w;
    w.show();
    
    return a.exec();
}
