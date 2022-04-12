#include "math/PerlinNoise.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>

int main(){

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Terrain generator");
    auto sizes = window.getSize();

    Perlin perlin;
    sf::Image map;
    map.create(sizes.x, sizes.y, sf::Color::White);

    for(unsigned i = 0; i < sizes.x; i++){
        for(unsigned j = 0; j < sizes.y; j++){
            unsigned val = perlin.perlin(i, j, 0) * 255;
            // std::cout << val << "\n";
            map.setPixel(i, j, sf::Color(val, val, val));
        }
    }

    sf::Texture texture;
    texture.loadFromImage(map);

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(0, 0));

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        window.draw(sprite);

        window.display();
    }
}