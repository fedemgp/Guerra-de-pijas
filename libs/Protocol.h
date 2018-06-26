//
// Created by rodrigo on 15/06/18.
//

#ifndef INC_4_WORMS_PROTOCOL_H
#define INC_4_WORMS_PROTOCOL_H


#include <fstream>
#include <netinet/in.h>
#include <string>
#include <vector>

#include "GameStateMsg.h"

#define COMMAND_LENGTH 1
#define INT_LENGTH 4
#define FILE_CHUNK_LENGTH 512

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
    void operator<<(uint32_t i){
        uint32_t networkInt = htonl(i);
        this->socket.send((char *) &networkInt, sizeof(uint32_t));
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

    void operator<<(const IO::LevelInfo &levelInfo){
        *this << levelInfo.id;
        *this << levelInfo.name;
        *this << levelInfo.playersQuantity;
    };

    void operator<<(const IO::GameInfo &info) {
        *this << info.gameID;
        *this << info.levelID;
        *this << info.levelName;
        *this << info.numCurrentPlayers;
        *this << info.numTotalPlayers;
    };

    template <typename T> void operator<<(const std::vector<T> &vec) {
        *this << vec.size();
        for (const auto &elem : vec) {
            *this << elem;
        }
    }

    void operator<<(std::ifstream &file) {
        std::vector<char> chunk(FILE_CHUNK_LENGTH);

        file.seekg(0, file.end);
        uint32_t length = file.tellg();
        file.seekg(0, file.beg);

        *this << length;

        uint32_t charactersToRead = length;

        while (charactersToRead > 0) {
            file.read(chunk.data(), FILE_CHUNK_LENGTH);
            uint32_t charactersRead = file.gcount();
            this->socket.send(chunk.data(), charactersRead);
            charactersToRead -= charactersRead;
        }
    }


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

    Protocol & operator>>(IO::LevelInfo &levelInfo) {
        *this >> levelInfo.id;
        *this >> levelInfo.name;
        *this >> levelInfo.playersQuantity;
        return *this;
    };

    Protocol &operator>>(IO::GameInfo &info){
        *this >> info.gameID;
        *this >> info.levelID;
        *this >> info.levelName;
        *this >> info.numCurrentPlayers;
        *this >> info.numTotalPlayers;
        return *this;
    };

    template <typename T> Protocol &operator>>(std::vector<T> &vec) {
        unsigned int elements{0};
        *this >> elements;
        for (unsigned int i = 0; i < elements; i++) {
            T elem;
            *this >> elem;
            vec.emplace_back(std::move(elem));
        }

        return *this;
    }

    Protocol &operator>>(std::ofstream &file) {
        std::vector<char> chunk(FILE_CHUNK_LENGTH);
        uint32_t fileLength;
        *this >> fileLength;
        uint32_t fileBytesWritten = 0;

        /* La cantidad de bytes a recibir es el mínimo entre los bytes
         * que quedan por recibir y el tamaño máximo de chunk.
         */
        while (fileBytesWritten < fileLength) {
            size_t bytesReceived = this->socket.receive(
                    chunk.data(),
                    std::min(fileLength - fileBytesWritten,
                             (uint32_t) FILE_CHUNK_LENGTH));
            file.write(chunk.data(), bytesReceived);
            fileBytesWritten += bytesReceived;
        }

        return *this;
    }


    /**
     * @brief returns socket by move semantic
     * @return
     */
    SOCKET getSocket() {
        this->socketRemoved = true;
        return std::move(this->socket);
    };

    void stopCommunication() {
        if (!this->socketRemoved) {
            this->socket.shutdown();
        }
    }

    bool socketRemoved{false};
};


#endif //INC_4_WORMS_PROTOCOL_H
