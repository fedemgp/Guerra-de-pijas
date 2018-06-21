//
// Created by rodrigo on 15/06/18.
//

#ifndef INC_4_WORMS_THREAD_H
#define INC_4_WORMS_THREAD_H


#include <thread>

class Thread {
private:
    std::thread thread;

public:
    Thread() = default;

    /* El thread del objeto recibido de asigna al propio
     * mediante move semantics.
     */
    Thread(Thread &&thread) noexcept;

    /* El thread del objeto recibido de asigna al propio
     * mediante move semantics.
     */
    Thread & operator=(Thread &&thread) noexcept;

    /* Se elimina el constructor copia ya que no debe usarse para un thread.
     */
    Thread(const Thread&) = delete;

    /* Se elimina el operador asignación ya que no debe usarse para un thread.
     */
    Thread & operator=(const Thread&) = delete;

    /* Comienza la ejecución del hilo.
     */
    void start();

    /* Hace el join del hilo.
     */
    void join();

    /* Este método deben implementarlo todas las clases que hereden de esta,
     * ya que es el método que el thread ejecutará.
     */
    virtual void run() = 0;

    /* Este método deben implementarlo todas las clases que hereden de esta,
     * ya que debe terminar la ejecución del hilo de una forma ordenada.
     */
    virtual void stop() = 0;

    /* El destructor es el default.
     */
    virtual ~Thread() = default;
};


#endif //INC_4_WORMS_THREAD_H
