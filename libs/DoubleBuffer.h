#ifndef DOUBLEBUFFER_H_
#define DOUBLEBUFFER_H_

#include <condition_variable>
#include <mutex>
#include "IO.h"

namespace IO {
template <typename T>
class DoubleBuffer {
   public:
    DoubleBuffer() {}
    ~DoubleBuffer() {}

    void swap();
    void set(const T& instance);
    T get(bool waitNew = false);

    void interrupt();

   private:
    bool hasData{false};
    bool interrupted{false};
    T copies[2];
    int current{0};
    std::mutex mutex;
    std::condition_variable dataSet;
};
}  // namespace IO

/**
 * @brief Swaps the background copy and the current copy.
 */
template <typename T>
void IO::DoubleBuffer<T>::swap() {
    std::unique_lock<std::mutex> lock(this->mutex);
    this->hasData = true;
    this->current = !this->current;
    this->dataSet.notify_all();
}

/**
 * @brief Sets the background copy to the given value.
 *
 * @tparam T Instance type.
 * @param instance The new copy.
 */
template <typename T>
void IO::DoubleBuffer<T>::set(const T& instance) {
    std::unique_lock<std::mutex> lock(this->mutex);
    /* sets the new value into the hidden instance */
    this->copies[!this->current] = instance;
}

/**
 * @brief Gets the current copy.
 *
 * @param waitNew if true, waits until a swap was done from the last time this function was called.
 *                if false, returns the copy eitherway.
 * @return The current copy.
 */
template <typename T>
T IO::DoubleBuffer<T>::get(bool waitNew) {
    std::unique_lock<std::mutex> lock(this->mutex);
    while (!this->hasData && !this->interrupted) {
        this->dataSet.wait(lock);
    }

    if (this->interrupted) {
        throw IO::Interrupted{};
    }

    if (waitNew) {
        this->hasData = false;
    }

    /* returns a copy of the visible instance */
    return this->copies[this->current];
}

/**
 * @brief Interrupts all the threads waiting in "get" launching an exception.
 *        Useful to unblock all the observers.
 */
template <typename T>
void IO::DoubleBuffer<T>::interrupt() {
    this->interrupted = true;
    this->dataSet.notify_all();
}

#endif
