#include <QApplication>
#include "InterfaceWidget.hpp"

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    Q_INIT_RESOURCE(pictures);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Systray"), QObject::tr("I couldn't detect any system tray on this system."));
        return 1;
    }
    QApplication::setQuitOnLastWindowClosed(false);

    InterfaceWidget w;
    w.show();
    
    return a.exec();
}
