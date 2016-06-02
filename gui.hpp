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
	Text cashText;
	Text pauseText;
	Text controlsText;

	RectangleShape pauseBackground;

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
		killText = cashText = scoreText;
		scoreText.setCharacterSize(80);
		killText.setCharacterSize(60);
		cashText.setCharacterSize(60);

		pauseText.setFont(pixel3);
		pauseText.setCharacterSize(150);
		pauseText.setColor(Color(255, 255, 255, 200));
		pauseText.setString("GAME PAUSED");
		pauseText.setOrigin(pauseText.getLocalBounds().left + pauseText.getLocalBounds().width*.5f, pauseText.getLocalBounds().top);

		controlsText.setFont(pixel3);
		controlsText.setCharacterSize(50);
		controlsText.setColor(Color(255, 255, 255, 200));
		controlsText.setString("Up, Down, Left, Right - Move\n W - Shoot\n  T - Upgrade missile number\n   Y - Upgrade missile power\n    H - Heal");
		controlsText.setOrigin(pauseText.getLocalBounds().left + pauseText.getLocalBounds().width*.5f, pauseText.getLocalBounds().top);

		hpBackground.setFillColor(Color(0, 0, 0, 100));
		hpBackground.setOutlineThickness(4.);
		hpBackground.setOutlineColor(Color(0, 0, 0, 200));
		hpBackground.setSize(Vector2f(400, 20));
		hpForeground.setFillColor(Color(200, 0, 0, 200));
		hpForeground.setSize(Vector2f(400, 20));

		pauseBackground.setFillColor(Color(0, 0, 0, 200));
		pauseBackground.setSize(Vector2f(WIDTH, HEIGHT));
	}

	void update(int hp, int maxHp, unsigned int score, int kill, int cash, Vector2f center)
	{
		scoreText.setString(std::to_string(score));
		killText.setString(std::to_string(kill));
		cashText.setString("CASH: " + std::to_string(cash) + "$");
		scoreText.setOrigin(scoreText.getLocalBounds().left + scoreText.getLocalBounds().width, scoreText.getLocalBounds().top);
		scoreText.setPosition(center + Vector2f(WIDTH * .5 - 20, HEIGHT * -.5 + 20));
		killText.setOrigin(killText.getLocalBounds().left + killText.getLocalBounds().width, killText.getLocalBounds().top);
		killText.setPosition(center + Vector2f(WIDTH * .5 - 20, HEIGHT * -.5 + 100));
		cashText.setOrigin(cashText.getLocalBounds().left, cashText.getLocalBounds().top);
		cashText.setPosition(center + Vector2f(WIDTH * -.5 + 20, HEIGHT * .5 - 60));

		if (hp>0) hpForeground.setSize(Vector2f(hp * 400 / maxHp, 20));
		else hpForeground.setSize(Vector2f(0, 20));
		hpBackground.setPosition(center + Vector2f(WIDTH * -.5 + 20, HEIGHT * -.5 + 20));
		hpForeground.setPosition(center + Vector2f(WIDTH * -.5 + 20, HEIGHT * -.5 + 20));

		pauseText.setPosition(center - Vector2f(0, 200));
		controlsText.setPosition(center - Vector2f(-150, 20));
		pauseBackground.setPosition(center - Vector2f(WIDTH*.5f, HEIGHT*.5f));
	}

	void draw(RenderWindow &window)
	{
		window.draw(scoreText);
		window.draw(killText);
		window.draw(cashText);
		window.draw(hpBackground);
		window.draw(hpForeground);
	}

	void drawPause(RenderWindow &window)
	{
		window.draw(pauseBackground);
		window.draw(pauseText);
		window.draw(controlsText);
	}
};