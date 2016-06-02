#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Missile
{
public:
	Texture missleTexture;
	Sprite missleSprite;
	float speed;
	int power;

	Missile::Missile() {};

	Missile::Missile(String tex, float rot, float sp, int pw)
	{
		init(tex, rot, sp, pw);
	}

	void init(String tex, float rot, float sp, int pw)
	{
		missleTexture.loadFromFile(tex);
		missleSprite.setTexture(missleTexture);
		missleSprite.setOrigin(Vector2f(missleSprite.getLocalBounds().width*.5f, missleSprite.getLocalBounds().height*.5f));
		missleSprite.setRotation(rot);
		speed = sp;
		power = pw;
	}

	void move(float delta)
	{
		float x, y;
		x = y = speed * delta;
		switch (int(missleSprite.getRotation()))
		{
		case 320:
			x = -x;
		case 40:
			y *= -SIN50;
			x *= COS50;
			break;
		case 295:
			x = -x;
		case 65:
			y *= -SIN25;
			x *= COS25;
			break;
		case 270:
			x = -x;
		case 90:
			y = 0;
			break;
		case 245:
			x = -x;
		case 115:
			y *= SIN25;
			x *= COS25;
			break;
		case 220:
			x = -x;
		case 140:
			y *= SIN50;
			x *= COS50;
			break;
		default:
			y = 0;
			if (missleSprite.getRotation() >= 180) x = -x;
			break;
		}

		missleSprite.move(Vector2f(x, y));
	}
};