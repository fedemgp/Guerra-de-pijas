/*
 * Created by Federico Manuel Gomez Peter 
 * Date: 02/05/2018.
 */

#include <cstring>
#include <netdb.h>
#include <unistd.h>

#include "ServerSocket.h"
#include "../common/Exception.h"
#include "../common/ErrorMessages.h"

ServerSocket::ServerSocket(const char *port){
    this->bindAndListen(port);
}

void ServerSocket::bindAndListen(const char *port){
    int status = 0;
    int option_value = 1;
    bool is_bound= false;
    /*
    *	inicializo el bloque de memoria de addrinfo,
    *	lo configuro para que result sea una lista de
    *	address pertenecientes a IPv4, y que sean TCP.
    */
    struct addrinfo hints = {AI_PASSIVE, AF_INET, SOCK_STREAM, 0, 0, nullptr,
                             nullptr, nullptr};
    struct addrinfo *result,*ptr;

    status = getaddrinfo(nullptr, port, &hints, &result);
    if (status != 0){
        throw Exception(ERR_MSG_SOCKET_INVALID_PORT, port,
                        gai_strerror(status));
    }
    /*
    *	Recorro los resultados posibles, hasta poder bindear
    */
    for (ptr = result; ptr != nullptr && !is_bound; ptr = ptr->ai_next){
        this->fd = ::socket(ptr->ai_family, ptr->ai_socktype,
                            ptr->ai_protocol);
        /*
        *	si la creación del socket falla, no debo hacer nada mas
        *	en el ciclo (ya que no se abrio ningun fd)
        */
        if (this->fd == -1){
            continue;
        }
        /*
        *	Del ejemplo del echoserver, se obtuvo la forma de
        *	configurar la reutilización de la dirección
        *	que no se encuentre disponible por un TIME_WAIT.
        *	si la configuración falla, debo liberar
        *	el socket (segun la documentación y el ejemplo
        *	que se encuentra en el manual de getaddrinfo)
        */
        status = setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, &option_value,
                            sizeof(option_value));
        if (status == -1){
            this->close();
            continue;
        }
        /*
        *	Si logro bindear, salgo del ciclo, sino, cierro el socket
        *	y pruebo en el siguiente resultado.
        */
        status = bind(this->fd, result->ai_addr, result->ai_addrlen);
        if (status == -1){
            this->close();
        } else {
            is_bound = true;
        }
    }
    freeaddrinfo(result);

    if (!is_bound){
        throw Exception(ERR_MSG_SOCKET_BINDING,
                        port);
    }

    status = listen(this->fd, 20);
    if (status == -1){
        throw Exception(ERR_MSG_SOCKET_LISTEN, strerror(errno));
    }
}

CommunicationSocket ServerSocket::accept(){
    int fd = ::accept(this->fd, nullptr, nullptr);
    if (fd == -1){
        throw Exception(ERR_MSG_SOCKET_ACCEPT,
                        strerror(errno));
    }
    return std::move(CommunicationSocket(fd));
}