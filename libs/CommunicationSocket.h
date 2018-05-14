/*
 * Created by Federico Manuel Gomez Peter
 * Date: 02/05/2018.
 */

#ifndef __COMMUNICATIONSOCKET_H__
#define __COMMUNICATIONSOCKET_H__

#include "Socket.h"
/**
 * Clase que se usa directamente en el servidor para comunicarse con el cliente.
 * Tiene la posibilidad de enviar y recibir mensajes, y es devuelta por
 * movimiento cuando se acepta una conexion.
 *
 * En el cliente, se usa indirectamente, ya que es padre de la clase
 * ClientSocket, la cual tiene la capacidad de realizar un connect al servidor.
 */
class CommunicationSocket : public Socket {
   protected:
    CommunicationSocket() = default;

   public:
    explicit CommunicationSocket(int fd);
    /**
     * Envia length bytes, contenidos en el buffer. Si la conexion falla, se
     * lanza una Exception.Retorna la cantidad de bytes eviados.
     * @param buffer
     * @param length
     * @return
     */
    unsigned int send(const char *buffer, unsigned int length);
    /**
     * Recibe length bytes y los guarda en el buffer. Si la conexion falla, se
     * lanza una Exception. Retorna la cantidad de bytes recibidos.
     * @param buffer
     * @param length
     * @return
     */
    unsigned int receive(char *buffer, unsigned int length);
};

#endif  //__COMMUNICATIONSOCKET_H__
