/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */

#ifndef __POINT_H__
#define __POINT_H__

// TODO change template for fixed class with float?
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

#endif //__POINT_H__
