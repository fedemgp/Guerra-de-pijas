/*
 * Created by Federico Manuel Gomez Peter
 * Date: 02/05/2018.
 */

#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "Socket.h"

Socket::Socket() : fd(-1) {}

Socket::Socket(int fd) : fd(fd) {}

Socket::Socket(Socket &&other) noexcept : fd(other.fd) {
    other.fd = -1;
}

Socket &Socket::operator=(Socket &&other) noexcept {
    if (this != &other) {
        this->fd = other.fd;
        other.fd = -1;
    }
    return *this;
}

Socket::~Socket() {
    if (this->fd != -1) {
        this->close();
    }
}

void Socket::close() {
    ::close(this->fd);
    this->fd = -1;
}

void Socket::shutdown() {
    ::shutdown(this->fd, SHUT_RDWR);
}
