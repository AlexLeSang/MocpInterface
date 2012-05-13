#ifndef MOCPWATCHER_HPP
#define MOCPWATCHER_HPP

#include <QThread>
#include <QProcess>
#include <QDebug>

class InterfaceWidget;

class MocpWatcher : public QThread {
    Q_OBJECT
    QProcess * process;
    InterfaceWidget * interfaceWidget;
    QString mocp;
    QString x_terminal_emulator;
    QStringList args;
    bool interruptFlag;
public:
    explicit MocpWatcher( InterfaceWidget * interface );
    ~MocpWatcher();
    void run();
signals:
    
public slots:
    void    interruptReadLoopSlot() { interruptFlag = true; }

    void    stopServerSlot();
    void    startServerSlot();

    void    openMocpSlot();
};

#endif // MOCPWATCHER_HPP
