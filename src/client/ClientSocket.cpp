/*
 * Created by Federico Manuel Gomez Peter
 * Date: 02/05/2018.
 */

#include <netdb.h>
#include <unistd.h>
#include <cstring>

#include "ClientSocket.h"
#include "ErrorMessages.h"
#include "Exception.h"

ClientSocket::ClientSocket(const char *hostName, const char *port) {
    int status;
    bool is_connected = false;

    struct addrinfo hints = {AI_PASSIVE, AF_INET, SOCK_STREAM, 0, 0, nullptr, nullptr, nullptr};
    struct addrinfo *result, *ptr;

    status = getaddrinfo(hostName, port, &hints, &result);
    if (status != 0) {
        throw Exception(ERR_MSG_SOCKET_INVALID_HOST_OR_PORT, hostName, port, strerror(errno));
    }

    for (ptr = result; ptr != nullptr && !is_connected; ptr = ptr->ai_next) {
        this->fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        /*
        *	si la creación del socket falla, no debo hacer nada mas
        *	en el ciclo (ya que no se abrio ningun fd)
        */
        if (this->fd == -1) {
            continue;
        }

        status = ::connect(this->fd, ptr->ai_addr, ptr->ai_addrlen);
        if (status == -1) {
            ::close(this->fd);
            this->fd = -1;
        } else {
            is_connected = true;
        }
    }

    freeaddrinfo(result);
    if (!is_connected) {
        throw Exception(ERR_MSG_CONNECTION_COULD_NOT_BE_STABLISHED, hostName, port);
    }
}
