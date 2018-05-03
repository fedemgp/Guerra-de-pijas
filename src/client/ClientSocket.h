/*
 * Created by Federico Manuel Gomez Peter
 * Date: 02/05/2018.
 */

#ifndef __ClientSocket_H__
#define __ClientSocket_H__

#include <string>

#include "CommunicationSocket.h"

/**
 * Socket que tiene la capacidad de realizar una conexion con el servidor,
 * partiendo del dato del host y el port a donde conectarse
 */
class ClientSocket: public CommunicationSocket{
public:
    ClientSocket(const char *hostName, const char *port);
};


#endif //__ClientSocket_H__
