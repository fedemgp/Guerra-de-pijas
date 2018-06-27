#ifndef BUFFER_H_
#define BUFFER_H_

#include <arpa/inet.h>
#include <cstdint>
#include <cstring>
#include <string>
#include "Exception.h"

namespace IO {
class Buffer {
   public:
    Buffer();
    explicit Buffer(const std::string &data);
    ~Buffer();

    template <typename NUMERIC>
    void append(NUMERIC v);
    void appendFloat(float v);
    void appendBuffer(void *data, std::size_t dataSize);

    std::string asString();

    template <typename NUMERIC>
    NUMERIC extract();
    float extractFloat();

    void getData(const uint8_t **data, std::size_t *size);

   private:
    void grow();

    uint8_t *data{nullptr};
    std::size_t dataSize{0};
    std::size_t offset{0};
};
}  // namespace IO

template <typename NUMERIC>
void IO::Buffer::append(NUMERIC v) {
    switch (sizeof(NUMERIC)) {
        case 1: {
            this->appendBuffer(&v, sizeof(v));
            return;
        }
        case 2: {
            uint16_t vt = htons(v);
            this->appendBuffer(&vt, sizeof(vt));
            return;
        }
        case 4: {
            uint32_t vt = htonl(v);
            this->appendBuffer(&vt, sizeof(vt));
            return;
        }
    }

    /* if it got here, the value couldn't be handled */
    throw Exception{"Invalid type"};
}

template <typename NUMERIC>
NUMERIC IO::Buffer::extract() {
    NUMERIC vt;
    memcpy(&vt, this->data + this->offset, sizeof(NUMERIC));

    if (this->dataSize - this->offset < sizeof(NUMERIC)) {
        throw Exception{"out of buffer"};
    }

    switch (sizeof(NUMERIC)) {
        case 1: {
            this->offset += sizeof(NUMERIC);
            return vt;
        }
        case 2: {
            this->offset += sizeof(NUMERIC);
            return ntohs(vt);
        }
        case 4: {
            this->offset += sizeof(NUMERIC);
            return ntohl(vt);
        }
    }

    /* if it got here, the value couldn't be handled */
    throw Exception{"Invalid type"};
}

#endif
