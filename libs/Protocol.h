//
// Created by rodrigo on 15/06/18.
//

#ifndef INC_4_WORMS_PROTOCOL_H
#define INC_4_WORMS_PROTOCOL_H


#include <netinet/in.h>
#include <string>
#include <vector>

#define COMMAND_LENGTH 1
#define INT_LENGTH 4
template <typename SOCKET>
class Protocol {
private:
    SOCKET socket;

public:
    explicit Protocol(SOCKET &socket) : socket(std::move(socket)) {};

//    /* Constructor por movimiento
//     */
//    Protocol(Protocol &&protocol);

//    /* Termina la comunicación, cerrando el socket.
//     */
//    void stopCommunication();

    /* El tipo char en este protocolo está asociado a los comandos.
     * En este caso se envía un comando.
     */
    void operator<<(unsigned char command){
        this->socket.send((const char *) &command, sizeof(command));
    };

    /* Envía un entero de 4 bytes sin signo en big endian.
     */
    void operator<<(unsigned int i){
        unsigned int networkInt = htonl(i);
        this->socket.send((char *) &networkInt, sizeof(unsigned int));
    };

    /* Envía un unsigned long tratándolo como un entero de 4 bytes
     * sin signo en big endian.
     */
    void operator<<(unsigned long i){
        *this << (unsigned int) i;
    };

    /* Envía una cadena de caracteres sin el caracter de fin de cadena,
     * primero enviando su longitud como un entero con el método ya definido.
     */
    void operator<<(const std::string &string){
        *this << (unsigned int) string.length();
        this->socket.send(string.c_str(), string.length());
    };

    /* Envía un vector de cadenas de caracteres, enviando cada una
     * por separado, utilizando el método ya definido para cicho fin.
     */
    void operator<<(const std::vector<std::string> &stringVector){
        *this << stringVector.size();
        for (auto &string : stringVector) {
            *this << string;
        }
    };

    void operator<<(std::vector<std::uint8_t> &uintVector){
        *this << uintVector.size();
        for (auto &uint : uintVector) {
            *this << uint;
        }
    };

    /* Recibe un comando.
     */
    Protocol & operator>>(unsigned char &command){
        char buffer;
        this->socket.receive(&buffer, COMMAND_LENGTH);
        command = buffer;
        return *this;
    };

    /* Recibe un entero de 4 bytes sin signo en big endian.
     */
    Protocol & operator>>(unsigned int &i) {
        std::vector<char> buffer(INT_LENGTH);
        this->socket.receive(buffer.data(), INT_LENGTH);
        i = ntohl(*(unsigned int *) buffer.data());
        return *this;
    };

    /* Recibe una cadena de caracteras recibiendo primero su longitud
     * como un entero de la forma ya especificada y luego los caracteres
     * sin el caracter de fin de cadena.
     */
    Protocol & operator>>(std::string &string) {
        unsigned int length;
        *this >> length;
        std::vector<char> buffer(length);
        this->socket.receive(buffer.data(), length);
        std::string localString(buffer.data(), length);
        string = std::move(localString);
        return *this;
    };

    /* Recibe un vector de cadenas de caracteres cuya longitud se conoce
     * de antemano. Se reciben todas las cadenas por separado recibiendo
     * de la forma ya indicada.
     */
    Protocol & operator>>(std::vector<std::string> &stringVector) {
        unsigned int elements{0};
        *this >> elements;
        for (unsigned int i = 0; i < elements; i++) {
            std::string string;
            *this >> string;
            stringVector.emplace_back(std::move(string));
        }

        return *this;
    };

    Protocol & operator>>(std::vector<std::uint8_t> &uintVector) {
        unsigned int elements{0};
        *this >> elements;
        for (unsigned int i = 0; i < elements; i++) {
            uint8_t uint;
            *this >> uint;
            uintVector.emplace_back(uint);
        }

        return *this;
    };
    /**
     * @brief returns socket by move semantic
     * @return
     */
    SOCKET getSocket() {
        return std::move(this->socket);
    };
};


#endif //INC_4_WORMS_PROTOCOL_H
