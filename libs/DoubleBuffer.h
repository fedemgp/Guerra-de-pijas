#ifndef DOUBLEBUFFER_H_
#define DOUBLEBUFFER_H_

#include <condition_variable>
#include <mutex>

namespace IO {
template <typename T>
class DoubleBuffer {
   public:
    DoubleBuffer() {}
    ~DoubleBuffer() {}

    void swap();
    void set(const T& instance);
    T get(bool waitNew = false);

   private:
    bool hasData{false};
    T copies[2];
    int current{0};
    std::mutex mutex;
    std::condition_variable dataSet;
};
}  // namespace IO

template <typename T>
void IO::DoubleBuffer<T>::swap() {
    std::unique_lock<std::mutex> lock(this->mutex);
    this->hasData = true;
    this->current = !this->current;
    this->dataSet.notify_all();
}

template <typename T>
void IO::DoubleBuffer<T>::set(const T& instance) {
    std::unique_lock<std::mutex> lock(this->mutex);
    /* sets the new value into the hidden instance */
    this->copies[!this->current] = instance;
}

template <typename T>
T IO::DoubleBuffer<T>::get(bool waitNew) {
    std::unique_lock<std::mutex> lock(this->mutex);
    while (!this->hasData) {
        this->dataSet.wait(lock);
    }

    if(waitNew) {
        this->hasData = false;
    }

    /* returns a copy of the visible instance */
    return this->copies[this->current];
}

#endif
