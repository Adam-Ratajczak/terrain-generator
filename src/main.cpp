#include "World.hpp"
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
    World world(sf::Vector2u(3000, 3000), 1000, 20000, 300000);

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                window.close();
        }

        world.handle_effect(event);

        world.draw(window);
    }
}