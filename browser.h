#ifndef BROWSER_H
#define BROWSER_H

#include <QObject>
#include <QApplication>
#include <QtNetwork/QLocalServer>
#include <QWidget>
#include <QThread>
#include "zmqserver.h"
#include "window.h"

class BrowserApplication : public QApplication {
         Q_OBJECT
     public:
         BrowserApplication(int &argc, char **argv);

         bool isRunning();                // Are there instances running
         Window *mainWindow;             // The MainWindow pointer

     private slots:
         // A trigger new connections
         void _newLocalConnection();
         // Read from socket
         void _readSocket();
         void _processDataFromZmqServer(QString data);

     private:
         // Create the server
         void _newLocalServer();
         // Activates the window
         void _activateWindow();
        //starts the zmq server
         void _activateZmqServer();

         QLocalServer *_localServer;     // The local socket Server
         QThread* thread;
         ZMQServer* zmqServer;
         QString _serverName;            // Service name


};

#endif // BROWSER_H
