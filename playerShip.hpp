#pragma once

#include "head.h"

#include <vector>

#include <SFML/Graphics.hpp>

#include "missle.hpp"
#include "enemyVector.hpp"

using namespace sf;

class PlayerShip
{
public:
	Sprite shipSprite;
	Texture shipTexture;
	int health, maxHealth;
	float coolDown, remainingCool;
	float speed;

	Missile mis;
	std::vector<Missile> playerMissles;

	PlayerShip::PlayerShip(Vector2f pos, String shipTex, String missTex, int hp, float cool, float speedShip, float rot, float speedMissle, int power)
	{
		shipTexture.loadFromFile(shipTex);
		shipSprite.setTexture(shipTexture);
		shipSprite.setOrigin(Vector2f(shipSprite.getLocalBounds().width*.5f, shipSprite.getLocalBounds().height*.5f));
		shipSprite.setPosition(pos);
		health = maxHealth = hp;
		coolDown = cool;
		speed = speedShip;
		remainingCool = 0.f;

		mis.init(missTex, rot, speedMissle, power);
	}

	void control(float delta)
	{
		float sXd = speed * delta;
		if ((Keyboard::isKeyPressed(Keyboard::Up)) && (Keyboard::isKeyPressed(Keyboard::Left))) shipSprite.move(Vector2f(-sXd * SIN45, -sXd * SIN45));
		else if ((Keyboard::isKeyPressed(Keyboard::Down)) && (Keyboard::isKeyPressed(Keyboard::Left))) shipSprite.move(Vector2f(-sXd * SIN45, sXd * SIN45));
		else if ((Keyboard::isKeyPressed(Keyboard::Up)) && (Keyboard::isKeyPressed(Keyboard::Right))) shipSprite.move(Vector2f(sXd * SIN45, -sXd * SIN45));
		else if ((Keyboard::isKeyPressed(Keyboard::Down)) && (Keyboard::isKeyPressed(Keyboard::Right))) shipSprite.move(Vector2f(sXd * SIN45, sXd * SIN45));
		else if (Keyboard::isKeyPressed(Keyboard::Up)) shipSprite.move(Vector2f(0.f, -sXd));
		else if (Keyboard::isKeyPressed(Keyboard::Down)) shipSprite.move(Vector2f(0.f, sXd));
		else if (Keyboard::isKeyPressed(Keyboard::Left)) shipSprite.move(Vector2f(-sXd, 0.f));
		else if (Keyboard::isKeyPressed(Keyboard::Right)) shipSprite.move(Vector2f(sXd, 0.f));

		if (shipSprite.getPosition().x < 50.f) shipSprite.setPosition(Vector2f(50.f, shipSprite.getPosition().y));
		if (shipSprite.getPosition().x > WIDTH - 50.f) shipSprite.setPosition(Vector2f(WIDTH - 50.f, shipSprite.getPosition().y));
		if (shipSprite.getPosition().y < 60.f) shipSprite.setPosition(Vector2f(shipSprite.getPosition().x, 60.f));
		if (shipSprite.getPosition().y > HEIGHT - 60.f) shipSprite.setPosition(Vector2f(shipSprite.getPosition().x, HEIGHT - 60.f));

		if ((Keyboard::isKeyPressed(Keyboard::W)) && (remainingCool <= 0.f))
		{
			mis.missleSprite.setPosition(shipSprite.getPosition() + Vector2f(30.f, 10.f));
			playerMissles.push_back(mis);
			remainingCool = coolDown;
		}

		if (remainingCool > 0.f)
		{
			remainingCool -= delta;
		}

		int i = 0;
		while (i < playerMissles.size())
		{
			playerMissles[i].move(delta, false);
			if (playerMissles[i].missleSprite.getPosition().x > WIDTH + 150)
			{
				playerMissles.erase(playerMissles.begin() + i);
				i--;
			}
			i++;
		}
	}

	void collision(EnemyVector &en)
	{
		int i = 0;
		while (i < en.enemies.size())
		{
			FloatRect enemy = en.enemies[i].shipSprite.getGlobalBounds();
			FloatRect player = shipSprite.getGlobalBounds();
			std::vector<Missile> enemyMissles = en.enemies[i].missles;
			
			if ((enemy.left + enemy.width > player.left)
				&& (enemy.left < player.left + player.width)
				&& (enemy.top < player.top + player.height)
				&& (enemy.top + enemy.height > player.top)
				&& (en.enemies[i].health > 0))
			{
				health -= en.enemies[i].health;
				en.enemies[i].health = 0;
			}
			else
			{
				int j = 0;
				if (en.enemies[i].health > 0) while (j < playerMissles.size())
				{
					Vector2f misPos = playerMissles[j].missleSprite.getOrigin() + Vector2f(playerMissles[j].missleSprite.getGlobalBounds().left, playerMissles[j].missleSprite.getGlobalBounds().top);
					if ((enemy.left<misPos.x) && (enemy.left + enemy.width>misPos.x) && (enemy.top<misPos.y) && (enemy.top + enemy.height>misPos.y))
					{
						en.enemies[i].health -= playerMissles[j].power;
						playerMissles.erase(playerMissles.begin() + j);
						j--;
					}
					j++;
				}
				j = 0;
				while (j < enemyMissles.size())
				{
					Vector2f misPos = enemyMissles[j].missleSprite.getOrigin() + Vector2f(enemyMissles[j].missleSprite.getGlobalBounds().left, enemyMissles[j].missleSprite.getGlobalBounds().top);
					if ((player.left<misPos.x) && (player.left + player.width>misPos.x) && (player.top<misPos.y) && (player.top + player.height>misPos.y))
					{
						health -= enemyMissles[j].power;
						enemyMissles.erase(enemyMissles.begin() + j);
						j--;
					}
					j++;
				}
				en.enemies[i].missles = enemyMissles;

				i++;
				std::cout<<health<<std::endl;
			}
		}
	}

	void draw(RenderWindow &window)
	{
		window.draw(shipSprite);

		for (int i = 0; i < playerMissles.size(); i++)
		{
			window.draw(playerMissles[i].missleSprite);
		}
	}
};