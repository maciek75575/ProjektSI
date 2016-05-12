#pragma once

#include "head.h"

#include <vector>

#include <SFML/Graphics.hpp>

#include "enemyShip.hpp"

using namespace sf;

class EnemyVector
{
public:
	EnemyShip enemy;
	std::vector<EnemyShip> enemies;

	EnemyVector::EnemyVector() {}

	EnemyVector::EnemyVector(Vector2f pos, String shipTex, String missTex, int hp, unsigned int value, float cool, float speedShip, float rot, float speedMissle, int power)
	{
		enemy.init(pos, shipTex, missTex, hp, value, cool, speedShip, rot, speedMissle, power);
		enemies.clear();
	}

	void init(Vector2f pos, String shipTex, String missTex, int hp, unsigned int value, float cool, float speedShip, float rot, float speedMissle, int power)
	{
		enemy.init(pos, shipTex, missTex, hp, value, cool, speedShip, rot, speedMissle, power);
		enemies.clear();
	}

	void addEnemy(Vector2f pos)
	{
		enemy.shipSprite.setPosition(pos);
		enemies.push_back(enemy);
	}

	void control(float delta)
	{
		int i = 0;
		while (i < enemies.size())
		{
			enemies[i].control(delta);
			if (enemies[i].shipSprite.getPosition().x < -150)
			{
				enemies.erase(enemies.begin() + i);
				i--;
			}
			i++;
		}
	}

	void draw(RenderWindow &window)
	{
		for (int i = 0; i < enemies.size(); i++)
		{
			enemies[i].draw(window);
		}
	}
};