#pragma once



#include "Asset_Manegement.h"
#include "State_Management.h"
#include "Main_Menu.h"
#include "GamePlay.h"
#include "PauseGame.h"
#include "HowToPlay.h"
#include <ctime>	// random

enum AssetID {
	MAIN_FONT = 0,
	GRASS,
	FOOD,
	WALL,
	SNAKE,
	EATINGSOUND,
	BGS,
	BACKGROUNDIMAGE,
	MENUBGS,
	SCOREBOX,
	MUSICENA,
	MUSICDIS,
	MENUBG,
	SECOND_FONT,
	GAMEOVERBG,
};


struct Context {
	std::unique_ptr<Asset_Manegement> m_Assets;
	std::unique_ptr<State_Management> m_States;
	std::unique_ptr<sf::RenderWindow> m_window;
	int isMusicEna;

	Context(){
		m_Assets = std::make_unique<Asset_Manegement>();
		m_States = std::make_unique<State_Management>();
		m_window = std::make_unique<sf::RenderWindow>();
		isMusicEna = 1;
	}
};



class Game
{
private:
	std::shared_ptr <Context> m_context;
	const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);	// This mean 60frames/1 seconds

public:
	Game();
	~Game();
	void Init();
	void Run();

};

