#include "InterfaceWidget.hpp"
#include "ui_InterfaceWidget.h"

/*!
 * \file InterfaceWidget.cpp
 * \author Olexandr Halushko alexlesang@gmail.com
 */


/*!
 * \brief InterfaceWidget::InterfaceWidget
 * \param parent Pointer on parent QWidget.
 */
InterfaceWidget::InterfaceWidget(QWidget *parent) : QWidget( parent, Qt::ToolTip ), ui( new Ui::InterfaceWidget ) {
    ui->setupUi(this);

    contextMenu = new QMenu( this );

    stopServerAction = new QAction( tr("&Stop server"), contextMenu );
    startServerAction = new QAction( tr("S&tart server"), contextMenu );
    closeAction = new QAction( tr("&Close"), contextMenu );
    showHideAction = new QAction( tr("Show/&hide"), contextMenu );
    openMocpAction = new QAction( tr("Open mocp"), contextMenu );
    togglePause = new QAction( tr("&Toggle pause"), contextMenu );
    nextTrack = new QAction( tr("&Next track"), contextMenu );
    prevTrack = new QAction( tr("&Prev track"), contextMenu );

    contextMenu->addAction( showHideAction );
    contextMenu->addAction( togglePause );
    contextMenu->addAction( nextTrack );
    contextMenu->addAction( prevTrack );
    contextMenu->addSeparator();
    contextMenu->addAction( openMocpAction );
    contextMenu->addAction( startServerAction );
    contextMenu->addAction( stopServerAction );
    contextMenu->addSeparator();
    contextMenu->addSeparator();
    contextMenu->addAction( closeAction );

    watcher = new MocpWatcher( this );

    connect( stopServerAction, SIGNAL( triggered() ), watcher, SLOT( stopServerSlot() ) );
    connect( startServerAction, SIGNAL( triggered() ), watcher, SLOT( startServerSlot() ) );

    connect( togglePause, SIGNAL( triggered() ), watcher, SLOT( togglePauseSlot() ) );
    connect( nextTrack, SIGNAL( triggered() ), watcher, SLOT( nextTrackSlot() ) );
    connect( prevTrack, SIGNAL( triggered() ), watcher, SLOT( prevTrackSlot() ) );

    connect( showHideAction, SIGNAL( triggered() ), this, SLOT( showHideSlot() ) );
    connect( openMocpAction, SIGNAL( triggered() ), watcher, SLOT( openMocpSlot() ) );

    connect( closeAction, SIGNAL( triggered() ), qApp, SLOT( quit() ) );

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

/*!
 * \brief InterfaceWidget::~InterfaceWidget
 */
InterfaceWidget::~InterfaceWidget() {
    watcher->interruptReadLoopSlot();
    while ( watcher->isRunning() ) {
        watcher->wait();
    }
    delete watcher;
    delete ui;
}

/*!
 * \brief InterfaceWidget::displayServerStatus
 * \param serverStatus Instance of enum SERVER_STATUS.
 */
void InterfaceWidget::displayServerStatus(SERVER_STATUS serverStatus) {
    switch ( serverStatus ) {
    case OFF:
        ui->serverStateLabel->setText( tr("Off") );
        break;
    case ON:
        ui->serverStateLabel->setText( tr("On") );
        break;
    default:
        break;
    }
}

/*!
 * \brief InterfaceWidget::displayComposition
 * \param composition QString which contains atist and composition name.
 */
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

/*!
 * \brief InterfaceWidget::displayTime
 * \param time QString which containe composition time.
 */
void InterfaceWidget::displayTime(QString time) {
    ui->timeLabel->setText(time);
}

/*!
 * \brief InterfaceWidget::mouseDoubleClickEvent
 */
void InterfaceWidget::mouseDoubleClickEvent(QMouseEvent *) {
    watcher->openMocpSlot();
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

    auto horEnd = moveToX + width();

    auto vertEnd = moveToY + height();

    auto desktopWidth = QApplication::desktop()->width();
    auto desktopHeight = QApplication::desktop()->height();

    if ( ( horEnd > desktopWidth ) || ( vertEnd > desktopHeight ) ) {
        return;
    }
    else {
        move( moveToX, moveToY );
    }
}

/*!
 * \brief InterfaceWidget::disableStartServerAction
 */
void InterfaceWidget::disableStartServerAction() {
    startServerAction->setDisabled( true );
    stopServerAction->setEnabled( true );
    openMocpAction->setEnabled( true );
}

/*!
 * \brief InterfaceWidget::disableStopServerAction
 */
void InterfaceWidget::disableStopServerAction() {
    stopServerAction->setDisabled( true );
    startServerAction->setEnabled( true );
    openMocpAction->setDisabled( true );
}

/*!
 * \brief InterfaceWidget::showHideSlot
 */
void InterfaceWidget::showHideSlot() {
    if ( isVisible() ) {
        hide();
    }
    else {
        show();
    }
}

/*!
 * \brief InterfaceWidget::trayIconClicked
 * \param reason QSystemTrayIcon::ActivationReason
 */
void InterfaceWidget::trayIconClicked(QSystemTrayIcon::ActivationReason reason) {
    switch ( reason ) {
    case QSystemTrayIcon::Trigger:
        showHideSlot();
        break;
    default:
        break;
    }
}
