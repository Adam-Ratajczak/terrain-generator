#pragma once

#include <cmath>
#include <ostream>

class Length {
public:
    enum Unit {
        Auto,
        Px,
        PxOtherSide,
        Percent
    };

    constexpr Length() = default;

    constexpr Length(Unit unit)
        : m_unit(unit) { }

    constexpr Length(float v, Unit unit)
        : m_value(v)
        , m_unit(unit) { }

    constexpr Unit unit() const { return m_unit; }
    constexpr float value() const { return m_value; }

    constexpr Length operator-() const { return { -m_value, m_unit }; }
    constexpr bool operator==(Length const& other) const { return m_unit == other.m_unit && m_value == other.m_value; }

private:
    friend std::ostream& operator<<(std::ostream& out, Length const& l) { return out << l.m_value << "U" << (int)l.unit(); }

    Unit m_unit = Auto;
    float m_value = 0;
};

constexpr Length operator""_px(long double v) {
    return Length(v, Length::Px);
}

constexpr Length operator""_px_o(long double v) {
    return Length(v, Length::PxOtherSide);
}

class Angle {
public:
    enum Unit {
        Rad,
        Deg
    };

    constexpr Angle() = default;

    constexpr Angle(float v, Unit unit)
        : m_value_in_radians(unit == Deg ? v / 180 * M_PI : v) { }

    constexpr float deg() const { return m_value_in_radians * 180 / M_PI; }
    constexpr float rad() const { return m_value_in_radians; }

    constexpr Angle operator-() const {
        Angle new_angle;
        new_angle.m_value_in_radians = -m_value_in_radians;
        return new_angle;
    }

private:
    float m_value_in_radians = 0;
};

constexpr Angle operator""_deg(long double v) {
    return Angle(v, Angle::Deg);
}

constexpr Angle operator""_rad(long double v) {
    return Angle(v, Angle::Rad);
}
