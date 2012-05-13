#include "MocpWatcher.hpp"

#include "InterfaceWidget.hpp"

MocpWatcher::MocpWatcher( InterfaceWidget *interface ) : /*QObject( qobject_cast<QObject *> (interface) ),*/ interfaceWidget(interface) {
    mocp = "/usr/bin/mocp";
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
    QString totalTime;
    QString timeLeft;

    while( !interruptFlag ) {
        sleep( 1 );

        process->start( mocp, args );
        process->waitForFinished();
        out = ( process->readAll() );

        if ( out.isEmpty() ) {
            interfaceWidget->displayServerStatus( OFF );
            continue;
        }
        else {
            interfaceWidget->displayServerStatus( ON );
        }

        if ( out.indexOf( "State: STOP" ) != -1 ) {
            interfaceWidget->displayComposition("");
            interfaceWidget->displayTime("00:00/00:00");
            continue;
        }

        int artistStartPos = out.indexOf( "Artist: " ) + 8;
        int songStartPos = out.indexOf( "SongTitle: " ); // 10
        int songEndPos = out.indexOf( "Album:" ) - 1;
        artist = out.mid ( artistStartPos, songStartPos - artistStartPos - 1 ) ;
        song = out.mid( songStartPos + 11, songEndPos - ( songStartPos + 11 ) );

        int totalTimePos = out.indexOf("TotalTime: "); // 11
        int timeLeftPos = out.indexOf("TimeLeft: "); // 10
        int timeLeftEndPos = out.indexOf("TotalSec");

        totalTime = out.mid(totalTimePos + 11, timeLeftPos - 12 - totalTimePos);
        timeLeft = out.mid(timeLeftPos + 10, timeLeftEndPos - 11 - timeLeftPos);
        interfaceWidget->displayComposition(artist + ": " + song);
        interfaceWidget->displayTime(timeLeft + "/" + totalTime);

    }
}


