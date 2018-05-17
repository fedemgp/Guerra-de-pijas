/*
 * Created by Federico Manuel Gomez Peter 
 * Date: 17/05/18.
 */

#ifndef __STREAM_H__
#define __STREAM_H__

#include <atomic>
#include <condition_variable>
#include <queue>

#include "Exception.h"

namespace IO {
    template<typename Msg>
    class Stream {
    public:
        Stream() {}

        ~Stream() {
            this->close();
        }

        void push(const Msg &m) {
            std::lock_guard <std::mutex> lock(this->mutex);
            this->q.push(m);
            this->not_empty.notify_all();
        }

        bool pop(Msg &m, bool block = true) {
            std::unique_lock <std::mutex> lock(this->mutex);
            while (this->q.empty() && !this->closed) {
                if (!block) {
                    return false;
                }
                this->not_empty.wait(lock);
            }

            if (this->closed) {
                throw Exception{"closed"};
            }

            m = this->q.front();
            this->q.pop();
            return true;
        }

        Stream &operator<<(const Msg &m) {
            this->push(m);
            return *this;
        }

        Stream &operator>>(Msg &m) {
            this->pop(m);
            return *this;
        }

        void close() {
            if (this->closed) {
                return;
            }
            this->closed = true;
            this->not_empty.notify_all();
        }

    private:
        std::queue<Msg> q;
        std::mutex mutex;
        std::condition_variable not_empty;
        std::atomic<bool> closed{false};
    };
}//namespaces IO
#endif //__STREAM_H__
