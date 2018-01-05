#include "stdafx.h"

int main() {
	bool running = true;

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Spaceship Rescue");
	sf::View view = window.getDefaultView();
	window.setView(view);

	sf::Clock clock;
	sf::Time timer;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float FPS = 60.0f;
	const sf::Time timePerFrame = sf::seconds(1.0f / FPS);

	// The main loop - ends as soon as the window is closed
	while (running == true)
	{
		while (window.isOpen())
		{
			// Event processing
			sf::Event event;
			while (window.pollEvent(event))
			{
				// Request for closing the window
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
			}

			timeSinceLastUpdate += clock.restart();

			window.clear(sf::Color::White);

			// Displays contents of current frame in the window
			if (timeSinceLastUpdate > timePerFrame) {
				//window.setView(view); // viewport

				window.display();

				timeSinceLastUpdate = sf::Time::Zero;
			}

			if (running == false)
			{
				window.close();
			}
		}
	}

	return 0;
}