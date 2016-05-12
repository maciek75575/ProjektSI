#pragma once

#include "head.h"

#include <vector>

#include <SFML/Graphics.hpp>

#include "missle.hpp"

using namespace sf;

class EnemyShip
{
public:
	Sprite shipSprite;
	Texture shipTexture;
	int health, maxHealth;
	int value;
	float coolDown, remainingCool;
	float speed;

	Missile mis;
	std::vector<Missile> missles;

	EnemyShip::EnemyShip() {}

	EnemyShip::EnemyShip(Vector2f pos, String shipTex, String missTex, int hp, unsigned int value, float cool, float speedShip, float rot, float speedMissle, int power)
	{
		init(pos, shipTex, missTex, hp, value, cool, speedShip, rot, speedMissle, power);
	}

	void init(Vector2f pos, String shipTex, String missTex, int hp, unsigned int value, float cool, float speedShip, float rot, float speedMissle, int power)
	{
		shipTexture.loadFromFile(shipTex);
		shipSprite.setTexture(shipTexture);
		shipSprite.setOrigin(Vector2f(shipSprite.getLocalBounds().width*.5f, shipSprite.getLocalBounds().height*.5f));
		shipSprite.setPosition(pos);
		health = maxHealth = hp;
		coolDown = cool;
		this->value = value;
		speed = speedShip;
		remainingCool = 0.f;

		mis.init(missTex, rot, speedMissle, power);
	}

	void control(float delta)
	{
		shipSprite.move(Vector2f(-speed * delta, 0.f));

		if ((remainingCool <= 0.f) && (health>0))
		{
			mis.missleSprite.setPosition(shipSprite.getPosition() + Vector2f(-30.f, 10.f));
			missles.push_back(mis);
			remainingCool = coolDown;
		}
		else remainingCool -= delta;

		int i = 0;
		while (i < missles.size())
		{
			missles[i].move(delta);
			if (missles[i].missleSprite.getPosition().x < -150)
			{
				missles.erase(missles.begin() + i);
				i--;
			}
			i++;
		}
	}

	void draw(RenderWindow &window)
	{
		if (health > 0) window.draw(shipSprite);

		for (int i = 0; i < missles.size(); i++)
		{
			window.draw(missles[i].missleSprite);
		}
	}
};