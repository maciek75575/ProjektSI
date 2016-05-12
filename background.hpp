#pragma once

#include <SFML/Graphics.hpp>

#include "head.h"

using namespace sf;

class Background
{
public:
	Texture backgroundTx;
	Sprite backgroundA;
	Sprite backgroundB;
	RectangleShape menuBg;

	Background::Background() {};

	Background::Background(String bgFile)
	{
		init(bgFile);
	}

	void init(String bgFile)
	{
		backgroundTx.loadFromFile(bgFile);
		backgroundA.setTexture(backgroundTx);
		backgroundB.setTexture(backgroundTx);
		backgroundA.setPosition(Vector2f(int(WIDTH - backgroundTx.getSize().x) * .5f, int(HEIGHT - backgroundTx.getSize().y) *.5f));
		backgroundB.setPosition(Vector2f(int(WIDTH - backgroundTx.getSize().x) * .5f + int(backgroundTx.getSize().x), int(HEIGHT - backgroundTx.getSize().y) *.5f));

		menuBg.setFillColor(Color(0, 0, 0, 200));
		menuBg.setSize(Vector2f(WIDTH, HEIGHT));
	}

	void update(float delta)
	{
		backgroundA.move(-40.f * delta, 0.f);
		backgroundB.move(-40.f * delta, 0.f);
		if (backgroundA.getPosition().x <= int(WIDTH - backgroundTx.getSize().x) * .5f - int(backgroundTx.getSize().x)) backgroundA.setPosition(backgroundB.getPosition() + Vector2f(float(backgroundTx.getSize().x), 0));
		if (backgroundB.getPosition().x <= int(WIDTH - backgroundTx.getSize().x) * .5f - int(backgroundTx.getSize().x)) backgroundB.setPosition(backgroundA.getPosition() + Vector2f(float(backgroundTx.getSize().x), 0));
	}

	void draw(RenderWindow &window)
	{
		window.draw(backgroundA);
		window.draw(backgroundB);
	}

	void drawMenuBg(RenderWindow &window, Vector2f tl = Vector2f(0, 0))
	{
		menuBg.setPosition(tl - Vector2f(WIDTH*.5f, HEIGHT*.5f));
		window.draw(menuBg);
	}
};
