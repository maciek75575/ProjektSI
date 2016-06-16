#pragma once

#include <SFML/Graphics.hpp>

#include "playerShip.hpp"

using namespace sf;

class PlayerUpgrades
{
public:
	static unsigned int missleLevelCosts[6];
	static unsigned int misslePowerCosts[6];

	short int missleLevel;
	short int misslePower;
	short int misslePowerLvl;
	short int healthCost;

	PlayerUpgrades::PlayerUpgrades()
	{
		missleLevel = 1;
		misslePower = 50;
		misslePowerLvl = 1;
		healthCost = 500;
	}

	unsigned int missleLevelUp(unsigned int cash)
	{
		switch (missleLevel)
		{
		case 1:
			if (cash >= missleLevelCosts[0])
			{
				cash -= missleLevelCosts[0];
				missleLevel++;
			}
			break;
		case 2:
			if (cash >= missleLevelCosts[1])
			{
				cash -= missleLevelCosts[1];
				missleLevel++;
			}
			break;
		case 3:
			if (cash >= missleLevelCosts[2])
			{
				cash -= missleLevelCosts[2];
				missleLevel++;
			}
			break;
		case 4:
			if (cash >= missleLevelCosts[3])
			{
				cash -= missleLevelCosts[3];
				missleLevel++;
			}
			break;
		case 5:
			if (cash >= missleLevelCosts[4])
			{
				cash -= missleLevelCosts[4];
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
			if (cash >= misslePowerCosts[0])
			{
				cash -= misslePowerCosts[0];
				misslePower = 75;
				misslePowerLvl++;
			}
			break;
		case 75:
			if (cash >= misslePowerCosts[1])
			{
				cash -= misslePowerCosts[1];
				misslePower = 100;
				misslePowerLvl++;
			}
			break;
		case 100:
			if (cash >= misslePowerCosts[2])
			{
				cash -= misslePowerCosts[2];
				misslePower = 150;
				misslePowerLvl++;
			}
			break;
		case 150:
			if (cash >= misslePowerCosts[3])
			{
				cash -= misslePowerCosts[3];
				misslePower = 250;
				misslePowerLvl++;
			}
			break;
		case 250:
			if (cash >= misslePowerCosts[4])
			{
				cash -= misslePowerCosts[4];
				misslePower = 400;
				misslePowerLvl++;
			}
			break;
		default:break;
		}
		return cash;
	}
};

unsigned int PlayerUpgrades::missleLevelCosts[6] = { 100,250,500,1500,2500,0 };
unsigned int PlayerUpgrades::misslePowerCosts[6] = { 100,200,500,1000,2500,0 };