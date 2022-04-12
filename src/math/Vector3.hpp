#pragma once

#include <GL/gl.h>
#include <SFML/System.hpp>
#include <cmath>
#include <ostream>

class Vector3 {
public:
    double x, y, z, w { 1 };

    Vector3()
        : x(0.)
        , y(0.)
        , z(0.) { }
    Vector3(double _x, double _y, double _z)
        : x(_x)
        , y(_y)
        , z(_z) { }
    Vector3(double _x, double _y)
        : x(_x)
        , y(_y)
        , z(0) { }
    Vector3(sf::Vector2f _a)
        : x(_a.x)
        , y(_a.y)
        , z(0) { }
    Vector3(sf::Vector2u _a)
        : x(_a.x)
        , y(_a.y)
        , z(0) { }
    Vector3(sf::Vector2i _a)
        : x(_a.x)
        , y(_a.y)
        , z(0) { }

    double magnitude() const;
    double angle() const;

    void glDraw() const;

    // Return a vector rotated by theta around (0,1,0) axis.
    // FIXME: Support arbitrary axis when this is needed.
    Vector3 rotate_vector(double theta) const;

    double distance_to(Vector3 const& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        double dz = z - other.z;
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }

    Vector3 normalized() const;
    double dot(const Vector3& a) const;
    Vector3 cross(const Vector3& a) const;

    friend std::ostream& operator<<(std::ostream& out, const Vector3& vec) {
        return out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
    }
};

inline Vector3 operator+(const Vector3& a, const Vector3& b) { return Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vector3 operator*(const Vector3& a, double b) { return Vector3(a.x * b, a.y * b, a.z * b); }
inline Vector3 operator*(double a, const Vector3& b) { return Vector3(a * b.x, a * b.y, a * b.z); }
inline Vector3 operator/(const Vector3& a, double b) { return Vector3(a.x / b, a.y / b, a.z / b); }
inline Vector3 operator-(const Vector3& a) { return Vector3(-a.x, -a.y, -a.z); }

inline Vector3& operator+=(Vector3& a, const Vector3& b) { return a = a + b; }
inline Vector3& operator-=(Vector3& a, const Vector3& b) { return a = a - b; }
inline Vector3& operator*=(Vector3& a, double b) { return a = a * b; }
inline Vector3& operator/=(Vector3& a, double b) { return a = a / b; }

inline bool operator==(const Vector3& a, const Vector3& b) { return a.x == b.x && a.y == b.y && a.z == b.z; }
inline bool operator!=(const Vector3& a, const Vector3& b) { return !(a == b); }

inline double Vector3::magnitude() const {
    return std::sqrt(x * x + y * y + z * z);
}

inline double Vector3::angle() const {
    return (std::atan2(y, x));
}

inline Vector3 Vector3::rotate_vector(double theta) const {
    double t_cos = std::cos(theta), t_sin = std::sin(theta);

    return Vector3(x * t_cos - y * t_sin, x * t_sin + y * t_cos, z);
}

inline Vector3 Vector3::normalized() const {
    return Vector3(x, y, z) / magnitude();
}

inline double Vector3::dot(const Vector3& a) const{
    return this->x * a.x + this->y * a.y + this->z * a.z;
}

inline Vector3 Vector3::cross(const Vector3& a) const{
    Vector3 result;
    result.x = this->y * a.z - this->z * a.y;
    result.y = this->z * a.x - this->x * a.z;
    result.z = this->x * a.y - this->y * a.x;

    return result;
}

inline double get_distance(Vector3 a, Vector3 b) {
    return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}

inline double get_distance_to_line(Vector3 a, Vector3 b, Vector3 c) {
    auto d = (c - b) / get_distance(c, b);
    auto v = a - b;
    double t = v.dot(d);
    auto p = b + t * d;

    return get_distance(p, a);
}

inline void Vector3::glDraw() const {
    glVertex3f(x, y, z);
}