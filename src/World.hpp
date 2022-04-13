#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>
#include "math/PerlinNoise.hpp"
#include "math/Vector2.hpp"

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
    sf::Texture m_cal_texture(Vector2 sizes) const;

    sf::Texture m_texture;
    bool m_changed = true, m_dragging = false, m_display_info = false;
    Vector2 m_prev_mouse_pos, m_offset, m_info_pos;
    float m_zoom = 1;

public:

    enum class TerrainType{
        DEEPOCEAN,      OCEAN,
        SEASHORE,       COAST,
        PLAINS,         HILLS,
        HIGHTLANDS,     MOUNTAINS,
        HIGHMOUNTAINS,  DEFAULT
    };

    enum class HumidityType{
        WATERY,         WET,
        MEDIOCRE,       DRY,
        DROUGHT,        DEFAULT
    };

    enum class TemperatureType{
        FREEZING,       SNOWY,
        COLD,           CHILLY,
        MEDIOCRE,       WARM,
        HOT,            BOILING,
        DEFAULT
    };

    enum class Biome{
        DEEPOCEAN_COLD,     DEEPOCEAN,          DEEPOCEAN_WARM,
        OCEAN_COLD,         OCEAN,              OCEAN_WARM,
        FROZEN_SHALLOW,     SEASHORE,           WARM_SEA,
        FJORD,              GRAVEL_BEACH,       BEACH,
        SEASHORE_FOREST,    ICE_PLAINS,         TUNDRA,
        TAIGA,              PLAINS,             COLD_FOREST,
        FOREST,             DRY_FOREST,         SAVANNA,
        SEMIDESERT,         DESERT,             JUNGLE,
        STEPPE,             ICE_PLAINS_HILLS,   TUNDRA_HILLS,
        TAIGA_HILLS,        HILLS,              COLD_FOREST_HILLS,
        FOREST_HILLS,       DRY_FOREST_HILLS,   SAVANNA_HILLS,
        SEMIDESERT_HILLS,   DESERT_HILLS,       JUNGLE_HILLS,
        STEPPE_HILLS,       ICY_MOUNTAINS,      COLD_MOUNTAINS,
        MOUNTAINS,          HIGH_MOUNTAINS,     SEMIDESERT_MOUNTAINS,
        DESERT_MOUNTAINS,   JUNGLE_MOUNTAINS,   DEFAULT
    };

    World(sf::Vector2u size, unsigned terrain_seed, unsigned humidity_seed, unsigned temperature_seed);
    void draw(sf::RenderWindow& window) const;
    void handle_effect(sf::Event& event);

private:
    Biome m_get_biome(TerrainType terrain_type, HumidityType humidity_type, TemperatureType temperature_type) const;
    void m_recalculate_biomes();
    std::vector<std::vector<sf::Color>> m_biomes;
};
