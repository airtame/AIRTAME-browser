#ifndef ZMQSERVER_H
#define ZMQSERVER_H

#include <QObject>
#include <QString>
#include "window.h"

class BrowserApplication;

class ZMQServer : public QObject
{
    Q_OBJECT
public:
    explicit ZMQServer(QObject *parent = 0);

signals:
    void finished();
    void error(QString error);
    void processData(QString data);

public slots:
     void processRequest();

};

#endif // ZMQSERVER_H
