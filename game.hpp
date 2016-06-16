#pragma once

#include "head.h"

#include <iostream>
#include <vector>

#include <stdlib.h>
#include <time.h>

#include <SFML/Graphics.hpp>

#include "playerShip.hpp"
#include "enemyVector.hpp"
#include "missle.hpp"
#include "gui.hpp"
#include "background.hpp"

using namespace sf;

class Game
{
public:
	RenderWindow *window;
	Gui myGui;
	View view;
	PlayerShip player01;
	EnemyVector enemies01;
	EnemyVector enemies02;
	Background bg;
	Clock clock;

	Font pixel3;
	Text gameOverText;

	Text contin;
	Text newGame;
	Text exit;

	int menuPos;

	//----------
	float wait;
	float wait2;
	//----------

	Game::Game()
	{
		window = new RenderWindow(VideoMode(WIDTH, HEIGHT), "", Style::Fullscreen);
		window->setFramerateLimit(120);

		myGui.init("fonts/LLPIXEL3.ttf");

		view.setSize(WIDTH, HEIGHT);

		bg.init("textures/background02.png");

		init();

		pixel3.loadFromFile("fonts/LLPIXEL3.ttf");
		gameOverText.setFont(pixel3);
		gameOverText.setCharacterSize(150);
		gameOverText.setColor(Color(0, 0, 0, 200));
		gameOverText.setString("GAME OVER");
		gameOverText.setOrigin(gameOverText.getLocalBounds().left + gameOverText.getLocalBounds().width*.5f, gameOverText.getLocalBounds().top);

		contin.setFont(pixel3);
		contin.setColor(Color(250, 250, 250, 250));
		contin.setCharacterSize(80);
		exit = newGame = contin;

		contin.setString("Continue");
		contin.setOrigin(contin.getLocalBounds().left + contin.getLocalBounds().width*.5f, contin.getLocalBounds().top + contin.getLocalBounds().height*.5f);
		newGame.setString("New game");
		newGame.setOrigin(newGame.getLocalBounds().left + newGame.getLocalBounds().width*.5f, newGame.getLocalBounds().top + newGame.getLocalBounds().height*.5f);
		exit.setString("Exit");
		exit.setOrigin(exit.getLocalBounds().left + exit.getLocalBounds().width*.5f, exit.getLocalBounds().top + exit.getLocalBounds().height*.5f);

		menuPos = 2;

		srand(time(NULL));
	}

	void init()
	{
		player01.init(Vector2f(WIDTH * .5f, HEIGHT * .5f), "textures/ship01.png", "textures/missle01.png", 400, .3f, 300.f, 90.f, 600.f, 50);
		enemies01.init(Vector2f(1300.f, 360.f), "textures/ship02.png", "textures/missle02.png", 100, 100, 1.f, 200.f, -90.f, 450.f, 50);
		enemies02.init(Vector2f(1300.f, 360.f), "textures/ship03.png", "textures/missle03.png", 150, 200, 1.5f, 150.f, -90.f, 350.f, 150);
	}

	void play()
	{
		bool pauseFlag = false;
		bool menuFlag = true;
		bool overFlag = false;
		bool tFlag = false;
		bool yFlag = false;
		bool hFlag = false;
		int menuRet = 0;
		float deltaTime = .01f;
		while (window->isOpen())
		{
			Event event;
			while (window->pollEvent(event))
			{
				if (event.type == Event::Closed)
				{
					window->close();
				}
			}
			
			if ((Keyboard::isKeyPressed(Keyboard::P)) && (!menuFlag) && (!overFlag))
			{
				float tmp = clock.getElapsedTime().asSeconds();
				pauseFlag = !pauseFlag;
				while (Keyboard::isKeyPressed(Keyboard::P));
				deltaTime = clock.restart().asSeconds();
				deltaTime = tmp;
			}
			if ((Keyboard::isKeyPressed(Keyboard::Escape)) || (menuRet == 1))
			{
				float tmp = clock.getElapsedTime().asSeconds();
				menuFlag = !menuFlag;
				menuRet = 0;
				pauseFlag = false;
				if (overFlag)
				{
					overFlag = false;
					init();
				}
				while (Keyboard::isKeyPressed(Keyboard::Escape));
				deltaTime = clock.restart().asSeconds();
				deltaTime = tmp;
			}
			if ((Keyboard::isKeyPressed(Keyboard::Space)) && (overFlag))
			{
				float tmp = clock.getElapsedTime().asSeconds();
				overFlag = false;
				init();
				while (Keyboard::isKeyPressed(Keyboard::Space));
				deltaTime = clock.restart().asSeconds();
				deltaTime = tmp;
			}

			if ((Keyboard::isKeyPressed(Keyboard::T)) && pauseFlag)
			{
				if (!tFlag)
				{
					tFlag = true;
					player01.cash = player01.upgrades.missleLevelUp(player01.cash);
				}
			}
			else tFlag = false;

			if ((Keyboard::isKeyPressed(Keyboard::Y)) && pauseFlag)
			{
				if (!yFlag)
				{
					yFlag = true;
					player01.cash = player01.upgrades.misslePowerUp(player01.cash);
				}
			}
			else yFlag = false;

			if ((Keyboard::isKeyPressed(Keyboard::H)) && pauseFlag)
			{
				if (!hFlag)
				{
					hFlag = true;
					if ((player01.cash >= 100) && (player01.health < player01.maxHealth))
					{
						player01.cash -= 100;
						player01.health += 200;
						if (player01.health > player01.maxHealth) player01.health = player01.maxHealth;
					}
				}
			}
			else hFlag = false;

			//--
			if ((Keyboard::isKeyPressed(Keyboard::B)) && (Keyboard::isKeyPressed(Keyboard::M))) player01.cash+=10;
			//--

			if (menuRet == 2)
			{
				init();
				pauseFlag = false;
				menuFlag = false;
				menuRet = 0;
			}


			if (pauseFlag) pause();
			else if (menuFlag) menuRet = menu();
			else if (overFlag) gameOver(deltaTime);
			else game(deltaTime);

			if (player01.health <= 0) overFlag = true;
			else overFlag = false;

			deltaTime = clock.restart().asSeconds();
		}
	}

	void game(float deltaTime)
	{
		window->clear();

		bg.update(deltaTime);
		bg.draw(*window);

		player01.control(deltaTime);
		if (wait > 0.f) wait -= deltaTime;
		else
		{
			enemies01.addEnemy(Vector2f(WIDTH + 150.f, 100.f + (rand() % (HEIGHT - 200))));
			wait = 1.5f + (rand() % 20) * .1f;
		}
		enemies01.control(deltaTime);

		if (player01.killCount >= 20)
		{
			if (wait2 > 0.f) wait2 -= deltaTime;
			else
			{
				enemies02.addEnemy(Vector2f(WIDTH + 150.f, 100.f + (rand() % (HEIGHT - 200))));
				wait2 = 2.f + (rand() % 40) * .1f;
			}
			enemies02.control(deltaTime);
		}

		player01.collision(enemies01);
		player01.collision(enemies02);

		player01.draw(*window);
		enemies01.draw(*window);
		enemies02.draw(*window);

		Vector2f viewCenter(WIDTH * .5f + (player01.shipSprite.getPosition().x - WIDTH * .5f) * .15f, HEIGHT * .5f + (player01.shipSprite.getPosition().y - HEIGHT * .5f) * .15f);

		myGui.update(player01.health, player01.maxHealth, player01.score, player01.killCount, player01.cash, player01.upgrades.missleLevel, player01.upgrades.missleLevelCosts[player01.upgrades.missleLevel-1], player01.upgrades.misslePower, player01.upgrades.misslePowerCosts[player01.upgrades.misslePowerLvl-1], viewCenter);
		myGui.draw(*window);

		view.setCenter(viewCenter);
		window->setView(view);
		window->display();
	}

	void gameOver(float deltaTime)
	{
		window->clear();

		bg.update(deltaTime);
		bg.draw(*window);
		
		if (wait > 0.f) wait -= deltaTime;
		else
		{
			enemies01.addEnemy(Vector2f(WIDTH + 150.f, 100.f + (rand() % (HEIGHT - 200))));
			wait = 1.5f + (rand() % 20) * .1f;
		}

		if (wait2 > 0.f) wait2 -= deltaTime;
		else
		{
			enemies02.addEnemy(Vector2f(WIDTH + 150.f, 100.f + (rand() % (HEIGHT - 200))));
			wait2 = 2.f + (rand() % 40) * .1f;
		}

		enemies01.control(deltaTime);
		enemies02.control(deltaTime);

		player01.collision(enemies01);
		player01.collision(enemies02);

		enemies01.draw(*window);
		enemies02.draw(*window);

		Vector2f viewCenter(WIDTH * .5f + (player01.shipSprite.getPosition().x - WIDTH * .5f) * .15f, HEIGHT * .5f + (player01.shipSprite.getPosition().y - HEIGHT * .5f) * .15f);

		myGui.update(player01.health, player01.maxHealth, player01.score, player01.killCount, player01.cash, player01.upgrades.missleLevel, player01.upgrades.missleLevelCosts[player01.upgrades.missleLevel - 1], player01.upgrades.misslePower, player01.upgrades.misslePowerCosts[player01.upgrades.misslePowerLvl-1], viewCenter);
		myGui.draw(*window);

		gameOverText.setPosition(viewCenter - Vector2f(0, 70));
		window->draw(gameOverText);

		view.setCenter(viewCenter);
		window->setView(view);
		window->display();
	}

	void pause()
	{
		window->clear();

		Vector2f viewCenter(WIDTH * .5f + (player01.shipSprite.getPosition().x - WIDTH * .5f) * .15f, HEIGHT * .5f + (player01.shipSprite.getPosition().y - HEIGHT * .5f) * .15f);

		bg.draw(*window);
		player01.draw(*window);
		enemies01.draw(*window);
		enemies02.draw(*window);

		myGui.update(player01.health, player01.maxHealth, player01.score, player01.killCount, player01.cash, player01.upgrades.missleLevel, player01.upgrades.missleLevelCosts[player01.upgrades.missleLevel - 1], player01.upgrades.misslePower, player01.upgrades.misslePowerCosts[player01.upgrades.misslePowerLvl-1], viewCenter);
		myGui.draw(*window);
		myGui.drawPause(*window);

		view.setCenter(viewCenter);
		window->setView(view);
		window->display();
	}

	int menu()
	{
		window->clear();

		Vector2f viewCenter(WIDTH * .5f + (player01.shipSprite.getPosition().x - WIDTH * .5f) * .15f, HEIGHT * .5f + (player01.shipSprite.getPosition().y - HEIGHT * .5f) * .15f);

		bg.draw(*window);
		player01.draw(*window);
		enemies01.draw(*window);
		enemies02.draw(*window);

		myGui.update(player01.health, player01.maxHealth, player01.score, player01.killCount, player01.cash, player01.upgrades.missleLevel, player01.upgrades.missleLevelCosts[player01.upgrades.missleLevel - 1], player01.upgrades.misslePower, player01.upgrades.misslePowerCosts[player01.upgrades.misslePowerLvl-1], viewCenter);
		myGui.draw(*window);

		bg.drawMenuBg(*window, viewCenter);

		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			menuPos--;
			if (menuPos < 1) menuPos = 3;
			while (Keyboard::isKeyPressed(Keyboard::Up));
		}

		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			menuPos++;
			if (menuPos > 3) menuPos = 1;
			while (Keyboard::isKeyPressed(Keyboard::Down));
		}

		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			switch (menuPos)
			{
			case 1:
				return 1;
			case 2:
				return 2;
			case 3:
				window->close();
			}
		}

		switch (menuPos)
		{
		case 1:
			contin.setCharacterSize(100);
			newGame.setCharacterSize(80);
			exit.setCharacterSize(80);
			contin.setColor(Color(250, 250, 250, 250));
			newGame.setColor(Color(250, 250, 250, 200));
			exit.setColor(Color(250, 250, 250, 200));
			contin.setOrigin(contin.getLocalBounds().left + contin.getLocalBounds().width*.5f, contin.getLocalBounds().top + contin.getLocalBounds().height*.5f);
			newGame.setOrigin(newGame.getLocalBounds().left + newGame.getLocalBounds().width*.5f, newGame.getLocalBounds().top + newGame.getLocalBounds().height*.5f);
			exit.setOrigin(exit.getLocalBounds().left + exit.getLocalBounds().width*.5f, exit.getLocalBounds().top + exit.getLocalBounds().height*.5f);
			break;
		case 2:
			contin.setCharacterSize(80);
			newGame.setCharacterSize(100);
			exit.setCharacterSize(80);
			contin.setColor(Color(250, 250, 250, 200));
			newGame.setColor(Color(250, 250, 250, 250));
			exit.setColor(Color(250, 250, 250, 200));
			contin.setOrigin(contin.getLocalBounds().left + contin.getLocalBounds().width*.5f, contin.getLocalBounds().top + contin.getLocalBounds().height*.5f);
			newGame.setOrigin(newGame.getLocalBounds().left + newGame.getLocalBounds().width*.5f, newGame.getLocalBounds().top + newGame.getLocalBounds().height*.5f);
			exit.setOrigin(exit.getLocalBounds().left + exit.getLocalBounds().width*.5f, exit.getLocalBounds().top + exit.getLocalBounds().height*.5f);
			break;
		case 3:
			contin.setCharacterSize(80);
			newGame.setCharacterSize(80);
			exit.setCharacterSize(100);
			contin.setColor(Color(250, 250, 250, 200));
			newGame.setColor(Color(250, 250, 250, 200));
			exit.setColor(Color(250, 250, 250, 250));
			contin.setOrigin(contin.getLocalBounds().left + contin.getLocalBounds().width*.5f, contin.getLocalBounds().top + contin.getLocalBounds().height*.5f);
			newGame.setOrigin(newGame.getLocalBounds().left + newGame.getLocalBounds().width*.5f, newGame.getLocalBounds().top + newGame.getLocalBounds().height*.5f);
			exit.setOrigin(exit.getLocalBounds().left + exit.getLocalBounds().width*.5f, exit.getLocalBounds().top + exit.getLocalBounds().height*.5f);
			break;
		}

		contin.setPosition(viewCenter + Vector2f(0, -100));
		newGame.setPosition(viewCenter + Vector2f(0, 0));
		exit.setPosition(viewCenter + Vector2f(0, 100));

		window->draw(contin);
		window->draw(newGame);
		window->draw(exit);

		view.setCenter(viewCenter);
		window->setView(view);
		window->display();
		return 0;
	}
};