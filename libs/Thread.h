/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 29/04/18
 */

#ifndef __server_thread_H__
#define __server_thread_H__

#include <thread>
/**
 * Clase Thread, utilizada para crear objetos vivos (en el caso particular de
 * este tp, ThClient y Server serán objetos vivos).
 */
class Thread{
private:
    std::thread thread;

public:
    Thread();
    /**
     * No se permite el uso de constructor por copia, o la asignación por copia.
     * Esto se hace para evitar copias de threads, y posibles conflictos que
     * esto puede generar.
     */
    Thread(const Thread &copy) = delete;
    Thread(Thread &&other) noexcept;
    virtual ~Thread();
    /**
     * funcion que inicia la operacion en un hilo aparte.
     */
    void start();
    /**
     * Libera los recursos del thread lanzado
     */
    void join();
    virtual void run() = 0;
    Thread& operator=(const Thread &copy) = delete;
    Thread& operator=(Thread &&other) noexcept;
};


#endif //__server_thread_H__
