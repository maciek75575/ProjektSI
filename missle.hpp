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

	void move(float delta, bool enemy=true)
	{
		if (enemy) missleSprite.move(Vector2f(-speed * delta, 0.f));
		else missleSprite.move(Vector2f(speed * delta, 0.f));
	}
};