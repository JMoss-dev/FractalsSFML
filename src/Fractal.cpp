#include <vector>
#include <cmath>
#include <iostream>

#include <SFML/Graphics.hpp>

std::vector<std::vector<int>> createFractal(int xMin, int xMax, int yMin, int yMax, int setNumIterations = 50)
{
    int numIterations = setNumIterations;
    int rad = 2;
    double resolution = 0.001;

    std::vector<std::vector<int>> fractalMat; // x,y
    int numX = (abs(xMin) + abs(xMax)) / resolution + 1;
    int numY = (abs(yMin) + abs(yMax)) / resolution + 1;
    std::vector<int> temp(numY, 0);
    fractalMat.resize(numX, temp);

    for (double cr = xMin; cr <= xMax; cr += resolution)
    {
        for (double ci = yMin; ci <= yMax; ci += resolution)
        {
            double zr = 0.0;
            double zi = 0.0;

            fractalMat.at((cr - xMin) / resolution).at((ci - yMin) / resolution) = -1;

            for (int i = 0; i < numIterations; i++)
            {
                double zrtemp = zr;
                zr = (zr * zr - zi * zi) + cr;
                zi = (2 * zrtemp * zi) + ci;

                if (zr * zr + zi * zi > rad * rad)
                {

                    fractalMat.at((cr - xMin) / resolution)
                        .at((ci - yMin) / resolution) = i;
                    break;
                }
            }
        }
    }

    return fractalMat;
}

std::vector<std::vector<sf::Color>> mapIterationsToColor(std::vector<std::vector<int>> &fractalMat)
{
    std::vector<std::vector<sf::Color>> colorMat;

    std::vector<sf::Color> temp(fractalMat.at(0).size(), sf::Color::White);
    colorMat.resize(fractalMat.size(), temp);

    std::vector<sf::Color>
        colorMap;
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

    for (int i = 0; i < fractalMat.size(); i++)
    {
        for (int j = 0; j < fractalMat.at(0).size(); j++)
        {
            if (fractalMat.at(i).at(j) == -1)
            {
                colorMat.at(i).at(j) = sf::Color::White;
                continue;
            }
            colorMat.at(i).at(j) = colorMap.at(fractalMat.at(i).at(j) % 16);
        }
    }

    /*for (int i = 0; i < colorMat.size(); i++)
    {
        for (int j = 0; j < colorMat.at(0).size(); j++)
        {
            std::cout << colorMat.at(i).at(j).r << "\n";
        }
    }*/

    return colorMat;
}

sf::Image renderColorMatToImage(std::vector<std::vector<sf::Color>> &colorMat)
{
    sf::Image returnImage;
    returnImage.create(colorMat.size(), colorMat.at(0).size(), sf::Color::White);

    for (int i = 0; i < colorMat.size(); i++)
    {
        for (int j = 0; j < colorMat.at(0).size(); j++)
        {
            returnImage.setPixel(i, j, colorMat.at(i).at(j));
        }
    }

    return returnImage;
}