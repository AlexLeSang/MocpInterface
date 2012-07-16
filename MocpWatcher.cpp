#include "MocpWatcher.hpp"
#include "InterfaceWidget.hpp"

/*!
 * \file MocpWatcher.cpp
 * \author Olexandr Halushko alexlesang@gmail.com
 */

/*!
 * \brief MocpWatcher::MocpWatcher
 * \param interface Pointer on interface widget.
 */
MocpWatcher::MocpWatcher( InterfaceWidget *interface ) : interfaceWidget(interface) {
    mocp = "/usr/bin/mocp";
    x_terminal_emulator = "xterm -geometry 200x40+75+100";
//    args << "-i";
    args << "-Q%state'\n'%artist'\n'%song'\n'%tt'\n'%tl";
    interruptFlag = false;
}

/*!
 * \brief MocpWatcher::~MocpWatcher
 */
MocpWatcher::~MocpWatcher() {
    delete process;
}

/*!
 * \brief MocpWatcher::run
 */
void MocpWatcher::run() {
    process = new QProcess;
    QString out;
    QString status;
    QString artist;
    QString song;
    QString totalTime;
    QByteArray outputByteArray;

    while( !interruptFlag ) {
        sleep( 1 );

        process->start( mocp, args );
        process->waitForFinished();
        outputByteArray = process->readAll();
        out = QString::fromUtf8(outputByteArray.data(),outputByteArray.size());
        // Check status
        status = out.left(out.indexOf('\n') - 1);
        if ( status.isEmpty() ) {
            interfaceWidget->displayServerStatus( OFF );
            interfaceWidget->displayComposition("");
            interfaceWidget->displayTime("00:00/00:00");
            interfaceWidget->disableStopServerAction();
            continue;
        }
        else {
            interfaceWidget->displayServerStatus( ON );
            interfaceWidget->disableStartServerAction();
        }

        // Get artist
        out.remove(0, status.length() + 3);
        artist = out.left(out.indexOf('\n') - 1);

        // Get song
        out.remove(0, artist.length() + 3);
        song = out.left(out.indexOf('\n') - 1);

        // Get total time
        out.remove(0, song.length() + 3);
        totalTime = out.left(out.indexOf('\n') - 1);

        // Get time left
        out.remove(0, totalTime.length() + 3);
        out.chop(1);

        interfaceWidget->displayComposition(artist + ": " + song);
        interfaceWidget->displayTime(out + "/" + totalTime);
    }
}

/*!
 * \brief MocpWatcher::interruptReadLoopSlot
 */
void MocpWatcher::interruptReadLoopSlot() {
   interruptFlag = true;
}

/*!
 * \brief MocpWatcher::stopServerSlot
 */
void MocpWatcher::stopServerSlot() {
    QStringList stopList;
    stopList << "-x";
    QProcess::startDetached( mocp, stopList );
    interfaceWidget->disableStopServerAction();
}

/*!
 * \brief MocpWatcher::startServerSlot
 */
void MocpWatcher::startServerSlot() {
    QStringList stopList;
    stopList << "-S";
    QProcess::startDetached( mocp, stopList );
    interfaceWidget->disableStartServerAction();
}

/*!
 * \brief MocpWatcher::openMocpSlot
 */
void MocpWatcher::openMocpSlot() {
    QProcess::startDetached( x_terminal_emulator + " " + mocp  );
}
