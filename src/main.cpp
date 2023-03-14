#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "Fractal.cpp"

int main()
{
    int desktopHeight = sf::VideoMode::getDesktopMode().height;
    float screenWidth = 3 * desktopHeight / 3;
    float screenHeight = 2 * desktopHeight / 3;
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Fractals");

    int numIterations = 1;
    double xMin = -2;
    double xMax = 1;
    double yMin = -1;
    double yMax = 1;

    double zoom = 1;

    auto fractalMat = createFractal(xMin, xMax, yMin, yMax, numIterations);

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
            auto fractalMat = createFractal(xMin, xMax, yMin, yMax, numIterations);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Comma))
        {
            numIterations--;
            auto fractalMat = createFractal(xMin, xMax, yMin, yMax, numIterations);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            yMin -= (fabs(yMin) + fabs(yMax)) / 5;
            yMax -= (fabs(yMin) + fabs(yMax)) / 5;
            auto fractalMat = createFractal(xMin, xMax, yMin, yMax, numIterations);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            yMin += (fabs(yMin) + fabs(yMax)) / 5;
            yMax += (fabs(yMin) + fabs(yMax)) / 5;
            auto fractalMat = createFractal(xMin, xMax, yMin, yMax, numIterations);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            xMin -= (fabs(yMin) + fabs(yMax)) / 5;
            xMax -= (fabs(yMin) + fabs(yMax)) / 5;
            auto fractalMat = createFractal(xMin, xMax, yMin, yMax, numIterations);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            xMin += (fabs(yMin) + fabs(yMax)) / 5;
            xMax += (fabs(yMin) + fabs(yMax)) / 5;
            auto fractalMat = createFractal(xMin, xMax, yMin, yMax, numIterations);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp))
        {
            /*zoom += 0.2;
            xMin = xMin / zoom;
            xMax = xMax / zoom;
            yMin = yMin / zoom;
            yMax = yMax / zoom;
            fractalMat = createFractal(xMin, xMax, yMin, yMax, numIterations);*/
            std::cout << "zoomIn\n";
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown))
        {
            /*zoom -= 0.2;
            xMin = xMin / zoom;
            xMax = xMax / zoom;
            yMin = yMin / zoom;
            yMax = yMax / zoom;
            fractalMat = createFractal(xMin, xMax, yMin, yMax, numIterations);*/
            std::cout << "ZoomOut\n";
        }

        // show coordinates
        std::string title = "Fractal";
        double midx = (xMin + xMax) / 2;
        double midy = (yMin + yMax) / 2;
        std::ostringstream pretitle;
        pretitle << "Fractal" << midx << " | " << midy << " | " << zoom;
        window.setTitle(pretitle.str());
        // clear
        window.clear();
        // draw
        // std::cout << fractalMat.size() << "| " << xMin - xMax << "\n";
        auto colorMat = mapIterationsToColor(fractalMat);
        auto image = renderColorMatToImage(colorMat);

        // renderer
        sf::Texture texture;
        texture.loadFromImage(image);
        sf::Sprite sprite(texture);
        // sprite.setScale(screenWidth / sprite.getLocalBounds().width, screenHeight / sprite.getLocalBounds().height);
        window.draw(sprite);
        window.display();
    }

    return 0;
}

// g++ -c .\src\main.cpp -I ..\SFML-2.5.1\include\ -o out\main.o; g++ .\out\main.o -o out\fractal -L..\SFML-2.5.1\lib\ -lsfml-graphics -lsfml-window -lsfml-system