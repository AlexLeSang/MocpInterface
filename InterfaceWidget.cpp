#include "InterfaceWidget.hpp"
#include "ui_InterfaceWidget.h"

InterfaceWidget::InterfaceWidget(QWidget *parent) : QWidget(parent), ui(new Ui::InterfaceWidget) {
    ui->setupUi(this);
    watcher = new MocpWatcher(this);
    watcher->start();
}

InterfaceWidget::~InterfaceWidget() {
    watcher->interruptReadLoop();
    while ( watcher->isRunning() ) {
        watcher->wait();
    }
    delete watcher;
    delete ui;
}

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

void InterfaceWidget::displayComposition(QString composition) {
    this->ui->artistLabel->setText( composition );
}

void InterfaceWidget::displayTime(QString time) {
    this->ui->timeLabel->setText(time);
}
