#ifndef INTERFACEWIDGET_HPP
#define INTERFACEWIDGET_HPP

#include <QtGui/QWidget>
#include <QtGui/QMenu>
#include <QtGui/QAction>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QDialog>
#include <QDesktopWidget>

#include "MocpWatcher.hpp"
#include <QtGui>

namespace Ui {
class InterfaceWidget;
}

enum SERVER_STATUS{
    OFF, /*!< Enum value Server Off. */
    ON /*!< Enum value Server On. */
};

/*!
 * Optimal comparison name lenght is length of QString which is perfect for InterfaceWidget
 *
 * \brief OPTIMAL_COMPOSITION_NAME_LENGHT
 */
constexpr int OPTIMAL_COMPOSITION_NAME_LENGHT = 42;

/*!
 * This is offsert from down corner of the screen for InterfaceWidget
 *
 * \brief DOWN_HEIGHT_OFFSET
 */

constexpr int DOWN_HEIGHT_OFFSET = 10;

/*!
 * \brief The InterfaceWidget class
 */
class InterfaceWidget : public QWidget {
    Q_OBJECT

public:

    explicit InterfaceWidget(QWidget *parent = 0);
    ~InterfaceWidget();
    
    void    displayServerStatus( SERVER_STATUS serverStatus );
    void    displayComposition( QString composition );
    void    displayTime( QString time );

    void    mousePressEvent(QMouseEvent * me);

public slots:

    void    disableStartServerAction();
    void    disableStopServerAction();

private:

    QSystemTrayIcon * trayIcon;

    QMenu * contextMenu;

    QAction * stopServerAction;
    QAction * startServerAction;
    QAction * closeAction;
    QAction * showHideAction;
    QAction * openMocpAction;

    MocpWatcher * watcher;

    Ui::InterfaceWidget *ui

private slots:

    void    showHideSlot();
    void    trayIconClicked( QSystemTrayIcon::ActivationReason reason );

};

#endif // INTERFACEWIDGET_HPP
