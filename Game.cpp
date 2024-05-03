#include "Game.h"

Game::Game() : m_context{ std::make_shared<Context>() } {
	m_context->m_window->create(sf::VideoMode(1080, 760), "Snake", sf::Style::Close);
	m_context->m_States->Add(std::make_unique<Main_Menu>(m_context));
	std::srand(static_cast<unsigned>(time(NULL)));
	this->Init();
}

Game::~Game() {

}

void Game::Init() {
	m_context->m_Assets->Add_Font(MAIN_FONT, "Pacifico-Regular.ttf");
	m_context->m_Assets->Add_Sound(EATINGSOUND, "Eating.wav");
	m_context->m_Assets->Add_Sound(BGS, "BackGroundSound.wav");
	m_context->m_Assets->Add_Texture(GRASS, "grass.png", true); // add repeated is make sure that grass will fill all the window
	m_context->m_Assets->Add_Texture(FOOD, "food.png");
	m_context->m_Assets->Add_Texture(WALL, "wall.png", true);
	m_context->m_Assets->Add_Texture(SNAKE, "snake_rec.png");
	m_context->m_Assets->Add_Texture(BACKGROUNDIMAGE, "backgoundImg1080x760.jpg");
	m_context->m_Assets->Add_Sound(MENUBGS, "MenuBGS.wav");
	m_context->m_Assets->Add_Texture(SCOREBOX, "small.png");
	m_context->m_Assets->Add_Texture(MUSICDIS, "music_disable.png");
	m_context->m_Assets->Add_Texture(MUSICENA, "music_enable.png");
	m_context->m_Assets->Add_Texture(MENUBG, "menubackgoundImg1080x760.jpg");
	m_context->m_Assets->Add_Font(SECOND_FONT, "arial.ttf");
	m_context->m_Assets->Add_Texture(GAMEOVERBG, "gameover.jpg");
}

void Game::Run() {

	sf::Clock clock;
	sf::Time timeSinceLastFrame = sf::Time::Zero;

	while (this->m_context->m_window->isOpen()) {
		timeSinceLastFrame += clock.restart();
		while (timeSinceLastFrame > TIME_PER_FRAME) {

			timeSinceLastFrame -= TIME_PER_FRAME;

			m_context->m_States->Process_State_Change();

			m_context->m_States->Get_Current_State()->ProcessInput();

			m_context->m_States->Get_Current_State()->Update(TIME_PER_FRAME);

			m_context->m_States->Get_Current_State()->Render();
		
		}
	}
}










