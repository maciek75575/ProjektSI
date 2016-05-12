#pragma once

#include <SFML/Graphics.hpp>

#include "head.h"

using namespace sf;

class Gui
{
public:
	Font pixel3;
	Text scoreText;
	Text killText;
	RectangleShape hpBackground;
	RectangleShape hpForeground;

	Gui::Gui() {};

	Gui::Gui(String fontName)
	{
		init(fontName);
	}

	void init(String fontName)
	{
		pixel3.loadFromFile(fontName);
		scoreText.setFont(pixel3);
		scoreText.setColor(Color(0, 0, 0, 150));
		killText = scoreText;
		scoreText.setCharacterSize(80);
		killText.setCharacterSize(60);

		hpBackground.setFillColor(Color(0, 0, 0, 100));
		hpBackground.setOutlineThickness(4.);
		hpBackground.setOutlineColor(Color(0, 0, 0, 200));
		hpBackground.setSize(Vector2f(400, 20));
		hpForeground.setFillColor(Color(200, 0, 0, 200));
		hpForeground.setSize(Vector2f(400, 20));
	}

	void update(int hp, int maxHp, unsigned int score, int kill, Vector2f center)
	{
		scoreText.setString(std::to_string(score));
		killText.setString(std::to_string(kill));
		scoreText.setOrigin(scoreText.getLocalBounds().left + scoreText.getLocalBounds().width, scoreText.getLocalBounds().top);
		scoreText.setPosition(center + Vector2f(WIDTH * .5 - 20, HEIGHT * -.5 + 20));
		killText.setOrigin(killText.getLocalBounds().left + killText.getLocalBounds().width, killText.getLocalBounds().top);
		killText.setPosition(center + Vector2f(WIDTH * .5 - 20, HEIGHT * -.5 + 100));

		if (hp>0) hpForeground.setSize(Vector2f(hp * 400 / maxHp, 20));
		else hpForeground.setSize(Vector2f(0, 20));
		hpBackground.setPosition(center + Vector2f(WIDTH * -.5 + 20, HEIGHT * -.5 + 20));
		hpForeground.setPosition(center + Vector2f(WIDTH * -.5 + 20, HEIGHT * -.5 + 20));
	}

	void draw(RenderWindow &window)
	{
		window.draw(scoreText);
		window.draw(killText);
		window.draw(hpBackground);
		window.draw(hpForeground);
	}
};