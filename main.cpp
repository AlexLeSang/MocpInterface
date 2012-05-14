#include <QApplication>
#include "InterfaceWidget.hpp"

/**
 * @author Olexandr Halushko alexlesang@gmail.com
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @brief main
 * @param argc
 * @param argv
 * @return
 */

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    Q_INIT_RESOURCE(pictures);

    if ( !QSystemTrayIcon::isSystemTrayAvailable() ) {
        QMessageBox::critical(0, QObject::tr("Systray"), QObject::tr("I couldn't detect any system tray on this system."));
        return 1;
    }
    QApplication::setQuitOnLastWindowClosed(false);

    InterfaceWidget w;
    w.show();
    
    return a.exec();
}
