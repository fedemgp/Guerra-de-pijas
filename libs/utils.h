#ifndef UTILS_H_
#define UTILS_H_

namespace Utils {

/**
 * @brief This class allows using enums classes as hash keys.
 *
 */
struct EnumClassHash {
    template <typename T>
    std::size_t operator()(T t) const {
        return static_cast<std::size_t>(t);
    }
};
}  // namespace Utils

#endif
