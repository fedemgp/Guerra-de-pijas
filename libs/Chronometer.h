#include <chrono>

namespace Utils {
class Chronometer {
   public:
    Chronometer();
    ~Chronometer();

    double elapsed();

   private:
    std::chrono::high_resolution_clock::time_point prev;
};
}  // namespace Utils
