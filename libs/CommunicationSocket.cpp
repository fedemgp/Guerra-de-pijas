/*
 * Created by Federico Manuel Gomez Peter 
 * Date: 02/05/2018.
 */

#include <sys/socket.h>

#include "CommunicationSocket.h"
#include "ErrorMessages.h"
#include "Exception.h"


CommunicationSocket::CommunicationSocket(int fd): Socket(fd){}

unsigned int CommunicationSocket::send(const char *buffer, unsigned int length){
    unsigned int sent = 0;
    int status = 0;

    while (sent < length){
        status = ::send(this->fd, &buffer[sent], length - sent,
                        MSG_NOSIGNAL);
        /*
         * Inspirado en el ejemplo del ejemplo de ayuda echoserver
         * status == 0: cerraron el socket, lanzo una exepcion de socket cerrado
         * para que no termine correctamente el servidor.
         * status < 0:	hubo un error
         * status > 0:	se enviaron status bytes
         */
        if (status == 0) {
            throw Exception(ERR_MSG_SOCKET_CLOSED);
        } else if (status < 0){
            throw Exception(ERR_MSG_SOCKET_CLOSED_UNEXPECTLY);
        } else{
            sent += status;
        }
    }

    return sent;
}

unsigned int CommunicationSocket::receive(char *buffer, unsigned int length){
    unsigned int received = 0;
    int status = 0;

    while (received < length){
        status = ::recv(this->fd, &buffer[received], length - received,
                        MSG_NOSIGNAL);
        /*
         * Inspirado en el ejemplo del ejemplo de ayuda echoserver
         * status == 0: cerraron el socket, lanzo una exepcion de socket cerrado
         * para que no termine correctamente el servidor.
         * status < 0:	hubo un error
         * status > 0:	se enviaron status bytes
         */
        if (status == 0) {
            throw Exception(ERR_MSG_SOCKET_CLOSED);
        } else if (status < 0){
            throw Exception(ERR_MSG_SOCKET_CLOSED_UNEXPECTLY);
        } else{
            received += status;
        }
    }
    return received;
}
