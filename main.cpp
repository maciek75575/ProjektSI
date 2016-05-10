#include "head.h"

#include <iostream>
#include <vector>

#include <stdlib.h>
#include <time.h>

#include <SFML/Graphics.hpp>

#include "playerShip.hpp"
#include "enemyVector.hpp"
#include "missle.hpp"

using namespace sf;

int main()
{
	srand(time(NULL));

	RenderWindow window(VideoMode(WIDTH, HEIGHT), "", Style::Fullscreen);
	window.setFramerateLimit(120);

	View view(FloatRect(0.f, 0.f, WIDTH, HEIGHT));
	window.setView(view);

	Texture backgroundTx;

	PlayerShip player01(Vector2f(WIDTH * .5f, HEIGHT * .5f), "textures/ship01.png", "textures/missle01.png", 1000, .3f, 300.f, 90.f, 600.f, 50);

	EnemyVector enemies01(Vector2f(1300.f, 360.f), "textures/ship02.png", "textures/missle02.png", 100, 1.f, 200.f, -90.f, 450.f, 50);

	backgroundTx.loadFromFile("textures/background02.png");
	Sprite backgroundA(backgroundTx);
	Sprite backgroundB(backgroundTx);
	backgroundA.setPosition(Vector2f(int(WIDTH - backgroundTx.getSize().x) * .5f, int(HEIGHT - backgroundTx.getSize().y) *.5f));
	backgroundB.setPosition(Vector2f(int(WIDTH - backgroundTx.getSize().x) * .5f + int(backgroundTx.getSize().x), int(HEIGHT - backgroundTx.getSize().y) *.5f));

	Clock clock;
	float deltaTime = .01f;

	//----------
	float wait = 2.f;
	//----------

	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			if ((event.type == Event::Closed) || (event.key.code == Keyboard::Escape))
			{
				window.close();
			}
		}

		window.clear();

		backgroundA.move(-40.f * deltaTime, 0.f);
		backgroundB.move(-40.f * deltaTime, 0.f);
		if (backgroundA.getPosition().x <= int(WIDTH - backgroundTx.getSize().x) * .5f - int(backgroundTx.getSize().x)) backgroundA.setPosition(backgroundB.getPosition() + Vector2f(float(backgroundTx.getSize().x), 0));
		if (backgroundB.getPosition().x <= int(WIDTH - backgroundTx.getSize().x) * .5f - int(backgroundTx.getSize().x)) backgroundB.setPosition(backgroundA.getPosition() + Vector2f(float(backgroundTx.getSize().x), 0));
		window.draw(backgroundA);
		window.draw(backgroundB);

		player01.control(deltaTime);
		if (wait > 0.f) wait -= deltaTime;
		else
		{
			enemies01.addEnemy(Vector2f(WIDTH + 150.f, 100.f + (rand() % (HEIGHT - 200))));
			wait = 2.f + (rand() % 20) * .1f;
		}
		enemies01.control(deltaTime);

		player01.collision(enemies01);

		player01.draw(window);
		enemies01.draw(window);

		view.setCenter(WIDTH * .5f + (player01.shipSprite.getPosition().x - WIDTH * .5f) * .15f, HEIGHT * .5f + (player01.shipSprite.getPosition().y - HEIGHT * .5f) * .15f);
		window.setView(view);
		window.display();

		deltaTime = clock.restart().asSeconds();
	}

	return 0;
}