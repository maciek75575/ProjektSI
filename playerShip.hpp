#pragma once

#include "head.h"

#include <vector>

#include <SFML/Graphics.hpp>

#include "missle.hpp"
#include "playerUpgrades.hpp"
#include "enemyVector.hpp"

using namespace sf;

class PlayerShip
{
public:
	Sprite shipSprite;
	Texture shipTexture;
	int health, maxHealth, killCount;
	unsigned int score, cash;
	float coolDown, remainingCool;
	float speed;

	PlayerUpgrades upgrades;

	Missile mis;
	std::vector<Missile> playerMissles;

	PlayerShip::PlayerShip() {};

	PlayerShip::PlayerShip(Vector2f pos, String shipTex, String missTex, int hp, float cool, float speedShip, float rot, float speedMissle, int power)
	{
		init(pos, shipTex, missTex, hp, cool, speedShip, rot, speedMissle, power);
	}

	void init(Vector2f pos, String shipTex, String missTex, int hp, float cool, float speedShip, float rot, float speedMissle, int power)
	{
		shipTexture.loadFromFile(shipTex);
		shipSprite.setTexture(shipTexture);
		shipSprite.setOrigin(Vector2f(shipSprite.getLocalBounds().width*.5f, shipSprite.getLocalBounds().height*.5f));
		shipSprite.setPosition(pos);
		health = maxHealth = hp;
		coolDown = cool;
		speed = speedShip;
		remainingCool = 0.f;
		score = 0;
		killCount = 0;
		cash = 0;
		playerMissles.clear();

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
			mis.power = upgrades.misslePower;
			switch (upgrades.missleLevel)
			{
			case 3:
				mis.missleSprite.setPosition(shipSprite.getPosition() + Vector2f(30.f, 10.f));
				mis.missleSprite.setRotation(65);
				playerMissles.push_back(mis);
				mis.missleSprite.setRotation(115);
				playerMissles.push_back(mis);
			case 1:
				mis.missleSprite.setPosition(shipSprite.getPosition() + Vector2f(30.f, 10.f));
				mis.missleSprite.setRotation(90);
				playerMissles.push_back(mis);
				remainingCool = coolDown;
				break;
			case 6:
				mis.missleSprite.setPosition(shipSprite.getPosition() + Vector2f(25.f, -7.f));
				mis.missleSprite.setRotation(40);
				playerMissles.push_back(mis);
				mis.missleSprite.setPosition(shipSprite.getPosition() + Vector2f(25.f, 27.f));
				mis.missleSprite.setRotation(140);
				playerMissles.push_back(mis);
			case 5:
				mis.missleSprite.setPosition(shipSprite.getPosition() + Vector2f(25.f, -7.f));
				mis.missleSprite.setRotation(65);
				playerMissles.push_back(mis);
				mis.missleSprite.setPosition(shipSprite.getPosition() + Vector2f(25.f, 27.f));
				mis.missleSprite.setRotation(115);
				playerMissles.push_back(mis);
			case 4:
				mis.missleSprite.setPosition(shipSprite.getPosition() + Vector2f(30.f, 4.f));
				mis.missleSprite.setRotation(65);
				playerMissles.push_back(mis);
				mis.missleSprite.setPosition(shipSprite.getPosition() + Vector2f(30.f, 16.f));
				mis.missleSprite.setRotation(115);
				playerMissles.push_back(mis);
			case 2:
				mis.missleSprite.setPosition(shipSprite.getPosition() + Vector2f(30.f, 4.f));
				mis.missleSprite.setRotation(90);
				playerMissles.push_back(mis);
				mis.missleSprite.setPosition(shipSprite.getPosition() + Vector2f(30.f, 16.f));
				playerMissles.push_back(mis);
				remainingCool = coolDown;
				break;
			}
		}

		if (remainingCool > 0.f)
		{
			remainingCool -= delta;
		}

		int i = 0;
		while (i < playerMissles.size())
		{
			playerMissles[i].move(delta);
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
				killCount++;
				if (score < en.enemies[i].value) score = 0;
				else score -= en.enemies[i].value;
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
						if (en.enemies[i].health <= 0)
						{
							killCount++;
							cash += en.enemies[i].value / 10;
							score += en.enemies[i].value;
						}
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