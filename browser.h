#ifndef BROWSER_H
#define BROWSER_H

#include <QObject>
#include <QApplication>
#include <QtNetwork/QLocalServer>
#include <QWidget>
#include "window.h"

class BrowserApplication : public QApplication {
         Q_OBJECT
     public:
         BrowserApplication(int &argc, char **argv);

         bool isRunning();                // Are there instances running
         Window *w;                        // The MainWindow pointer

     private slots:
         // A trigger new connections
         void _newLocalConnection();
         // Read from socket
         void _readSocket();

     private:
         // Create the server
         void _newLocalServer();
         // Activates the window
         void _activateWindow();

         QLocalServer *_localServer;     // The local socket Server
         QString _serverName;            // Service name
};

#endif // BROWSER_H
