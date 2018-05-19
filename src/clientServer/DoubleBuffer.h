#ifndef DOUBLEBUFFER_H_
#define DOUBLEBUFFER_H_

#include <mutex>

namespace IO {
template <typename T>
class DoubleBuffer {
   public:
    DoubleBuffer() {}
    ~DoubleBuffer() {}

    void swap();
    void set(const T& instance);
    const T get() const;

   private:
    T copies[2];
    int current{0};
    std::mutex mutex;
};
}  // namespace IO

template <typename T>
void IO::DoubleBuffer::swap() {
    std::lock_guard<std::mutex> lock(this->mutex);
    this->current = !this->current;
}

template <typename T>
void IO::DoubleBuffer::set(const T& instance) {
    /* sets the new value into the hidden instance */
    this->current[!this->current] = instance;
}

template <typename T>
void IO::DoubleBuffer::get(const T& instance) {
    /* returns a copy of the visible instance */
    return this->current[this->current];
}

#endif
