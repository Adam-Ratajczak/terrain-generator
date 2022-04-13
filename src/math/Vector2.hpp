#pragma once

#include <GL/gl.h>
#include <SFML/System.hpp>
#include <cmath>
#include <ostream>

class Vector2 {
public:
    double x, y { 1 };

    Vector2()
        : x(0.)
        , y(0.) { }
    Vector2(double _x, double _y, double _z)
        : x(_x)
        , y(_y) { }
    Vector2(double _x, double _y)
        : x(_x)
        , y(_y) { }
    Vector2(sf::Vector2f _a)
        : x(_a.x)
        , y(_a.y) { }
    Vector2(sf::Vector2u _a)
        : x(_a.x)
        , y(_a.y) { }
    Vector2(sf::Vector2i _a)
        : x(_a.x)
        , y(_a.y)  { }

    double magnitude() const;
    double angle() const;

    void glDraw() const;

    // Return a vector rotated by theta around (0,1,0) axis.
    // FIXME: Support arbitrary axis when this is needed.
    Vector2 rotate_vector(double theta) const;

    double distance_to(Vector2 const& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    Vector2 normalized() const;
    double dot(const Vector2& a) const;
    Vector2 cross(const Vector2& a) const;

    friend std::ostream& operator<<(std::ostream& out, const Vector2& vec) {
        return out << "(" << vec.x << ", " << vec.y << ")";
    }
};

inline Vector2 operator+(const Vector2& a, const Vector2& b) { return Vector2(a.x + b.x, a.y + b.y); }
inline Vector2 operator-(const Vector2& a, const Vector2& b) { return Vector2(a.x - b.x, a.y - b.y); }
inline Vector2 operator*(const Vector2& a, double b) { return Vector2(a.x * b, a.y * b * b); }
inline Vector2 operator*(double a, const Vector2& b) { return Vector2(a * b.x, a * b.y); }
inline Vector2 operator/(const Vector2& a, double b) { return Vector2(a.x / b, a.y / b); }
inline Vector2 operator-(const Vector2& a) { return Vector2(-a.x, -a.y); }

inline Vector2& operator+=(Vector2& a, const Vector2& b) { return a = a + b; }
inline Vector2& operator-=(Vector2& a, const Vector2& b) { return a = a - b; }
inline Vector2& operator*=(Vector2& a, double b) { return a = a * b; }
inline Vector2& operator/=(Vector2& a, double b) { return a = a / b; }

inline bool operator==(const Vector2& a, const Vector2& b) { return a.x == b.x && a.y == b.y;}
inline bool operator!=(const Vector2& a, const Vector2& b) { return !(a == b); }

inline double Vector2::magnitude() const {
    return std::sqrt(x * x + y * y);
}

inline double Vector2::angle() const {
    return (std::atan2(y, x));
}

inline Vector2 Vector2::rotate_vector(double theta) const {
    double t_cos = std::cos(theta), t_sin = std::sin(theta);

    return Vector2(x * t_cos - y * t_sin, x * t_sin + y * t_cos);
}

inline Vector2 Vector2::normalized() const {
    return Vector2(x, y) / magnitude();
}

inline double Vector2::dot(const Vector2& a) const{
    return this->x * a.x + this->y * a.y;
}

inline Vector2 Vector2::cross(const Vector2& a) const{
    Vector2 result;

    return result;
}

inline double get_distance(Vector2 a, Vector2 b) {
    return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

inline double get_distance_to_line(Vector2 a, Vector2 b, Vector2 c) {
    auto d = (c - b) / get_distance(c, b);
    auto v = a - b;
    double t = v.dot(d);
    auto p = b + t * d;

    return get_distance(p, a);
}

inline void Vector2::glDraw() const {
    glVertex3f(x, y, 0);
}
