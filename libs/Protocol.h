//
// Created by rodrigo on 15/06/18.
//

#ifndef INC_4_WORMS_PROTOCOL_H
#define INC_4_WORMS_PROTOCOL_H


#include <string>
#include <vector>

#include "CommunicationSocket.h"
#include "../src/client/ClientSocket.h"

#define COMMAND_LENGTH 1
#define INT_LENGTH 4

class Protocol {
private:
    CommunicationSocket &socket;

public:
    explicit Protocol(CommunicationSocket &communicationSocket);

//    /* Constructor por movimiento
//     */
//    Protocol(Protocol &&protocol);

    /* Determina si el servidor estableció que la información enviada
     * por el cliente es correcta.
     */
    bool isDataOk();

//    /* Termina la comunicación, cerrando el socket.
//     */
//    void stopCommunication();

    /* El tipo char en este protocolo está asociado a los comandos.
     * En este caso se envía un comando.
     */
    void operator<<(unsigned char command);

    /* Envía un entero de 4 bytes sin signo en big endian.
     */
    void operator<<(unsigned int i);

    /* Envía un unsigned long tratándolo como un entero de 4 bytes
     * sin signo en big endian.
     */
    void operator<<(unsigned long i);

    /* Envía una cadena de caracteres sin el caracter de fin de cadena,
     * primero enviando su longitud como un entero con el método ya definido.
     */
    void operator<<(const std::string &string);

    /* Envía un vector de cadenas de caracteres, enviando cada una
     * por separado, utilizando el método ya definido para cicho fin.
     */
    void operator<<(const std::vector<std::string> &stringVector);

    /* Recibe un comando.
     */
    Protocol & operator>>(unsigned char &command);

    /* Recibe un entero de 4 bytes sin signo en big endian.
     */
    Protocol & operator>>(unsigned int &i);

    /* Recibe una cadena de caracteras recibiendo primero su longitud
     * como un entero de la forma ya especificada y luego los caracteres
     * sin el caracter de fin de cadena.
     */
    Protocol & operator>>(std::string &string);

    /* Recibe un vector de cadenas de caracteres cuya longitud se conoce
     * de antemano. Se reciben todas las cadenas por separado recibiendo
     * de la forma ya indicada.
     */
    Protocol & operator>>(std::vector<std::string> &stringVector);

};


#endif //INC_4_WORMS_PROTOCOL_H
