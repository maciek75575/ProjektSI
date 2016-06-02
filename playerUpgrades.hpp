#pragma once

#include <SFML/Graphics.hpp>

#include "playerShip.hpp"

using namespace sf;

class PlayerUpgrades
{
public:
	short int missleLevel;
	short int misslePower;

	PlayerUpgrades::PlayerUpgrades()
	{
		missleLevel = 1;
		misslePower = 50;
	}

	unsigned int missleLevelUp(unsigned int cash)
	{
		switch (missleLevel)
		{
		case 1:
			if (cash >= 100)
			{
				cash -= 100;
				missleLevel++;
			}
			break;
		case 2:
			if (cash >= 250)
			{
				cash -= 250;
				missleLevel++;
			}
			break;
		case 3:
			if (cash >= 500)
			{
				cash -= 500;
				missleLevel++;
			}
			break;
		case 4:
			if (cash >= 1500)
			{
				cash -= 1500;
				missleLevel++;
			}
			break;
		case 5:
			if (cash >= 2500)
			{
				cash -= 2500;
				missleLevel++;
			}
			break;
		default:break;
		}
		return cash;
	}

	unsigned int misslePowerUp(unsigned int cash)
	{
		switch (misslePower)
		{
		case 50:
			if (cash >= 100)
			{
				cash -= 100;
				misslePower = 75;
			}
			break;
		case 75:
			if (cash >= 200)
			{
				cash -= 200;
				misslePower = 100;
			}
			break;
		case 100:
			if (cash >= 500)
			{
				cash -= 500;
				misslePower = 150;
			}
			break;
		case 150:
			if (cash >= 1000)
			{
				cash -= 1000;
				misslePower = 250;
			}
			break;
		case 250:
			if (cash >= 2500)
			{
				cash -= 2500;
				misslePower = 400;
			}
			break;
		default:break;
		}
		return cash;
	}
};