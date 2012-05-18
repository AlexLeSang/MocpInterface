#ifndef INTERFACEWIDGET_HPP
#define INTERFACEWIDGET_HPP

#include <QtGui/QWidget>
#include <QtGui/QMenu>
#include <QtGui/QAction>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QDialog>
#include <QDesktopWidget>
#include <QtGui/QMouseEvent>

#include "MocpWatcher.hpp"

/*!
 * \file InterfaceWidget.hpp
 * \author Olexandr Halushko alexlesang@gmail.com
 */

/*!
 * \namespace Ui
 * \brief Standart namespace from QtDesigner.
 */
namespace Ui {
class InterfaceWidget;
}

/*!
 * \enum SERVER_STATUS
 * \brief The SERVER_STATUS enum
 */
enum SERVER_STATUS{
    OFF, /*!< Enum value Server Off. */
    ON /*!< Enum value Server On. */
};
<<<<<<< HEAD
/**
* Optimal comparison name lenght is length of QString which is perfect for InterfaceWidget
*
* @brief OPTIMAL_COMPOSITION_NAME_LENGHT
*/
constexpr int OPTIMAL_COMPOSITION_NAME_LENGHT = 42;
/**
* This is offsert from down corner of the screen for InterfaceWidget
*
* @brief DOWN_HEIGHT_OFFSET
*/
constexpr int DOWN_HEIGHT_OFFSET = 27;
=======

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
>>>>>>> 6015f573db8e05038e28d1c84f685c7da6350b88

/*!
 * \class InterfaceWidget
 * \brief The InterfaceWidget class implement interface for mocp player.
 */
class InterfaceWidget : public QWidget {
    Q_OBJECT
<<<<<<< HEAD
    
    QSystemTrayIcon * trayIcon;

    QMenu * contextMenu;

    QAction * stopServerAction;
    QAction * startServerAction;
    QAction * closeAction;
    QAction * showHideAction;
    QAction * openMocpAction;
    QAction * playMocpAction;
    QAction * nextMocpAction;
    QAction * prevMocpAction;
    MocpWatcher * watcher;
=======
>>>>>>> 6015f573db8e05038e28d1c84f685c7da6350b88

public:

    explicit InterfaceWidget(QWidget *parent = 0);
    ~InterfaceWidget();
    
    void    displayServerStatus( SERVER_STATUS serverStatus );
    void    displayComposition( QString composition );
    void    displayTime( QString time );


public slots:

    void    disableStartServerAction();
    void    disableStopServerAction();

<<<<<<< HEAD

=======
>>>>>>> 6015f573db8e05038e28d1c84f685c7da6350b88
private:

    QSystemTrayIcon * trayIcon;

    QMenu * contextMenu;

    QAction * stopServerAction;
    QAction * startServerAction;
    QAction * closeAction;
    QAction * showHideAction;
    QAction * openMocpAction;

    MocpWatcher * watcher;

    Ui::InterfaceWidget *ui;

    void    mouseDoubleClickEvent(QMouseEvent *);
    void    mouseMoveEvent(QMouseEvent * me);

private slots:

    void    showHideSlot();
    void    trayIconClicked( QSystemTrayIcon::ActivationReason reason );

};

#endif // INTERFACEWIDGET_HPP
