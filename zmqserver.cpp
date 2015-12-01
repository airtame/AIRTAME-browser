extern "C" {
#include <sys/stat.h>
#include <unistd.h>
}
#include <QDebug>
#include <QThread>
#include "zmq.hpp"
#include "zmqserver.h"

#define IO_THREADS_NR 1

static const std::string path_to_socket_file="/tmp/airtame-browser";
static const std::string address = "ipc://" + path_to_socket_file;



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

        socket.bind(address.c_str());
        int result = chmod(path_to_socket_file.c_str(),ACCESSPERMS);
        if (result != 0) {
            qDebug()<<"Error changing permissions : " << __FILE__<< __LINE__ << result;
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

