#ifndef INTERFACEWIDGET_HPP
#define INTERFACEWIDGET_HPP

#include <QtGui/QWidget>

#include "MocpWatcher.hpp"

namespace Ui {
class InterfaceWidget;
}

enum SERVER_STATUS{
    OFF, ON
};

class InterfaceWidget : public QWidget {
    Q_OBJECT
    
    MocpWatcher * watcher;

public:
    explicit InterfaceWidget(QWidget *parent = 0);
    ~InterfaceWidget();
    
    void    displayServerStatus( SERVER_STATUS serverStatus );
    void    displayComposition( QString composition );
    void    displayTime( QString time );

private:
    Ui::InterfaceWidget *ui;
};

#endif // INTERFACEWIDGET_HPP
