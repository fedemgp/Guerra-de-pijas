/*
 * Created by Federico Manuel Gomez Peter on 02/05/2018.
 */

#ifndef __SOCKET_H__
#define __SOCKET_H__

class Socket {
   protected:
    int fd;
    /**
     * Constructor protegido, las clases hijas ClientSocket, ServerSocket y
     * DataSocket lo usaran para asignar el fd.
     */
    Socket();
    explicit Socket(int fd);
    void close();

   public:
    virtual ~Socket();
    /*
     * La superclase Socket se va a poder mover, pero no copiar.
     */
    Socket(Socket &&other) noexcept;
    Socket &operator=(Socket &&other) noexcept;
    Socket(Socket &other) = delete;
    Socket &operator=(Socket &other) = delete;
    void connect(const char *hostName, const char *port);
    /**
     *  Termina la comunicacion del socket.
     */
    void shutdown();
};

#endif  //__SOCKET_H__
