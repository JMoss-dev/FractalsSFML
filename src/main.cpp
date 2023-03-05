#include <iostream>
#include <cmath>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

bool isPartOfFractal(float cr, float ci, int numIterations, int rad);
void setColorForIndex(int index);
sf::Color color;

float startzr = 0;

int main()
{
    int desktopHeight = sf::VideoMode::getDesktopMode().height;
    float screenWidth = 2 * desktopHeight / 3;
    float screenHeight = 2 * desktopHeight / 3;
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Fractals");

    int numPixels = 1000; // px per width and height

    sf::RectangleShape pixel(sf::Vector2f(1, 1));
    int windowHeight = window.getSize().y;
    pixel.setSize(sf::Vector2f(windowHeight / numPixels, windowHeight / numPixels));
    pixel.setPosition(sf::Vector2f(0, 0));
    pixel.setOrigin(pixel.getSize().x / 2, pixel.getSize().y / 2);

    // performance
    sf::Image image;
    image.create(screenWidth, screenHeight, sf::Color::White);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear
        window.clear();
        // draw
        for (int i = 0; i < screenWidth; i = i + screenWidth / numPixels)
        {
            for (int j = 0; j < screenWidth; j = j + screenWidth / numPixels)
            {
                if (isPartOfFractal(4 * i / screenWidth - 2, 4 * j / screenWidth - 2, 100, 2))
                {
                    // pixel.setPosition(i, j);
                    // pixel.setFillColor(color);
                    // window.draw(pixel);
                }
                // pixel.setFillColor(color);
                // pixel.setPosition(i, j);
                // window.draw(pixel);
                image.setPixel(i, j, color);
            }
            // std::cout << "column " << i << " finished\n";
        }
        // draw
        //  display
        sf::Texture texture;
        texture.loadFromImage(image);
        sf::Sprite sprite(texture);
        window.draw(sprite);
        window.display();
    }

    return 0;
}

bool isPartOfFractal(float cr, float ci, int numIterations, int rad)
{
    // do until numIterations is reached z(n+1) = z(n)^2+c with z(0) = 0
    float zr = startzr;
    float zi = 0;

    for (int i = 0; i < numIterations; i++)
    {
        // calculate next number
        float zrtemp = zr;
        zr = (zr * zr - zi * zi) + cr;
        zi = (2 * zrtemp * zi) + ci;

        // check condition if further away from 0,0 than rad
        if (zr * zr + zi * zi > rad * rad)
        {
            setColorForIndex(i);
            return false;
        }
    }

    color = sf::Color(255, 255, 255);
    return true;
    /*if (cr == 0 || ci == 0)
    {
        return true;
    }

    return false;*/
}

void setColorForIndex(int index)
{
    int i = index % 16;
    std::vector<sf::Color> colorMap;
    colorMap.push_back(sf::Color(66, 30, 15));
    colorMap.push_back(sf::Color(25, 7, 26));
    colorMap.push_back(sf::Color(9, 1, 47));
    colorMap.push_back(sf::Color(4, 4, 73));
    colorMap.push_back(sf::Color(0, 7, 100));
    colorMap.push_back(sf::Color(12, 44, 138));
    colorMap.push_back(sf::Color(24, 82, 177));
    colorMap.push_back(sf::Color(57, 125, 209));
    colorMap.push_back(sf::Color(134, 181, 229));
    colorMap.push_back(sf::Color(211, 236, 248));
    colorMap.push_back(sf::Color(241, 233, 191));
    colorMap.push_back(sf::Color(248, 201, 95));
    colorMap.push_back(sf::Color(255, 170, 0));
    colorMap.push_back(sf::Color(204, 128, 0));
    colorMap.push_back(sf::Color(153, 87, 0));
    colorMap.push_back(sf::Color(106, 52, 3));

    color = colorMap.at(i);
}

// g++ -c .\src\main.cpp -I..\SFML-2.5.1\include
// g++ main.o -o sfml-app -L..\SFML-2.5.1\lib\ -lsfml-graphics -lsfml-window -lsfml-system
// g++ -c .\src\main.cpp -I..\SFML-2.5.1\include -o out\main.o; g++ out\main.o -o out\sfml-app -L..\SFML-2.5.1\lib\ -lsfml-graphics -lsfml-window -lsfml-system; .\out\sfml-app.exe