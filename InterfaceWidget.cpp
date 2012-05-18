#include "InterfaceWidget.hpp"
#include "ui_InterfaceWidget.h"
<<<<<<< HEAD
/**
* @brief InterfaceWidget::InterfaceWidget
* @param parent
*/
=======

/*!
 * \file InterfaceWidget.cpp
 * \author Olexandr Halushko alexlesang@gmail.com
 */


/*!
 * \brief InterfaceWidget::InterfaceWidget
 * \param parent Pointer on parent QWidget.
 */
>>>>>>> 6015f573db8e05038e28d1c84f685c7da6350b88
InterfaceWidget::InterfaceWidget(QWidget *parent) : QWidget( parent, Qt::ToolTip ), ui( new Ui::InterfaceWidget ) {
    ui->setupUi(this);

    contextMenu = new QMenu( this );

    stopServerAction = new QAction( tr("&Stop server"), contextMenu );
    startServerAction = new QAction( tr("S&tart server"), contextMenu );
    closeAction = new QAction( tr("&Close"), contextMenu );
    showHideAction = new QAction( tr("Show/&hide"), contextMenu );
    openMocpAction = new QAction( tr("Open mocp"), contextMenu );
    playMocpAction = new QAction( tr("&Play/Pause"), contextMenu );
    nextMocpAction = new QAction(tr("&Next"), contextMenu);
    prevMocpAction = new QAction(tr("P&rev"), contextMenu);

    contextMenu->addAction( playMocpAction );
    contextMenu->addAction( nextMocpAction );
    contextMenu->addAction( prevMocpAction );
    contextMenu->addAction( showHideAction );
    contextMenu->addSeparator();
    contextMenu->addAction( openMocpAction );
    contextMenu->addAction( startServerAction );
    contextMenu->addAction( stopServerAction );
    contextMenu->addSeparator();
    contextMenu->addAction( closeAction );



    watcher = new MocpWatcher( this );

    connect( stopServerAction, SIGNAL( triggered() ), watcher, SLOT( stopServerSlot() ) );
    connect( startServerAction, SIGNAL( triggered() ), watcher, SLOT( startServerSlot() ) );
    connect( showHideAction, SIGNAL( triggered() ), this, SLOT( showHideSlot() ) );
    connect( openMocpAction, SIGNAL( triggered() ), watcher, SLOT( openMocpSlot() ) );
    connect(playMocpAction,SIGNAL(triggered()),watcher,SLOT(playMocpSlot()));
    connect( closeAction, SIGNAL( triggered() ), qApp, SLOT( quit() ) );
    connect(nextMocpAction,SIGNAL(triggered()),watcher,SLOT(nextMocpSlot()));
    connect(prevMocpAction,SIGNAL(triggered()),watcher,SLOT(prevMocpSlot()));

    trayIcon = new QSystemTrayIcon( this );
    trayIcon->setContextMenu( contextMenu );
    trayIcon->setIcon( QIcon( ":/icons/mocp_icon.png" ) );
    trayIcon->show();

    connect( trayIcon, SIGNAL( activated(QSystemTrayIcon::ActivationReason) ), this, SLOT( trayIconClicked(QSystemTrayIcon::ActivationReason) ) );

    auto * desktop = QApplication::desktop();

    QPoint posPoint( desktop->size().width() - width(), desktop->size().height() - height() - DOWN_HEIGHT_OFFSET );

    move( posPoint );

    watcher->start();
}
<<<<<<< HEAD
/**
* @brief InterfaceWidget::~InterfaceWidget
*/
=======

/*!
 * \brief InterfaceWidget::~InterfaceWidget
 */
>>>>>>> 6015f573db8e05038e28d1c84f685c7da6350b88
InterfaceWidget::~InterfaceWidget() {
    watcher->interruptReadLoopSlot();
    while ( watcher->isRunning() ) {
        watcher->wait();
    }
    delete watcher;
    delete ui;
}
<<<<<<< HEAD
/**
* @brief InterfaceWidget::displayServerStatus
* @param serverStatus
*/
=======

/*!
 * \brief InterfaceWidget::displayServerStatus
 * \param serverStatus Instance of enum SERVER_STATUS.
 */
>>>>>>> 6015f573db8e05038e28d1c84f685c7da6350b88
void InterfaceWidget::displayServerStatus(SERVER_STATUS serverStatus) {
    switch ( serverStatus ) {
    case OFF:
        this->ui->serverStateLabel->setText("Off");
        break;
    case ON:
        this->ui->serverStateLabel->setText("On");
        break;
    default:
        break;
    }
}
<<<<<<< HEAD
/**
* @brief InterfaceWidget::displayComposition
* @param composition
*/
=======

/*!
 * \brief InterfaceWidget::displayComposition
 * \param composition QString which contains atist and composition name.
 */
>>>>>>> 6015f573db8e05038e28d1c84f685c7da6350b88
void InterfaceWidget::displayComposition(QString composition) {
    if ( composition.size() > OPTIMAL_COMPOSITION_NAME_LENGHT ) {
        QString shortComposition = composition.mid( 0, OPTIMAL_COMPOSITION_NAME_LENGHT - 3 );
        shortComposition.append("...");
        ui->artistLabel->setText( shortComposition );
    }
    else {
        ui->artistLabel->setText( composition );
    }
    trayIcon->setToolTip( composition );
}
<<<<<<< HEAD
/**
* @brief InterfaceWidget::displayTime
* @param time
*/
=======

/*!
 * \brief InterfaceWidget::displayTime
 * \param time QString which containe composition time.
 */
>>>>>>> 6015f573db8e05038e28d1c84f685c7da6350b88
void InterfaceWidget::displayTime(QString time) {
    ui->timeLabel->setText(time);
}

<<<<<<< HEAD
/**
* @brief InterfaceWidget::disableStartServerAction
*/
=======
/*!
 * \brief InterfaceWidget::mouseDoubleClickEvent
 */
void InterfaceWidget::mouseDoubleClickEvent(QMouseEvent *) {
    showHideSlot();
}

/*!
 * \brief InterfaceWidget::mouseMoveEvent
 * \param me Pointer on QMouseEvent.
 */
void InterfaceWidget::mouseMoveEvent(QMouseEvent *me) {

    auto globalX = me->globalX();
    auto globalY = me->globalY();
    auto localX = me->x();
    auto localY = me->y();

    auto moveToX = globalX;
    auto moveToY = globalY;

    if ( localX > 0 ) {
        moveToX += localX;
    }
    if ( localY > 0 ) {
        moveToY += localY;
    }

    move( moveToX, moveToY );
}

/*!
 * \brief InterfaceWidget::disableStartServerAction
 */
>>>>>>> 6015f573db8e05038e28d1c84f685c7da6350b88
void InterfaceWidget::disableStartServerAction() {
startServerAction->setDisabled( true );
 stopServerAction->setEnabled( true );
  openMocpAction->setEnabled( true );
}

<<<<<<< HEAD
/**
* @brief InterfaceWidget::disableStopServerAction
*/
=======
/*!
 * \brief InterfaceWidget::disableStopServerAction
 */
>>>>>>> 6015f573db8e05038e28d1c84f685c7da6350b88
void InterfaceWidget::disableStopServerAction() {
  stopServerAction->setDisabled( true );
  startServerAction->setEnabled( true );
  openMocpAction->setDisabled( true );
}

<<<<<<< HEAD
/**
* @brief InterfaceWidget::showHideSlot
*/
=======
/*!
 * \brief InterfaceWidget::showHideSlot
 */
>>>>>>> 6015f573db8e05038e28d1c84f685c7da6350b88
void InterfaceWidget::showHideSlot() {
    if ( isVisible() ) {
        hide();
    }
    else {
        show();
    }
}
<<<<<<< HEAD
/**
* @brief InterfaceWidget::trayIconClicked
* @param reason
*/
=======

/*!
 * \brief InterfaceWidget::trayIconClicked
 * \param reason QSystemTrayIcon::ActivationReason
 */
>>>>>>> 6015f573db8e05038e28d1c84f685c7da6350b88
void InterfaceWidget::trayIconClicked(QSystemTrayIcon::ActivationReason reason) {
    switch ( reason ) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        showHideSlot();
        break;
    case QSystemTrayIcon::MiddleClick:
        watcher->playMocpSlot();
        break;
    default:
        break;
    }
}
