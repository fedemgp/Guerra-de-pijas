#include "Chronometer.h"

Utils::Chronometer::Chronometer() {
    this->prev = std::chrono::high_resolution_clock::now();
}

Utils::Chronometer::~Chronometer() {}

/**
 * @brief Returns the number of milliseconds elapsed since the last call to this function.
 *
 * @return double Milliseconds elapsed.
 */
double Utils::Chronometer::elapsed() {
    std::chrono::high_resolution_clock::time_point current =
        std::chrono::high_resolution_clock::now();

    double dt = std::chrono::duration_cast<std::chrono::duration<double>>(current - prev).count();
    this->prev = current;
    return dt;
}
