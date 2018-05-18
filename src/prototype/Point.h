#ifndef WORMS_POINT_H
#define WORMS_POINT_H

namespace Math {
    template <typename Numeric>
    class Point {
    public:
        Point(Numeric x, Numeric y) : x(x), y(y) {}
        ~Point() {}

        Point<Numeric> &operator=(const Point<Numeric> &other) {
            this->x = other.x;
            this->y = other.y;
            return *this;
        }

        Numeric x, y;
    };
}  // namespace Math

#endif //WORMS_POINT_H
