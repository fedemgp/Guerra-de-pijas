/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */

#ifndef __POINT_H__
#define __POINT_H__

#define PI 3.14159265

#include <math.h>

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

    Point<Numeric> &operator-=(const Point<Numeric> &other) {
        this->x -= other.x;
        this->y -= other.y;
        return *this;
    }

    Point<Numeric> &operator+=(const Point<Numeric> &other) {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }

    double distance(const Point<Numeric> &other) const {
        Point<Numeric> dist = *this - other;
        return sqrt(dist.x * dist.x + dist.y * dist.y);
    }

    friend Point<Numeric> operator/(const Point<Numeric> &p, Numeric n) {
        return Point<Numeric>{p.x / n, p.y / n};
    }

    friend Point<Numeric> operator*(const Point<Numeric> &p, Numeric n) {
        return Point<Numeric>{p.x * n, p.y * n};
    }

    friend bool operator==(const Point<Numeric> &a, const Point<Numeric> &b) {
        return ((a.x == b.x) && (a.y == b.y));
    }

    friend bool operator!=(const Point<Numeric> &a, const Point<Numeric> &b) {
        return !(a == b);
    }

    friend Point<Numeric> operator+(Point<Numeric> a, const Point<Numeric> &b) {
        /* `a` is passed by value! */
        a += b;
        return a;
    }

    friend Point<Numeric> operator-(Point<Numeric> a, const Point<Numeric> &b) {
        /* `a` is passed by value! */
        a -= b;
        return a;
    }

    Numeric x, y;
};
}  // namespace Math

#endif  //__POINT_H__
