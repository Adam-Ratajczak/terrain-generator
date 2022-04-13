#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include "math/PerlinNoise.hpp"

class World{
private:
    std::vector<std::vector<float>> m_terrain;
    std::vector<std::vector<float>> m_humidity;
    std::vector<std::vector<float>> m_temperature;
    unsigned m_size_x, m_size_y;

	siv::PerlinNoise::seed_type m_terrain_seed;
	siv::PerlinNoise::seed_type m_humidity_seed;
	siv::PerlinNoise::seed_type m_temperature_seed;

	siv::PerlinNoise m_terrain_perlin;
	siv::PerlinNoise m_humidity_perlin;
	siv::PerlinNoise m_temperature_perlin;

    void m_recalculate();
    sf::Color m_get_coord_color(unsigned x, unsigned y) const;
    sf::Texture m_cal_texture(sf::Vector2u sizes) const;

public:

    enum class TerrainType{
        DEEPOCEAN,
        OCEAN,
        SEASHORE,
        COAST,
        PLAINS,
        HILLS,
        HIGHTLANDS,
        MOUNTAINS,
        HIGHMOUNTAINS
    };

    enum class HumidityType{
        WATERY,
        WET,
        MEDIOCRE,
        DRY,
        DROUGHT
    };

    enum class TemperatureType{
        FREEZING,
        SNOWY,
        COLD,
        CHILLY,
        MEDIOCRE,
        WARM,
        HOT,
        BOILING
    };

    enum class Biome{
        
    };

    World(sf::Vector2u size, unsigned terrain_seed, unsigned humidity_seed, unsigned temperature_seed);
    void draw(sf::RenderWindow& window) const;
};
