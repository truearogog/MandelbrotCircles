#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

#define PI 3.14159265358979323846

const int n = 300;
typedef short unsigned int byte;
const int winSize = 700;

sf::Vector2f* points = new sf::Vector2f[n];
sf::CircleShape* pointShapes = new sf::CircleShape[n];
sf::VertexArray* lines = new sf::VertexArray[n];

void updateVertexArray(uint16_t k)
{
	for (uint16_t i = 0; i < n; ++i)
	{
		lines[i][1] = points[(i * k) % n];
	}
	std::cout << k << std::endl;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(winSize, winSize), "MandelbrotCircles");

	float angle = 360.f/n;
	for (uint16_t i = 0; i < n; ++i)
	{
		float x = (float)((winSize/2-20) * cos(angle * (i+1) * PI / 180)) + (winSize/2);
		float y = (float)((winSize/2-20) * sin(angle * (i+1) * PI / 180)) + (winSize/2);
		points[i] = sf::Vector2f(x, y);
		lines[i] = sf::VertexArray(sf::LinesStrip, 2);
		lines[i][0] = points[i];
		pointShapes[i] = sf::CircleShape(3);
		pointShapes[i].setOrigin(1.5, 1.5);
		pointShapes[i].setFillColor(sf::Color::Red);
		pointShapes[i].setPosition(points[i]);
	}

	uint16_t k = 2;
	updateVertexArray(k);

	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Up)
				{
					++k;
					updateVertexArray(k);
				}

				if (event.key.code == sf::Keyboard::Down)
				{
					--k;
					updateVertexArray(k);
				}
			}
		}

		/*
		if (clock.getElapsedTime().asMilliseconds() >= sf::milliseconds(1000).asMilliseconds())
		{
			++k;
			updateVertexArray(k);
			clock.restart();
		}
		*/

		window.clear();
		for (uint16_t i = 0; i < n; ++i)
		{
			//draw the point
			window.draw(pointShapes[i]);
			window.draw(lines[i]);
		}
		window.display();
	}

	return 0;
}