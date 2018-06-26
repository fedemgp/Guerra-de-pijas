#include "Buffer.h"
#include <cstdlib>
#include <cstring>

IO::Buffer::Buffer() {
    this->dataSize = 2;
    this->data = (uint8_t *)malloc(this->dataSize);
}

IO::Buffer::Buffer(const std::string &data) {
    this->dataSize = data.size();
    this->data = (uint8_t *)malloc(this->dataSize);

    memcpy(this->data, data.data(), data.size());
}

IO::Buffer::~Buffer() {
    if (this->data) {
        free(this->data);
    }
}

std::string IO::Buffer::asString() {
    std::string output;
    output.reserve(this->dataSize);
    output.append((char *)this->data, this->dataSize);
    return output;
}

void IO::Buffer::appendFloat(float v) {
    static_assert(sizeof(v) == 4, "needs 32 bit float");

    union {
        uint32_t u32;
        float f;
    } u;
    u.f = v;
    this->append(u.u32);
}

void IO::Buffer::appendBuffer(void *data, std::size_t dataSize) {
    while (this->dataSize - this->offset < dataSize) {
        this->grow();
    }
    memcpy(this->data + this->offset, data, dataSize);
    this->offset += dataSize;
}

void IO::Buffer::grow() {
    this->dataSize *= 2;
    this->data = static_cast<uint8_t *>(realloc(this->data, this->dataSize));
}

void IO::Buffer::getData(const uint8_t **data, std::size_t *size) {
    *data = this->data;
    *size = this->offset;
}

float IO::Buffer::extractFloat() {
    uint32_t v = this->extract<uint32_t>();
    union {
        uint32_t u32;
        float f;
    } u = {v};
    return u.f;
}
