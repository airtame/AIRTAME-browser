#include "browser.h"
#include <QtNetwork/QLocalSocket>
#include <QFileInfo>

#define TIME_OUT                (500)    // 500ms

BrowserApplication::BrowserApplication(int &argc, char **argv)
    : QApplication(argc, argv)
    , w(NULL)
    , _localServer(NULL) {

    // The application name as the name of the LocalServer
    _serverName = QFileInfo(QCoreApplication::applicationFilePath()).fileName();
    _newLocalServer();
}

void BrowserApplication::_readSocket() {
    QLocalSocket *socket = (QLocalSocket*)sender();
    //Read all data on the socket & store it on a QByteArray
    QByteArray block = socket->readAll();
    QString cmd(block);

    QStringList pieces = cmd.split("\n");

    // Process the commands coming through the socket!
    foreach(QString line, pieces) {
        QStringList vals = line.split(" ");
        if (vals.at(0) == "URL" && vals.length() > 1) {
            qDebug() << "Changing URL to: " << vals.at(1);
            w->setUrl(vals.at(1));
        }
	// FIXME: join stutfz
	if (vals.at(0) == "EVAL" && vals.length() > 1) {
	    qDebug() << "Evaling JS: " << vals.at(1);
	    w->evalJS(vals.at(1));
	}
    }

    delete socket;
}

void BrowserApplication::_newLocalConnection() {
    QLocalSocket *socket = _localServer->nextPendingConnection();
    if(socket) {
        connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));
        connect(socket, SIGNAL(readyRead()), this , SLOT(_readSocket()));
    }
}

void BrowserApplication::_newLocalServer() {
    _localServer = new QLocalServer(this);
    connect(_localServer, SIGNAL(newConnection()), this, SLOT(_newLocalConnection()));
    if(!_localServer->listen(_serverName)) {
        if(_localServer->serverError() == QAbstractSocket::AddressInUseError) {
            QLocalServer::removeServer(_serverName); // <-- A key
            _localServer->listen(_serverName); // Listen again
        }
    }
}
