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

public slots:

    void    interruptReadLoopSlot();
    void    stopServerSlot();
    void    startServerSlot();
    void    openMocpSlot();

private:

    QProcess * process; /*!< Watch process pointer */
    InterfaceWidget * interfaceWidget; /*! Interface pointer */
    QString mocp;
    QString x_terminal_emulator;
    QStringList args;
    bool interruptFlag;
};

#endif // MOCPWATCHER_HPP
