#include "InterfaceWidget.hpp"
#include "ui_InterfaceWidget.h"
/**
* @brief InterfaceWidget::InterfaceWidget
* @param parent
*/
InterfaceWidget::InterfaceWidget(QWidget *parent) : QWidget( parent, Qt::ToolTip ), ui( new Ui::InterfaceWidget ) {
    ui->setupUi(this);

    contextMenu = new QMenu( this );

    stopServerAction = new QAction( tr("&Stop server"), contextMenu );
    startServerAction = new QAction( tr("S&tart server"), contextMenu );
    closeAction = new QAction( tr("&Close"), contextMenu );
    showHideAction = new QAction( tr("Show/&hide"), contextMenu );
    openMocpAction = new QAction( tr("Open mocp"), contextMenu );
    playMocpAction = new QAction( tr("&Play/Pause"), contextMenu );

    contextMenu->addAction( playMocpAction );
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
    connect(playMocpAction,SIGNAL(triggered()),watcher,SLOT(mocpPlay()));
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
/**
* @brief InterfaceWidget::~InterfaceWidget
*/
InterfaceWidget::~InterfaceWidget() {
    watcher->interruptReadLoopSlot();
    while ( watcher->isRunning() ) {
        watcher->wait();
    }
    delete watcher;
    delete ui;
}
/**
* @brief InterfaceWidget::displayServerStatus
* @param serverStatus
*/
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
/**
* @brief InterfaceWidget::displayComposition
* @param composition
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
/**
* @brief InterfaceWidget::displayTime
* @param time
*/
void InterfaceWidget::displayTime(QString time) {
    ui->timeLabel->setText(time);
}

/**
* @brief InterfaceWidget::disableStartServerAction
*/
void InterfaceWidget::disableStartServerAction() {
startServerAction->setDisabled( true );
 stopServerAction->setEnabled( true );
  openMocpAction->setEnabled( true );
}

/**
* @brief InterfaceWidget::disableStopServerAction
*/
void InterfaceWidget::disableStopServerAction() {
  stopServerAction->setDisabled( true );
  startServerAction->setEnabled( true );
  openMocpAction->setDisabled( true );
}

/**
* @brief InterfaceWidget::showHideSlot
*/
void InterfaceWidget::showHideSlot() {
    if ( isVisible() ) {
        hide();
    }
    else {
        show();
    }
}
/**
* @brief InterfaceWidget::trayIconClicked
* @param reason
*/
void InterfaceWidget::trayIconClicked(QSystemTrayIcon::ActivationReason reason) {
    switch ( reason ) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        showHideSlot();
        break;
    case QSystemTrayIcon::MiddleClick:
        watcher->mocpPlay();
        break;
    default:
        break;
    }
}
