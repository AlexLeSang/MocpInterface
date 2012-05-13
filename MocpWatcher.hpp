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
};

#endif // MOCPWATCHER_HPP
