#ifndef IO_H_
#define IO_H_

#include <exception>

namespace IO {
/**
 * @brief Interrupt exception.
 */
class Interrupted : public std::exception {
   public:
    Interrupted() = default;
    ~Interrupted() = default;
};
}  // namespace IO

#endif
