/*
 * Created by Federico Manuel Gomez Peter
 * Date: 02/05/2018.
 */

#ifndef __SERVERSOCKET_H__
#define __SERVERSOCKET_H__

#include <string>

#include "CommunicationSocket.h"
#include "Socket.h"

class ServerSocket : public Socket {
   public:
    explicit ServerSocket(const char *port);
    /**
     * Acepta una conexión y devuelve un CommunicationSocket por movimiento.
     * @return Socket para comunicacion
     */
    CommunicationSocket accept();
    void bindAndListen(const char *port);
};

#endif  //__SERVERSOCKET_H__
