#include "MocpWatcher.hpp"

#include "InterfaceWidget.hpp"

MocpWatcher::MocpWatcher( InterfaceWidget *interface ) : interfaceWidget(interface) {
    mocp = "/usr/bin/mocp";
    x_terminal_emulator = "xterm -geometry 200x40+0+0 ";
    args << "-i";
    interruptFlag = false;
}

MocpWatcher::~MocpWatcher() {
    delete process;
}

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
//        out = ( process->readAll() );

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
        fileName = fileName.mid(fileName.lastIndexOf("/")+1,fileName.length() - fileName.lastIndexOf("/") - 4);
        artist = out.mid ( artistStartPos, songStartPos - artistStartPos - 1 ) ;
        song = out.mid( songStartPos + 11, songEndPos - ( songStartPos + 11 ) );

        int totalTimePos = out.indexOf("TotalTime: "); // 11
        int timeLeftPos = out.indexOf("TimeLeft: "); // 10
        int timeLeftEndPos = out.indexOf("TotalSec");

        totalTime = out.mid(totalTimePos + 11, timeLeftPos - 12 - totalTimePos);
        timeLeft = out.mid(timeLeftPos + 10, timeLeftEndPos - 11 - timeLeftPos);
        if (! (artist.isEmpty() && song.isEmpty()))
        interfaceWidget->displayComposition(artist + ": " + song);
        else
        interfaceWidget->displayComposition(fileName);
        interfaceWidget->displayTime(timeLeft + "/" + totalTime);
    }
}

void MocpWatcher::stopServerSlot() {
    QStringList stopList;
    stopList << "-x";
    QProcess::startDetached( mocp, stopList );
    interfaceWidget->disableStopServerAction();
}

void MocpWatcher::startServerSlot() {
    QStringList stopList;
    stopList << "-S";
    QProcess::startDetached( mocp, stopList );
    interfaceWidget->disableStartServerAction();
}

void MocpWatcher::openMocpSlot() {
    QProcess::startDetached( x_terminal_emulator + " " + mocp  );
}

void MocpWatcher::mocpPlay(){
    QStringList play;
    play << "--toggle-pause";
    QProcess::startDetached( mocp, play );
}
