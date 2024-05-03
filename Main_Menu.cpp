#include "Main_Menu.h"

Main_Menu::Main_Menu(std::shared_ptr<Context>& context) 
	: m_context{ context },isPlayButtonPressed{false}, isPlayButtonSelected{true},
	isExitButtonSelected{false}, isExitButtonPressed{false}, m_SoundArea{100, 100, 64, 64},
	isHowToPlaySelected{ false }, isHowToPlayPressed{ false }
{
	if (m_context->isMusicEna) {
		m_context->isMusicEna = 1;
	}
}

Main_Menu::~Main_Menu() {

}


void Main_Menu::Init() {
	
	// Title
	m_gameTitle.setFont(m_context->m_Assets->Get_Font(MAIN_FONT));
	m_gameTitle.setString("Snake Game");
	m_gameTitle.setFillColor(sf::Color::Blue);
	float text_x = m_gameTitle.getLocalBounds().width;
	float text_y = m_gameTitle.getLocalBounds().height;
	m_gameTitle.setPosition(sf::Vector2f((m_context->m_window->getSize().x / 2)-text_x/2,
		((m_context->m_window->getSize().y / 2) - text_y / 2)-150.f));
	m_gameTitle.setCharacterSize(40);

	// Sounds
	m_MenuBGS.setBuffer(m_context->m_Assets->Get_Sound(MENUBGS));
	m_MenuBGS.setLoop(true);
	m_MenuBGS.play();

	// Texture
	m_BackGoundImg.setTexture(m_context->m_Assets->Get_Texture(MENUBG));

	m_MusicEna.setTexture(m_context->m_Assets->Get_Texture(MUSICENA));
	m_MusicEna.setPosition(sf::Vector2f(100, 100));
	m_MusicDis.setTexture(m_context->m_Assets->Get_Texture(MUSICDIS));
	m_MusicDis.setPosition(sf::Vector2f(100, 100));
	
	// Play Button
	m_PlayButton.setFont(m_context->m_Assets->Get_Font(MAIN_FONT));
	m_PlayButton.setString("Play");

	// Exit Button
	m_ExitButton.setFont(m_context->m_Assets->Get_Font(MAIN_FONT));
	m_ExitButton.setString("Exit");

	// HowToPlay Button
	m_HowToPlay.setFont(m_context->m_Assets->Get_Font(MAIN_FONT));
	m_HowToPlay.setString("How To Play");
}

void Main_Menu::ProcessInput() {
	sf::Event ev;
	while (m_context->m_window->pollEvent(ev)) {
		if (ev.type == sf::Event::Closed)
			m_context->m_window->close();
		else if (ev.type == sf::Event::KeyPressed) {
			switch (ev.key.code) {
				case sf::Keyboard::Up: {
					if (!isPlayButtonSelected && !isExitButtonSelected) {
						isPlayButtonSelected = true;
						isHowToPlaySelected = false;
						isExitButtonSelected = false;
					}
					else if(!isPlayButtonSelected && !isHowToPlaySelected){
						isPlayButtonSelected = false;
						isHowToPlaySelected = true;
						isExitButtonSelected = false;
					}
					break;
				}
				case sf::Keyboard::Down: {
					if (!isExitButtonSelected && !isPlayButtonSelected) {
						isPlayButtonSelected = false;
						isHowToPlaySelected = false;
						isExitButtonSelected = true;
					}
					else if(!isExitButtonSelected && !isHowToPlaySelected) {
						isPlayButtonSelected = false;
						isHowToPlaySelected = true;
						isExitButtonSelected = false;
					}
					break;
				}
				case sf::Keyboard::Return: {	// Enter
					if (isPlayButtonSelected) {
						isPlayButtonPressed = true;
						isHowToPlayPressed = false;
						isExitButtonPressed = false;
					}
					else if (isHowToPlaySelected) {
						isPlayButtonPressed = false;
						isHowToPlayPressed = true;
						isExitButtonPressed = false;
					}
					else {
						isPlayButtonPressed = false;
						isHowToPlayPressed = false;
						isExitButtonPressed = true;
					}
					break;
				}
			}
		}
		else if (ev.type == sf::Event::MouseButtonPressed) {
			if (ev.mouseButton.button == sf::Mouse::Left) {
				// checking mouse position
				sf::Vector2i mousePosition = sf::Mouse::getPosition(*m_context->m_window);
				if (m_SoundArea.contains(mousePosition)) {
					m_context->isMusicEna ^= 0x1;
					if (m_context->isMusicEna) {
						m_MenuBGS.play();
					}
					else {
						m_MenuBGS.pause();
					}
				}
			}
		}
	}
}

void Main_Menu::Update(sf::Time deltaTime) {
	if (isPlayButtonSelected) {
		m_PlayButton.setFillColor(sf::Color::Blue);
		m_ExitButton.setFillColor(sf::Color::White);
		m_PlayButton.setCharacterSize(40);
		m_ExitButton.setCharacterSize(30);
		m_HowToPlay.setFillColor(sf::Color::White);
		m_HowToPlay.setCharacterSize(30);

		float play_x = m_PlayButton.getLocalBounds().width;
		float play_y = m_PlayButton.getLocalBounds().height;
		m_PlayButton.setPosition(sf::Vector2f((m_context->m_window->getSize().x / 2) - play_x / 2,
			((m_context->m_window->getSize().y / 2) - play_y / 2) - 25.f));

		float htp_x = m_HowToPlay.getLocalBounds().width;
		float htp_y = m_HowToPlay.getLocalBounds().height;
		m_HowToPlay.setPosition(sf::Vector2f((m_context->m_window->getSize().x / 2) - htp_x / 2,
			((m_context->m_window->getSize().y / 2) - htp_y / 2) + 25.f));

		float exit_x = m_ExitButton.getLocalBounds().width;
		float exit_y = m_ExitButton.getLocalBounds().height;
		m_ExitButton.setPosition(sf::Vector2f((m_context->m_window->getSize().x / 2) - exit_x / 2,
			((m_context->m_window->getSize().y / 2) - exit_y / 2) + 65.f));
	}
	else if (isExitButtonSelected) {
		m_ExitButton.setFillColor(sf::Color::Blue);
		m_PlayButton.setFillColor(sf::Color::White);
		m_PlayButton.setCharacterSize(30);
		m_ExitButton.setCharacterSize(40);
		m_HowToPlay.setFillColor(sf::Color::White);
		m_HowToPlay.setCharacterSize(30);

		float play_x = m_PlayButton.getLocalBounds().width;
		float play_y = m_PlayButton.getLocalBounds().height;
		m_PlayButton.setPosition(sf::Vector2f((m_context->m_window->getSize().x / 2) - play_x / 2,
			((m_context->m_window->getSize().y / 2) - play_y / 2) - 25.f));

		float htp_x = m_HowToPlay.getLocalBounds().width;
		float htp_y = m_HowToPlay.getLocalBounds().height;
		m_HowToPlay.setPosition(sf::Vector2f((m_context->m_window->getSize().x / 2) - htp_x / 2,
			((m_context->m_window->getSize().y / 2) - htp_y / 2) + 25.f));

		float exit_x = m_ExitButton.getLocalBounds().width;
		float exit_y = m_ExitButton.getLocalBounds().height;
		m_ExitButton.setPosition(sf::Vector2f((m_context->m_window->getSize().x / 2) - exit_x / 2,
			((m_context->m_window->getSize().y / 2) - exit_y / 2) + 65.f));
	}
	else {
		m_HowToPlay.setFillColor(sf::Color::Blue);
		m_HowToPlay.setCharacterSize(40);
		m_PlayButton.setFillColor(sf::Color::White);
		m_PlayButton.setCharacterSize(30);
		m_ExitButton.setFillColor(sf::Color::White);
		m_ExitButton.setCharacterSize(30);
		
		float play_x = m_PlayButton.getLocalBounds().width;
		float play_y = m_PlayButton.getLocalBounds().height;
		m_PlayButton.setPosition(sf::Vector2f((m_context->m_window->getSize().x / 2) - play_x / 2,
			((m_context->m_window->getSize().y / 2) - play_y / 2) - 25.f));

		float htp_x = m_HowToPlay.getLocalBounds().width;
		float htp_y = m_HowToPlay.getLocalBounds().height;
		m_HowToPlay.setPosition(sf::Vector2f((m_context->m_window->getSize().x / 2) - htp_x / 2,
			((m_context->m_window->getSize().y / 2) - htp_y / 2) + 25.f));

		float exit_x = m_ExitButton.getLocalBounds().width;
		float exit_y = m_ExitButton.getLocalBounds().height;
		m_ExitButton.setPosition(sf::Vector2f((m_context->m_window->getSize().x / 2) - exit_x / 2,
			((m_context->m_window->getSize().y / 2) - exit_y / 2) + 65.f));
	}
	
	if (isPlayButtonPressed) {
		//todo:
		// go to Play State:
		m_context->m_States->Add(std::make_unique<GamePlay>(m_context), true);
		m_MenuBGS.stop();
	}
	else if (isHowToPlayPressed) {
		m_context->m_States->Add(std::make_unique<HowToPlay>(m_context), true);
		m_MenuBGS.stop();
	}
	else if (isExitButtonPressed) {
		m_context->m_window->close();
	}
}

void Main_Menu::Render() {
	m_context->m_window->clear(sf::Color::Green);
	m_context->m_window->draw(m_BackGoundImg);
	m_context->m_window->draw(m_gameTitle);
	m_context->m_window->draw(m_PlayButton);
	m_context->m_window->draw(m_HowToPlay);
	m_context->m_window->draw(m_ExitButton);
	if (m_context->isMusicEna) {
		m_context->m_window->draw(m_MusicEna);
	}
	else {
		m_context->m_window->draw(m_MusicDis);
	}
	m_context->m_window->display();
}

