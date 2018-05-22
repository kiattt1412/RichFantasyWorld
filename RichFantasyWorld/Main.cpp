#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <crtdbg.h>
#include <memory>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <string>
#include <windows.h>
#include "Hero.h"
#include "Map.h"
#include "Monster.h"

#define _CRTDBG_MAP_ALLOC

using namespace std;



char userInput;
void InitGame();
void PrintInfo();
void gamePlay();
auto hero = std::make_shared<Hero>();
auto map = std::make_shared<Map>();
auto monster = std::make_shared<Monster>();
std::vector<std::shared_ptr<Monster>> monsterStore;
int playround = 1;
int day = 1;
int hour = 1;
bool inGame = true;
int locationX, locationY;
float minute = 0;


int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	InitGame();
	map->printMap();
	PrintInfo();
	gamePlay();
	//getchar();
	return 0;
}



void InitGame()
{

	srand((unsigned int)time(NULL));
	hero->setHeroPosition(1, 1, *map);

	for (int i = 0; i < monster->MaxMonsterNumber; i++)
	{
		auto mon = std::make_shared<Monster>();

		monsterStore.push_back(mon);
		monsterStore[i]->setMonsterID(i);
		int montype = rand() % 4 + 1;
		monsterStore[i]->setMonsterType(montype);

		bool finishPlacedMonster = false;
		while (!finishPlacedMonster)
		{
			locationX = rand() % 28 + 2;
			locationY = rand() % 28 + 2;

			if (map->mapGrid[locationY][locationX] == 0)
			{
				finishPlacedMonster = true;
			}
		}
		monsterStore[i]->setMonsterPosition(locationX, locationY, *map , montype);
	}

}

void PrintInfo()
{
	cout << "Hero HP : " << hero->heroHP << endl;
	for (int i = 0; i < monster->MaxMonsterNumber; i++)
	{
		if (monsterStore[i] != NULL)
		{
			cout << "Monster " << i << " HP :" << monsterStore[i]->monsterHP  
				 << " | Type : " << monsterStore[i]->monsterType
				 << " | Atk  : " << monsterStore[i]->monsterAtkDamage << endl ;
		}
		
	}
}

void gamePlay()
{
	if (playround > 1)
	{
		std::system("cls");
		map->printMap();
		PrintInfo();
	}
	while (true && hero->isAlive && inGame)
	{
		if (!hero->isFighting)
		{
			//cin >> userInput;
			if (_kbhit())
			{
				userInput = static_cast<char>(_getch());
				if (userInput == 'W' || userInput == 'A' || userInput == 'S' || userInput == 'D' ||
					userInput == 'w' || userInput == 'a' || userInput == 's' || userInput == 'd')
				{
					hero->heroMove(userInput, *map, monsterStore);
					std::system("cls");
					map->printMap();
					PrintInfo();
				}
				else if (userInput == 'x' || userInput == 'X')
				{
					inGame = false;
				}
			}			
			cout << "Day : " << day << " Hour : " << hour  << " Minute : " << minute << "\r"; 
			if (minute >= 60) { minute = 0; hour++; }
			if (hour >= 24)
			{
				hour = 0;
				day++;
				for (int i = 0; i < monster->MaxMonsterNumber; i++)
				{
					if (monsterStore[i] != NULL)
					{
						monsterStore[i]->monsterStronger();
					}
				}
				std::system("cls");
				map->printMap();
				PrintInfo();
			}

			minute+=0.03*100;

			Sleep(30);
			
		}
		else if (hero->isFighting)
		{
			//cin >> userInput;
			//userInput = (int)_getch();
			if (_kbhit())
			{
				userInput = static_cast<char>(_getch());
				if (userInput == 'W' || userInput == 'A' || userInput == 'S' || userInput == 'D' ||
					userInput == 'w' || userInput == 'a' || userInput == 's' || userInput == 'd')
				{
					hero->isFighting = false;
					hero->heroMoveOut(userInput, *map, monsterStore);
					std::system("cls");
					map->printMap();
					PrintInfo();
				}

				else if (userInput == 'k' || userInput == 'K')
				{
					hero->damageCal(monsterStore, *map);
					std::system("cls");
					map->printMap();
					PrintInfo();
					
				}
				else if (userInput == 'x' || userInput == 'X')
				{
					inGame = false;
				}
			}
			cout << "Day : " << day << " Hour : " << hour << " Minute : " << minute << "\r";
			minute += 0.03*100;
			if (minute >= 60) { minute = 0; hour++; }
			if (hour >= 24) 
			{ 
				hour = 0; 
				day++;
				for (int i = 0; i < monster->MaxMonsterNumber; i++)
				{
					if (monsterStore[i] != NULL)
					{
						monsterStore[i]->monsterStronger();
					}
				}
				std::system("cls");
				map->printMap();
				PrintInfo();
			}
			Sleep(30);
		}
	}
	if (!hero->isAlive)
	{
		hero->isAlive = true;
		hero.reset();
		playround++;
		hero = std::make_shared<Hero>();
		monster.reset();
		monster = std::make_shared<Monster>();
		map.reset();
		map = std::make_shared<Map>();
		monsterStore.clear();
		//std::vector<std::shared_ptr<Monster>> monsterStore;
		InitGame();
		gamePlay();
	}
}