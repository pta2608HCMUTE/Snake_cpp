#include "PauseGame.h"


PauseGame::PauseGame(std::shared_ptr<Context>& context) : m_context{ context }, m_SoundArea { 100, 100, 64, 64 } {

}

PauseGame::~PauseGame() {

}


void PauseGame::Init() {
	// Title
	m_PauseTitle.setFont(m_context->m_Assets->Get_Font(MAIN_FONT));
	m_PauseTitle.setString("Paused");
	float text_x = m_PauseTitle.getLocalBounds().width;
	float text_y = m_PauseTitle.getLocalBounds().height;
	m_PauseTitle.setPosition(sf::Vector2f((m_context->m_window->getSize().x / 2) - text_x / 2,
		((m_context->m_window->getSize().y / 2) - text_y / 2)));
	m_PauseTitle.setCharacterSize(40);
	m_MusicEna.setTexture(m_context->m_Assets->Get_Texture(MUSICENA));
	m_MusicEna.setPosition(sf::Vector2f(100, 100));
	m_MusicDis.setTexture(m_context->m_Assets->Get_Texture(MUSICDIS));
	m_MusicDis.setPosition(sf::Vector2f(100, 100));

}

void PauseGame::ProcessInput() {
	sf::Event ev;
	while (m_context->m_window->pollEvent(ev)) {
		if (ev.type == sf::Event::Closed)
			m_context->m_window->close();
		else if (ev.type == sf::Event::KeyPressed) {
			switch (ev.key.code) {
				case sf::Keyboard::Escape: {
					this->m_context->m_States->Pop_Current();
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
						m_BGS.play();
					}
					else {
						m_BGS.pause();
					}
				}
			}
		}
	}
}

void PauseGame::Update(sf::Time deltaTime) {

}

void PauseGame::Render() {
	if (m_context->isMusicEna) {
		m_context->m_window->draw(m_MusicEna);
	}
	else {
		m_context->m_window->draw(m_MusicDis);
	}

	m_context->m_window->draw(m_PauseTitle);
	m_context->m_window->display();
}
