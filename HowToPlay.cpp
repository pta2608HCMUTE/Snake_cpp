#include "HowToPlay.h"
HowToPlay::HowToPlay(std::shared_ptr<Context>& context) : m_context{ context } {

}

HowToPlay::~HowToPlay() {

}


void HowToPlay::Init() {
	// Title
	for (auto& title : m_HTPTitle) {
		title.setFont(m_context->m_Assets->Get_Font(MAIN_FONT));
		title.setFillColor(sf::Color(255, 51, 153));
	}
	
	m_HTPTitle[0].setString("How To Play?");
	m_HTPTitle[0].setPosition(sf::Vector2f(100, 100));
	m_HTPTitle[0].setCharacterSize(40);

	m_HTPTitle[1].setPosition(sf::Vector2f(100, 100 + 375));
	m_HTPTitle[1].setString("Press Escape To Return");
	m_HTPTitle[1].setCharacterSize(40);

	for (auto& text : m_HTPText) {
		text.setFont(m_context->m_Assets->Get_Font(MAIN_FONT));
		text.setFillColor(sf::Color(0x33ccff));
	}
	m_HTPText[0].setPosition(sf::Vector2f(25, 100 + 75));
	m_HTPText[0].setString("- Do not hit a wall and do not bite your own tail.");

	m_HTPText[1].setPosition(sf::Vector2f(25, 100 + 125));
	m_HTPText[1].setString("- Crashing into a wall or your tail will end the game immediately.");

	m_HTPText[2].setPosition(sf::Vector2f(25, 100 + 175));
	m_HTPText[2].setString("- 1 points will be added to the score for eating the fruit.");

	m_HTPText[3].setPosition(sf::Vector2f(25, 100 + 225));
	m_HTPText[3].setString("- The length of the snake will be increased after eating the fruits.");

	m_HTPText[4].setPosition(sf::Vector2f(25, 100 + 275));
	m_HTPText[4].setString("- Use keyboard Up, Down, Left, Right to move the snake.");


	m_BackGoundImg.setTexture(m_context->m_Assets->Get_Texture(BACKGROUNDIMAGE));

}

void HowToPlay::ProcessInput() {
	sf::Event ev;
	while (m_context->m_window->pollEvent(ev)) {
		if (ev.type == sf::Event::Closed)
			m_context->m_window->close();
		else if (ev.type == sf::Event::KeyPressed) {
			switch (ev.key.code) {
				case sf::Keyboard::Escape: {
					m_context->m_States->Add(std::make_unique<Main_Menu>(m_context), true);
					break;
				}
			}
		}
	}
}

void HowToPlay::Update(sf::Time deltaTime) {

}

void HowToPlay::Render() {
	m_context->m_window->clear();
	m_context->m_window->draw(m_BackGoundImg);
	for (auto& text : m_HTPText) {
		m_context->m_window->draw(text);
	}
	for (auto &title : m_HTPTitle)
		m_context->m_window->draw(title);
	m_context->m_window->display();
}