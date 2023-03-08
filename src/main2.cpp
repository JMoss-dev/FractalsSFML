#include <iostream>
#include <cmath>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include "Fractal.cpp"

bool isPartOfFractal(float cr, float ci, int numIterations, int rad);
void setColorForIndex(int index);
sf::Color color;

float startzr = 0;

int main()
{
    int desktopHeight = sf::VideoMode::getDesktopMode().height;
    float screenWidth = 3 * desktopHeight / 3;
    float screenHeight = 2 * desktopHeight / 3;
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Fractals");

    int numIterations = 1;

    auto fractalMat = createFractal(-2, 1, -1, 1, numIterations);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized)
            {
                screenWidth = window.getSize().x;
                screenHeight = window.getSize().y;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Period))
        {
            numIterations++;
            fractalMat = createFractal(-2, 1, -1, 1, numIterations);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Comma))
        {
            numIterations--;
            fractalMat = createFractal(-2, 1, -1, 1, numIterations);
        }

        // clear
        window.clear();
        // draw
        auto colorMat = mapIterationsToColor(fractalMat);
        auto image = renderColorMatToImage(colorMat);

        // renderer
        sf::Texture texture;
        texture.loadFromImage(image);
        sf::Sprite sprite(texture);
        sprite.setScale(screenWidth / sprite.getLocalBounds().width, screenHeight / sprite.getLocalBounds().height);
        window.draw(sprite);
        window.display();
    }

    return 0;
}

// g++ -c .\src\main.cpp -I..\SFML-2.5.1\include
// g++ main.o -o sfml-app -L..\SFML-2.5.1\lib\ -lsfml-graphics -lsfml-window -lsfml-system
// g++ -c .\src\main.cpp -I..\SFML-2.5.1\include -o out\main.o; g++ out\main.o -o out\sfml-app -L..\SFML-2.5.1\lib\ -lsfml-graphics -lsfml-window -lsfml-system; .\out\sfml-app.exe