#ifndef MOCPWATCHER_HPP
#define MOCPWATCHER_HPP

#include <QThread>
#include <QProcess>
#include <QDebug>

/*!
 * \file MocpWatcher.hpp
 * \author Olexandr Halushko alexlesang@gmail.com
 */

class InterfaceWidget;
/*!
 * \class MocpWatcher
 * \brief The MocpWatcher class work with mocp server
 */
class MocpWatcher : public QThread {
    Q_OBJECT

public:
    explicit MocpWatcher( InterfaceWidget * interface );
    ~MocpWatcher();
    void run();

signals:
    
public slots:
    void    interruptReadLoopSlot();
    void    stopServerSlot();
    void    startServerSlot();
    void    playMocpSlot();
    void    nextMocpSlot();
    void    prevMocpSlot();
    void    openMocpSlot();
private:
<<<<<<< HEAD
    QProcess * process;
    InterfaceWidget * interfaceWidget;
=======

    QProcess * process; /*!< Watch process pointer */
    InterfaceWidget * interfaceWidget; /*! Interface pointer */
>>>>>>> 6015f573db8e05038e28d1c84f685c7da6350b88
    QString mocp;
    QString x_terminal_emulator;
    QStringList args;
    bool interruptFlag;
};

#endif // MOCPWATCHER_HPP
