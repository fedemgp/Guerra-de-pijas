//
// Created by rodrigo on 15/06/18.
//

#include <netinet/in.h>
#include "Protocol.h"

Protocol::Protocol(CommunicationSocket &&communicationSocket) :
        socket(std::move(communicationSocket)){
}

bool Protocol::isDataOk() {
    unsigned char command;
    *this >> command;
    return command;
}

//void Protocol::stopCommunication() {
//    this->socket.stopCommunication();
//}

void Protocol::operator<<(const char command) {
    this->socket.send(&command, sizeof(command));
}

void Protocol::operator<<(const unsigned int i) {
    unsigned int networkInt = htonl(i);
    this->socket.send((char *) &networkInt, sizeof(unsigned int));
}

void Protocol::operator<<(const unsigned long i) {
    *this << (unsigned int) i;
}

void Protocol::operator<<(const std::string &string) {
    *this << (unsigned int) string.length();
    this->socket.send(string.c_str(), string.length());
}

void Protocol::operator<<(const std::vector<std::string> &stringVector) {
    for (auto &string : stringVector) {
        *this << string;
    }
}

Protocol &Protocol::operator>>(unsigned char &command) {
    char buffer;
    this->socket.receive(&buffer, COMMAND_LENGTH);
    command = buffer;
    return *this;
}

Protocol &Protocol::operator>>(unsigned int &i) {
    std::vector<char> buffer(INT_LENGTH);
    this->socket.receive(buffer.data(), INT_LENGTH);
    i = ntohl(*(unsigned int *) buffer.data());
    return *this;
}

Protocol &Protocol::operator>>(std::string &string) {
    unsigned int length;
    *this >> length;
    std::vector<char> buffer(length);
    this->socket.receive(buffer.data(), length);
    std::string localString(buffer.data(), length);
    string = std::move(localString);
    return *this;
}

Protocol &Protocol::operator>>(std::vector<std::string> &stringVector) {
    unsigned int elements = stringVector.size();
    for (unsigned int i = 0; i < elements; i++) {
        std::string string;
        *this >> string;
        stringVector[i] = std::move(string);
    }

    return *this;
}

//Protocol::Protocol(Protocol &&protocol) :
//        socket(std::move(protocol.socket)){
//}

