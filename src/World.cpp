#include "World.hpp"
#include "math/Vector2.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

World::World(sf::Vector2u size, unsigned terrain_seed, unsigned humidity_seed, unsigned temperature_seed) :
            m_size_x(size.x),
            m_size_y(size.y),
            m_terrain_seed(terrain_seed),
            m_humidity_seed(humidity_seed),
            m_temperature_seed(temperature_seed){
                m_terrain_perlin.reseed(terrain_seed);
                m_humidity_perlin.reseed(humidity_seed);
                m_temperature_perlin.reseed(temperature_seed);

                m_prev_mouse_pos = sf::Mouse::getPosition();

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
            m_terrain[x][y] = m_terrain_perlin.octave2D_01((x * 0.001), (y * 0.001), 2);
            m_humidity[x][y] = m_humidity_perlin.octave2D_01((x * 0.0005), (y * 0.0005), 2);
            m_temperature[x][y] = m_temperature_perlin.octave2D_01((x * 0.0005), (y * 0.0005), 2);
        }
    }

    m_recalculate_biomes();
}

void World::m_recalculate_biomes(){
    m_biomes.resize(m_size_x);

    for(unsigned x = 0; x < m_size_x; x++){
        m_biomes[x].resize(m_size_y);
        for(unsigned y = 0; y < m_size_y; y++){
            m_biomes[x][y] = m_get_coord_color(x, y);
        }
    }
}

sf::Texture World::m_cal_texture(Vector2 sizes) const{
    sf::Image img;
    img.create(sizes.x, sizes.y, sf::Color::Black);

    for(int x = 0; x < sizes.x + m_offset.x; x++){
        for(int y = 0; y < sizes.y + m_offset.y; y++){
            if(x < m_size_x && y < m_size_y)
                img.setPixel(x, y, m_biomes[x][y]);
            else
                img.setPixel(x, y, sf::Color::Black);            
        }
    }

    sf::Texture result;
    result.loadFromImage(img);

    return result;
}

void World::handle_effect(sf::Event &event){
    if(event.type == sf::Event::MouseButtonPressed){
        if (event.mouseButton.button == sf::Mouse::Button::Left) {
            m_dragging = true;
            m_prev_mouse_pos = sf::Mouse::getPosition();
            // std::cout << "XD\n";
        }else if (event.mouseButton.button == sf::Mouse::Button::Right) {
            m_display_info = true;
            m_info_pos = sf::Mouse::getPosition();
        }
    }else if(event.type == sf::Event::MouseMoved){
        if(m_dragging){
            Vector2 mouse_pos(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
            m_offset += m_prev_mouse_pos - mouse_pos;
            m_prev_mouse_pos = mouse_pos;
            m_changed = true;
        }
    }else if(event.type == sf::Event::MouseButtonReleased){
        m_dragging = false;
    }
}

void World::draw(sf::RenderWindow &window){
    if(m_changed)
        m_texture = m_cal_texture(window.getSize());
    m_changed = false;

    sf::Sprite sprite;
    sprite.setTexture(m_texture);
    
    window.clear();

    window.draw(sprite);

    window.display();
}
