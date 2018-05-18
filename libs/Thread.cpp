/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 29/04/18
 */
#include <thread>

#include "Thread.h"

Thread::Thread() = default;

Thread::~Thread() = default;

Thread::Thread(Thread &&other) noexcept{
    this->thread = std::move(other.thread);
}

void Thread::start(){
    this->thread = std::thread(&Thread::run, this);
}

void Thread::join(){
    this->thread.join();
}

Thread& Thread::operator=(Thread &&other) noexcept{
    this->thread = std::move(other.thread);
    return *this;
}
