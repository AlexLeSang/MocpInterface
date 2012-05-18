#include "MocpWatcher.hpp"

#include "InterfaceWidget.hpp"

<<<<<<< HEAD
/**
* @brief MocpWatcher::MocpWatcher
* @param interface
*/
=======
/*!
 * \file MocpWatcher.cpp
 * \author Olexandr Halushko alexlesang@gmail.com
 */

/*!
 * \brief MocpWatcher::MocpWatcher
 * \param interface Pointer on interface widget.
 */
>>>>>>> 6015f573db8e05038e28d1c84f685c7da6350b88
MocpWatcher::MocpWatcher( InterfaceWidget *interface ) : interfaceWidget(interface) {
    mocp = "/usr/bin/mocp";
    x_terminal_emulator = "xterm -geometry 200x40+0+0 ";
    args << "-i";
    interruptFlag = false;
}

<<<<<<< HEAD
/**
* @brief MocpWatcher::~MocpWatcher
*/
=======
/*!
 * \brief MocpWatcher::~MocpWatcher
 */
>>>>>>> 6015f573db8e05038e28d1c84f685c7da6350b88
MocpWatcher::~MocpWatcher() {
    delete process;
}

<<<<<<< HEAD
/**
* @brief MocpWatcher::run
*/
=======
/*!
 * \brief MocpWatcher::run
 */
>>>>>>> 6015f573db8e05038e28d1c84f685c7da6350b88
void MocpWatcher::run() {
    process = new QProcess;
    QString out;
    QString artist;
    QString song;
    QString fileName;
    QString totalTime;
    QString timeLeft;
    QByteArray outputByteArray;

    while( !interruptFlag ) {
        sleep( 1 );

        process->start( mocp, args );
        process->waitForFinished();
        outputByteArray = process->readAll();
        out = QString::fromUtf8(outputByteArray.data(),outputByteArray.size());


        if ( out.isEmpty() ) {
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

        if ( out.indexOf( "State: STOP" ) != -1 ) {
            interfaceWidget->displayComposition("");
            interfaceWidget->displayTime("00:00/00:00");
            continue;
        }

        int artistStartPos = out.indexOf( "Artist: " ) + 8;
        int songStartPos = out.indexOf( "SongTitle: " ); // 10
        int songEndPos = out.indexOf( "Album:" ) - 1;
        int fileNamePos = out.indexOf("File:") + 6;

        fileName = out.mid(fileNamePos, out.indexOf( "Title:" ) - 1 - fileNamePos);
        fileName = fileName.mid(fileName.lastIndexOf("/")+1,fileName.length() - fileName.lastIndexOf("/") - 5);
        artist = out.mid ( artistStartPos, songStartPos - artistStartPos - 1 ) ;
        song = out.mid( songStartPos + 11, songEndPos - ( songStartPos + 11 ) );

        int totalTimePos = out.indexOf("TotalTime: "); // 11
        int timeLeftPos = out.indexOf("TimeLeft: "); // 10
        int timeLeftEndPos = out.indexOf("TotalSec: ");

        totalTime = out.mid(totalTimePos + 11, timeLeftPos - 12 - totalTimePos);
        timeLeft = out.mid(timeLeftPos + 10, timeLeftEndPos - 11 - timeLeftPos);
        if (! (artist.isEmpty() && song.isEmpty()))
            interfaceWidget->displayComposition(artist + ": " + song);
        else
            interfaceWidget->displayComposition(fileName.replace(" - ",": "));
        interfaceWidget->displayTime(timeLeft + "/" + totalTime);
    }
}

<<<<<<< HEAD
/**
* Set interrupt flag and stop watch loop
*
* @brief MocpWatcher::interruptReadLoopSlot
*/
=======
/*!
 * \brief MocpWatcher::interruptReadLoopSlot
 */
>>>>>>> 6015f573db8e05038e28d1c84f685c7da6350b88
void MocpWatcher::interruptReadLoopSlot() {
    interruptFlag = true;
}

<<<<<<< HEAD
/**
* @brief MocpWatcher::stopServerSlot
*/
=======
/*!
 * \brief MocpWatcher::stopServerSlot
 */
>>>>>>> 6015f573db8e05038e28d1c84f685c7da6350b88
void MocpWatcher::stopServerSlot() {
    QStringList stopList;
    stopList << "-x";
    QProcess::startDetached( mocp, stopList );
    interfaceWidget->disableStopServerAction();
}

<<<<<<< HEAD
/**
* @brief MocpWatcher::startServerSlot
*/
=======
/*!
 * \brief MocpWatcher::startServerSlot
 */
>>>>>>> 6015f573db8e05038e28d1c84f685c7da6350b88
void MocpWatcher::startServerSlot() {
    QStringList stopList;
    stopList << "-S";
    QProcess::startDetached( mocp, stopList );
    interfaceWidget->disableStartServerAction();
}

<<<<<<< HEAD
/**
* @brief MocpWatcher::mocpPlay
*/
void MocpWatcher::playMocpSlot()
{
    QStringList play;
    play << "--toggle-pause";
    QProcess::startDetached( mocp, play );
}

void MocpWatcher::nextMocpSlot()
{
    QStringList next;
    next << "--next";
    QProcess::startDetached( mocp, next );
}

void MocpWatcher::prevMocpSlot()
{
    QStringList prev;
    prev << "--previous";
    QProcess::startDetached( mocp, prev );
}

/**
* @brief MocpWatcher::openMocpSlot
*/
=======
/*!
 * \brief MocpWatcher::openMocpSlot
 */
>>>>>>> 6015f573db8e05038e28d1c84f685c7da6350b88
void MocpWatcher::openMocpSlot() {
    QProcess::startDetached( x_terminal_emulator + " " + mocp  );
}


