#include <sys/stat.h>
#include <unistd.h>
#include <QDebug>
#include <QThread>
#include <zmq.hpp>
#include "zmqserver.h"

#define IO_THREADS_NR 1
#define REP_RESPONSE "Done"


ZMQServer::ZMQServer(QObject *parent) : QObject(parent)
{

}


void ZMQServer::processRequest()
{

    //declare the context and PULL-PUSH socket type
    zmq::context_t context (IO_THREADS_NR);
    zmq::socket_t socket(context,ZMQ_PULL);

    //use IPC communication model
    try {

        socket.bind("ipc:///tmp/airtame-browser");
        int result = chmod("/tmp/airtame-browser",ACCESSPERMS);
        if (result != 0) {
            qDebug()<<"Error changeing permissions : " << __FILE__<< __LINE__ << result;
        }

    } catch(zmq::error_t error) {
        qDebug() << __FILE__<< __LINE__<< error.what() << " : " << error.num();
        //send signal to close the application
        emit finished();
    }

    while (true) {
        try {
            zmq::message_t request;
            //  Wait for next request from client
            socket.recv(&request);
            QString clientCommand(request.data<char>());

            //emit signal to the main application thread for processing the command
            emit processData(clientCommand.left(request.size()));
        } catch(zmq::error_t error) {
            qDebug() << __FILE__<< __LINE__<< error.what() << " : " << error.num();
        }
    }

}

