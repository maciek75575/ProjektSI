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
	Text pauseCashText;
	Text pauseText;
	Text controlsText;
	Text upgradeText;
	Text powerUpgradeText;
	Text numberUpgradeText;

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
		controlsText.setColor(Color(255, 255, 255, 200));
		upgradeText = controlsText;
		controlsText.setCharacterSize(40);
		powerUpgradeText = numberUpgradeText = controlsText;
		controlsText.setString("H - Heal, Cost: 500\nUp, Down, Left, Right - Move\nW - Shoot");
		controlsText.setOrigin(controlsText.getLocalBounds().left + controlsText.getLocalBounds().width*.5f, controlsText.getLocalBounds().top);

		upgradeText.setCharacterSize(50);
		upgradeText.setString("Upgrades");
		upgradeText.setOrigin(upgradeText.getLocalBounds().left + upgradeText.getLocalBounds().width*.5f, upgradeText.getLocalBounds().top);

		hpBackground.setFillColor(Color(0, 0, 0, 100));
		hpBackground.setOutlineThickness(4.);
		hpBackground.setOutlineColor(Color(0, 0, 0, 200));
		hpBackground.setSize(Vector2f(400, 20));
		hpForeground.setFillColor(Color(200, 0, 0, 200));
		hpForeground.setSize(Vector2f(400, 20));

		pauseBackground.setFillColor(Color(0, 0, 0, 200));
		pauseBackground.setSize(Vector2f(WIDTH, HEIGHT));
	}

	void update(int hp, int maxHp, unsigned int score, int kill, int cash, int numLvl, int numCost, int powLvl, int powCost, Vector2f center)
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
		pauseCashText = cashText;
		pauseCashText.setColor(Color(255, 255, 255, 200));

		numberUpgradeText.setString("Missile number:\nLevel: " + std::to_string(numLvl) + "\nMax level: 6\nUpgrade cost: " + std::to_string(numCost) + "\nT - Upgrade");
		powerUpgradeText.setString("Missile damage:\nDamage: " + std::to_string(powLvl) + "\nMax damage: 400\nUpgrade cost: " + std::to_string(powCost) + "\nY - Upgrade");

		if (hp>0) hpForeground.setSize(Vector2f(hp * 400 / maxHp, 20));
		else hpForeground.setSize(Vector2f(0, 20));
		hpBackground.setPosition(center + Vector2f(WIDTH * -.5 + 20, HEIGHT * -.5 + 20));
		hpForeground.setPosition(center + Vector2f(WIDTH * -.5 + 20, HEIGHT * -.5 + 20));

		pauseText.setPosition(center - Vector2f(0, 300));
		controlsText.setPosition(center - Vector2f(0, -150));
		upgradeText.setPosition(center - Vector2f(0, 150));
		powerUpgradeText.setPosition(center - Vector2f(0, 100));
		numberUpgradeText.setPosition(center - Vector2f(500, 100));
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
		window.draw(upgradeText);
		window.draw(pauseCashText);
		window.draw(powerUpgradeText);
		window.draw(numberUpgradeText);
	}
};