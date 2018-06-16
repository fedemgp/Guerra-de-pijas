//
// Created by rodrigo on 15/06/18.
//

#include <thread>
#include "Thread.h"

Thread::Thread(Thread &&thread) noexcept {
    this->thread = std::move(thread.thread);
}

Thread & Thread::operator=(Thread &&thread) noexcept {
    this->thread = std::move(thread.thread);
    return *this;
}

void Thread::start() {
    this->thread = std::thread(&Thread::run, this);
}

void Thread::join() {
    this->thread.join();
}
