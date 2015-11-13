extern "C" {
#include <sys/types.h>
#include <sys/stat.h>
}
#include <zmq.hpp>
#include <QtNetwork/QLocalSocket>
#include <QFileInfo>
#include "browser.h"
#include "zmqserver.h"

#define TIME_OUT                (500)    // 500ms

BrowserApplication::BrowserApplication(int &argc, char **argv)
    : QApplication(argc, argv)
    , mainWindow(NULL)
    , _localServer(NULL)
    ,thread(NULL)
    ,zmqServer(NULL)
{

    // The application name as the name of the LocalServer
    _serverName = QFileInfo(QCoreApplication::applicationFilePath()).fileName();
#ifdef ZMQ_VERSION
    #pragma message "zmq server"
    _activateZmqServer();

#else
    #pragma message "socket server"
    _newLocalServer();
#endif
}

void BrowserApplication::_readSocket()
{
    QLocalSocket *socket = (QLocalSocket*)sender();
    //Read all data on the socket & store it on a QByteArray
    QByteArray block = socket->readAll();

    QString cmd(block);
    //process command
    mainWindow->processCommand(cmd);

    delete socket;
}

void BrowserApplication::_newLocalConnection()
{
    QLocalSocket *socket = _localServer->nextPendingConnection();
    if(socket) {
        connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));
        connect(socket, SIGNAL(readyRead()), this , SLOT(_readSocket()));
    }
}

void BrowserApplication::_newLocalServer()
{
    mode_t last_mode = umask(0);
    _localServer = new QLocalServer(this);
    connect(_localServer, SIGNAL(newConnection()), this, SLOT(_newLocalConnection()));
    if(!_localServer->listen(_serverName)) {
        if(_localServer->serverError() == QAbstractSocket::AddressInUseError) {
            QLocalServer::removeServer(_serverName); // <-- A key
            _localServer->listen(_serverName); // Listen again
        }
    }
    umask(last_mode);
}

void BrowserApplication::_activateZmqServer()
{

    /* Start the zmq server */

    try {
        thread = new QThread();
        zmqServer = new ZMQServer();
    } catch (std::bad_alloc& ba_excep) {
        qDebug() <<__FILE__<< __LINE__<< " bad_alloc caught: " << ba_excep.what();

        if (thread != NULL) {
            delete thread;
            thread = NULL;
        }

        if (zmqServer != NULL) {
            delete zmqServer;
            zmqServer = NULL;
        }

        throw ba_excep;
    }

    zmqServer->moveToThread(thread);
    //bind the signal emitted from the zmq Server to the application slot
    QObject::connect(zmqServer,SIGNAL(processData(QString)),this,SLOT(_processDataFromZmqServer(QString)));

    QObject::connect(thread, SIGNAL(started()), zmqServer, SLOT(processRequest()));
    QObject::connect(zmqServer, SIGNAL(finished()), thread, SLOT(quit()));
    QObject::connect(zmqServer, SIGNAL(finished()), zmqServer, SLOT(deleteLater()));
    QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

void BrowserApplication::_processDataFromZmqServer(QString data)
{
    mainWindow->processCommand(data);
}
