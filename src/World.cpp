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

sf::Color World::m_get_coord_color(unsigned x, unsigned y) const{
    TerrainType terrain_type;
    HumidityType humidity_type;
    TemperatureType temperature_type;

    if(m_terrain[x][y] <= 0.1)
        terrain_type = TerrainType::DEEPOCEAN;
    else if(m_terrain[x][y] <= 0.2)
        terrain_type = TerrainType::OCEAN;
    else if(m_terrain[x][y] <= 0.3)
        terrain_type = TerrainType::SEASHORE;
    else if(m_terrain[x][y] <= 0.4)
        terrain_type = TerrainType::COAST;
    else if(m_terrain[x][y] <= 0.6)
        terrain_type = TerrainType::PLAINS;
    else if(m_terrain[x][y] <= 0.7)
        terrain_type = TerrainType::HILLS;
    else if(m_terrain[x][y] <= 0.8)
        terrain_type = TerrainType::HIGHTLANDS;
    else if(m_terrain[x][y] <= 0.9)
        terrain_type = TerrainType::MOUNTAINS;
    else if(m_terrain[x][y] <= 1.0)
        terrain_type = TerrainType::HIGHMOUNTAINS;
    
    if(m_humidity[x][y] <= 0.2)
        humidity_type = HumidityType::WATERY;
    else if(m_humidity[x][y] <= 0.4)
        humidity_type = HumidityType::WET;
    else if(m_humidity[x][y] <= 0.6)
        humidity_type = HumidityType::MEDIOCRE;
    else if(m_humidity[x][y] <= 0.8)
        humidity_type = HumidityType::DRY;
    else if(m_humidity[x][y] <= 1.0)
        humidity_type = HumidityType::DROUGHT;
    
    if(m_temperature[x][y] <= 0.1)
        temperature_type = TemperatureType::FREEZING;
    else if(m_temperature[x][y] <= 0.2)
        temperature_type = TemperatureType::SNOWY;
    else if(m_temperature[x][y] <= 0.3)
        temperature_type = TemperatureType::COLD;
    else if(m_temperature[x][y] <= 0.4)
        temperature_type = TemperatureType::CHILLY;
    else if(m_temperature[x][y] <= 0.7)
        temperature_type = TemperatureType::MEDIOCRE;
    else if(m_temperature[x][y] <= 0.8)
        temperature_type = TemperatureType::WARM;
    else if(m_temperature[x][y] <= 0.9)
        temperature_type = TemperatureType::HOT;
    else if(m_temperature[x][y] <= 1.0)
        temperature_type = TemperatureType::BOILING;
}
