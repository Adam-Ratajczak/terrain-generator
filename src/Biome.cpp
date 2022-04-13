#include "World.hpp"
#include <SFML/Graphics/Color.hpp>

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
    else
        terrain_type = TerrainType::DEFAULT;
    
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
    else
        humidity_type = HumidityType::DEFAULT;
    
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
    else
        temperature_type = TemperatureType::DEFAULT;

    Biome biome = m_get_biome(terrain_type, humidity_type, temperature_type);

    switch (biome) {
        case Biome::BEACH: return sf::Color(255, 215, 105);
        case Biome::COLD_FOREST: return sf::Color(41, 74, 34);
        case Biome::COLD_FOREST_HILLS: return sf::Color(58, 74, 55);
        case Biome::COLD_MOUNTAINS: return sf::Color(42, 55, 61);
        case Biome::DEEPOCEAN: return sf::Color(0, 38, 56);
        case Biome::DEEPOCEAN_COLD: return sf::Color(60, 72, 94);
        case Biome::DEEPOCEAN_WARM: return sf::Color(0, 68, 191);
        case Biome::DEFAULT: return sf::Color(0, 0, 0);
        case Biome::DESERT: return sf::Color(232, 230, 93);
        case Biome::DESERT_HILLS: return sf::Color(156, 154, 81);
        case Biome::DESERT_MOUNTAINS: return sf::Color(117, 117, 88);
        case Biome::DRY_FOREST: return sf::Color(86, 161, 0);
        case Biome::DRY_FOREST_HILLS: return sf::Color(137, 209, 4);
        case Biome::FJORD: return sf::Color(53, 55, 66);
        case Biome::FOREST: return sf::Color(0, 140, 30);
        case Biome::FOREST_HILLS: return sf::Color(49, 143, 69);
        case Biome::FROZEN_SHALLOW: return sf::Color(41, 107, 145);
        case Biome::GRAVEL_BEACH: return sf::Color(111, 129, 140);
        case Biome::HIGH_MOUNTAINS: return sf::Color(43, 45, 46);
        case Biome::HILLS: return sf::Color(102, 245, 86);
        case Biome::ICY_MOUNTAINS: return sf::Color(95, 139, 158);
        case Biome::ICE_PLAINS: return sf::Color(178, 219, 237);
        case Biome::ICE_PLAINS_HILLS: return sf::Color(133, 218, 255);
        case Biome::JUNGLE: return sf::Color(50, 94, 21);
        case Biome::JUNGLE_HILLS: return sf::Color(61, 115, 25);
        case Biome::JUNGLE_MOUNTAINS: return sf::Color(55, 84, 35);
        case Biome::MOUNTAINS: return sf::Color(107, 115, 102);
        case Biome::OCEAN: return sf::Color(18, 136, 255);
        case Biome::OCEAN_COLD: return sf::Color(105, 179, 255);
        case Biome::OCEAN_WARM: return sf::Color(23, 139, 207);
        case Biome::PLAINS: return sf::Color(58, 189, 38);
        case Biome::SAVANNA: return sf::Color(58, 189, 38);
        case Biome::SAVANNA_HILLS: return sf::Color(115, 179, 27);
        case Biome::SEASHORE: return sf::Color(64, 184, 40);
        case Biome::SEASHORE_FOREST: return sf::Color(29, 143, 6);
        case Biome::SEMIDESERT: return sf::Color(168, 152, 25);
        case Biome::SEMIDESERT_HILLS: return sf::Color(207, 190, 58);
        case Biome::SEMIDESERT_MOUNTAINS: return sf::Color(125, 118, 62);
        case Biome::STEPPE: return sf::Color(147, 163, 0);
        case Biome::STEPPE_HILLS: return sf::Color(172, 189, 17);
        case Biome::TAIGA: return sf::Color(1, 74, 32);
        case Biome::TAIGA_HILLS: return sf::Color(22, 84, 48);
        case Biome::TUNDRA: return sf::Color(218, 229, 230);
        case Biome::TUNDRA_HILLS: return sf::Color(189, 219, 222);
        case Biome::WARM_SEA: return sf::Color(23, 160, 179);
    }
}

World::Biome World::m_get_biome(TerrainType terrain_type, HumidityType humidity_type, TemperatureType temperature_type) const{
    if(terrain_type == TerrainType::DEEPOCEAN){
        if(temperature_type == TemperatureType::FREEZING || temperature_type == TemperatureType::SNOWY || temperature_type == TemperatureType::COLD)
            return Biome::DEEPOCEAN_COLD;
        else if(temperature_type == TemperatureType::CHILLY || temperature_type == TemperatureType::MEDIOCRE || temperature_type == TemperatureType::WARM)
            return Biome::DEEPOCEAN;
        else if(temperature_type == TemperatureType::HOT || temperature_type == TemperatureType::BOILING)
            return Biome::DEEPOCEAN_WARM;
    }else if(terrain_type == TerrainType::OCEAN){
        if(temperature_type == TemperatureType::FREEZING || temperature_type == TemperatureType::SNOWY || temperature_type == TemperatureType::COLD)
            return Biome::OCEAN_COLD;
        else if(temperature_type == TemperatureType::CHILLY || temperature_type == TemperatureType::MEDIOCRE || temperature_type == TemperatureType::WARM)
            return Biome::OCEAN;
        else if(temperature_type == TemperatureType::HOT || temperature_type == TemperatureType::BOILING)
            return Biome::OCEAN_WARM;
    }else if(terrain_type == TerrainType::SEASHORE){
        if(temperature_type == TemperatureType::FREEZING || temperature_type == TemperatureType::SNOWY || temperature_type == TemperatureType::COLD)
            return Biome::FROZEN_SHALLOW;
        else if(temperature_type == TemperatureType::CHILLY || temperature_type == TemperatureType::MEDIOCRE || temperature_type == TemperatureType::WARM)
            return Biome::SEASHORE;
        else if(temperature_type == TemperatureType::HOT || temperature_type == TemperatureType::BOILING)
            return Biome::WARM_SEA;
    }else if(terrain_type == TerrainType::COAST){
        if(temperature_type == TemperatureType::FREEZING || temperature_type == TemperatureType::SNOWY)
            return Biome::FJORD;
        else if(temperature_type == TemperatureType::COLD || temperature_type == TemperatureType::CHILLY)
            return Biome::GRAVEL_BEACH;
        else if((temperature_type == TemperatureType::MEDIOCRE || temperature_type == TemperatureType::WARM) && (humidity_type == HumidityType::WATERY || humidity_type == HumidityType::WET))
            return Biome::SEASHORE_FOREST;
        else if(temperature_type == TemperatureType::MEDIOCRE || temperature_type == TemperatureType::WARM || temperature_type == TemperatureType::HOT || temperature_type == TemperatureType::BOILING)
            return Biome::BEACH;
    }else if(terrain_type == TerrainType::PLAINS){
        if(temperature_type == TemperatureType::FREEZING){
            if(humidity_type == HumidityType::WATERY || humidity_type == HumidityType::WET)
                return Biome::ICE_PLAINS;
            else
                return Biome::TUNDRA;
        }else if(temperature_type == TemperatureType::SNOWY){
            if(humidity_type == HumidityType::WATERY || humidity_type == HumidityType::WET || humidity_type == HumidityType::MEDIOCRE)
                return Biome::TUNDRA;
            else
                return Biome::TAIGA;
        }else if(temperature_type == TemperatureType::COLD || temperature_type == TemperatureType::CHILLY){
            if(humidity_type == HumidityType::WATERY || humidity_type == HumidityType::WET)
                return Biome::COLD_FOREST;
            else
                return Biome::PLAINS;
        }else if(temperature_type == TemperatureType::MEDIOCRE){
            if(humidity_type == HumidityType::WATERY || humidity_type == HumidityType::WET)
                return Biome::FOREST;
            else
                return Biome::PLAINS;
        }else if(temperature_type == TemperatureType::WARM){
            if(humidity_type == HumidityType::WATERY || humidity_type == HumidityType::WET)
                return Biome::DRY_FOREST;
            else
                return Biome::STEPPE;
        }else if(temperature_type == TemperatureType::HOT){
            if(humidity_type == HumidityType::WATERY || humidity_type == HumidityType::WET)
                return Biome::SAVANNA;
            else
                return Biome::SEMIDESERT;
        }else if(temperature_type == TemperatureType::BOILING){
            if(humidity_type == HumidityType::WATERY || humidity_type == HumidityType::WET)
                return Biome::JUNGLE;
            else
                return Biome::DESERT;
        }
    }else if(terrain_type == TerrainType::HILLS || terrain_type == TerrainType::HIGHTLANDS){
        if(temperature_type == TemperatureType::FREEZING){
            if(humidity_type == HumidityType::WATERY || humidity_type == HumidityType::WET)
                return Biome::TUNDRA;
            else
                return Biome::TUNDRA_HILLS;
        }else if(temperature_type == TemperatureType::SNOWY){
            if(humidity_type == HumidityType::WATERY || humidity_type == HumidityType::WET || humidity_type == HumidityType::MEDIOCRE)
                return Biome::TUNDRA_HILLS;
            else
                return Biome::TAIGA_HILLS;
        }else if(temperature_type == TemperatureType::COLD || temperature_type == TemperatureType::CHILLY){
            if(humidity_type == HumidityType::WATERY || humidity_type == HumidityType::WET)
                return Biome::COLD_FOREST_HILLS;
            else
                return Biome::HILLS;
        }else if(temperature_type == TemperatureType::MEDIOCRE){
            if(humidity_type == HumidityType::WATERY || humidity_type == HumidityType::WET)
                return Biome::FOREST_HILLS;
            else
                return Biome::HILLS;
        }else if(temperature_type == TemperatureType::WARM){
            if(humidity_type == HumidityType::WATERY || humidity_type == HumidityType::WET)
                return Biome::DRY_FOREST_HILLS;
            else
                return Biome::STEPPE_HILLS;
        }else if(temperature_type == TemperatureType::HOT){
            if(humidity_type == HumidityType::WATERY || humidity_type == HumidityType::WET)
                return Biome::SAVANNA_HILLS;
            else
                return Biome::SEMIDESERT_HILLS;
        }else if(temperature_type == TemperatureType::BOILING){
            if(humidity_type == HumidityType::WATERY || humidity_type == HumidityType::WET)
                return Biome::JUNGLE_HILLS;
            else
                return Biome::DESERT_HILLS;
        }
    }else if(terrain_type == TerrainType::MOUNTAINS){
        if(temperature_type == TemperatureType::FREEZING){
            if(humidity_type == HumidityType::WATERY || humidity_type == HumidityType::WET)
                return Biome::ICY_MOUNTAINS;
            else
                return Biome::COLD_MOUNTAINS;
        }else if(temperature_type == TemperatureType::SNOWY || temperature_type == TemperatureType::COLD){
            if(humidity_type == HumidityType::WATERY || humidity_type == HumidityType::WET || humidity_type == HumidityType::MEDIOCRE)
                return Biome::COLD_MOUNTAINS;
            else
                return Biome::MOUNTAINS;
        }else if(temperature_type == TemperatureType::CHILLY || temperature_type == TemperatureType::MEDIOCRE || temperature_type == TemperatureType::WARM){
            return Biome::MOUNTAINS;
        }else if(temperature_type == TemperatureType::HOT){
            if(humidity_type == HumidityType::WATERY || humidity_type == HumidityType::WET)
                return Biome::MOUNTAINS;
            else
                return Biome::SEMIDESERT_MOUNTAINS;
        }else if(temperature_type == TemperatureType::BOILING){
            if(humidity_type == HumidityType::WATERY || humidity_type == HumidityType::WET)
                return Biome::JUNGLE_MOUNTAINS;
            else
                return Biome::DESERT_MOUNTAINS;
        }
    }else if(terrain_type == TerrainType::HIGHMOUNTAINS){
        return Biome::HIGH_MOUNTAINS;
    }

    return Biome::DEFAULT;
}
