#include <SFML/Graphics.hpp>
#include <iostream>
#include "tools.h"

#define ROWS      60
#define COLUMNS   80
#define SCANLINES 180

#define SCREEN_WIDTH  960
#define SCREEN_HEIGHT 720

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({960u, 720u}), "The PVG Chip Demo");
    auto [width, height] = window.getSize();
    window.setFramerateLimit(144);
    
    sf::Texture texture( sf::Vector2u(width, height) );
    sf::Sprite sprite(texture);
    
    auto [tw, th] = texture.getSize();
    std::vector<std::uint8_t> pixels(tw * th * 4);
    
    drawRect(10, 44, 5, 5, ColorID::White, pixels);
    drawRect(11, 45, 3, 3, ColorID::Black, pixels);
    drawRect(10, 50, 5, 5, ColorID::Red, pixels);
    drawRect(10, 56, 5, 5, ColorID::Blue, pixels);
    drawRect(10, 62, 5, 5, ColorID::Green, pixels);
    
    drawRect(16, 44, 5, 5, ColorID::White, pixels);
    drawRect(16, 50, 5, 5, ColorID::Magenta, pixels);
    drawRect(16, 56, 5, 5, ColorID::Cyan, pixels);
    drawRect(16, 62, 5, 5, ColorID::Yellow, pixels);
    
    sf::Image logo("assets/logo.png");
    drawImage(22, 44, logo, pixels);
    
    sf::Image demo("assets/demo.png");
    drawImage(55, 64, demo, pixels);
    
    sf::Image parrot("assets/parrot.png");
    drawImage(9, 1, parrot, pixels);
    
    texture.update( pixels.data() );

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
	window.draw(sprite);
        window.display();
    }
}

