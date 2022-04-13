#include "World.hpp"

World::World(sf::Vector2u size, unsigned terrain_seed, unsigned humidity_seed, unsigned temperature_seed) :
            m_size_x(size.x),
            m_size_y(size.y),
            m_terrain_seed(terrain_seed),
            m_humidity_seed(humidity_seed),
            m_temperature_seed(temperature_seed){
                m_terrain_perlin.reseed(terrain_seed);
                m_humidity_perlin.reseed(humidity_seed);
                m_temperature_perlin.reseed(temperature_seed);

                m_recalculate();
            }

void World::m_recalculate(){
    m_terrain.resize(m_size_x);
    m_humidity.resize(m_size_x);
    m_temperature.resize(m_size_x);

    for(unsigned x = 0; x < m_size_x; x++){
        m_terrain[x].resize(m_size_y);
        m_humidity[x].resize(m_size_y);
        m_temperature[x].resize(m_size_y);
        for(unsigned y = 0; y < m_size_y; y++){
            m_terrain[x][y] = m_terrain_perlin.octave2D_01((x * 0.01), (y * 0.01), 4);
            m_humidity[x][y] = m_humidity_perlin.octave2D_01((x * 0.01), (y * 0.01), 4);
            m_temperature[x][y] = m_temperature_perlin.octave2D_01((x * 0.01), (y * 0.01), 4);
        }
    }
}
