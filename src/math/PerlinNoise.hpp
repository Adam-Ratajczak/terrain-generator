#pragma once

class Perlin{
    unsigned m_seed = 0;
    double fade(double x) const;
    double grad(int hash, double x, double y, double z) const;
    double lerp(double a, double b, double x) const;
public:
    Perlin() = default;
    void set_seed(unsigned seed){m_seed = seed;}
    double perlin(double x, double y, double z) const;
};
