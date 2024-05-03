#include "GameOver.h"

GameOver::GameOver(std::shared_ptr<Context>& context)
	: m_context{ context }, isPlayAgainButtonPressed{ false }, isPlayAgainButtonSelected{ true },
	isExitButtonSelected{ false }, isExitButtonPressed{ false }
{
}

GameOver::~GameOver() {

}

void GameOver::Init() {
	//m_context->m_Assets->Add_Font(MAIN_FONT, "Pacifico-Regular.ttf"); // we also declared it

	// Title
	m_gameOverTitle.setFont(m_context->m_Assets->Get_Font(MAIN_FONT));
	m_gameOverTitle.setString("Game Over");
	float text_x = m_gameOverTitle.getLocalBounds().width;
	float text_y = m_gameOverTitle.getLocalBounds().height;
	m_gameOverTitle.setPosition(sf::Vector2f((m_context->m_window->getSize().x / 2) - text_x / 2,
		((m_context->m_window->getSize().y / 2) - text_y / 2) - 250.f));
	m_gameOverTitle.setCharacterSize(40);

	// Play Button
	m_PlayAgainButton.setFont(m_context->m_Assets->Get_Font(MAIN_FONT));
	m_PlayAgainButton.setString("Play Again");


	// Exit Button
	m_ExitButton.setFont(m_context->m_Assets->Get_Font(MAIN_FONT));
	m_ExitButton.setString("Exit");

	// Texture
	m_BackGoundImg.setTexture(m_context->m_Assets->Get_Texture(GAMEOVERBG));
}

void GameOver::ProcessInput() {
	sf::Event ev;
	while (m_context->m_window->pollEvent(ev)) {
		if (ev.type == sf::Event::Closed)
			m_context->m_window->close();
		else if (ev.type == sf::Event::KeyPressed) {
			switch (ev.key.code) {
			case sf::Keyboard::Up: {
				if (!isPlayAgainButtonSelected) {
					isPlayAgainButtonSelected = true;
					isExitButtonSelected = false;
				}
				break;
			}
			case sf::Keyboard::Down: {
				if (!isExitButtonSelected) {
					isPlayAgainButtonSelected = false;
					isExitButtonSelected = true;
				}
				break;
			}
			case sf::Keyboard::Return: {	// Enter
				if (isPlayAgainButtonSelected) {
					isPlayAgainButtonPressed = true;
					isExitButtonPressed = false;
				}
				else {
					isPlayAgainButtonPressed = false;
					isExitButtonPressed = true;
				}
				break;
			}
			}
		}
	}
}

void GameOver::Update(sf::Time deltaTime) {
	if (isPlayAgainButtonSelected) {
		m_PlayAgainButton.setFillColor(sf::Color::Blue);
		m_ExitButton.setFillColor(sf::Color::White);
		m_PlayAgainButton.setCharacterSize(40);

		m_ExitButton.setCharacterSize(30);

		float play_x = m_PlayAgainButton.getLocalBounds().width;
		float play_y = m_PlayAgainButton.getLocalBounds().height;
		m_PlayAgainButton.setPosition(sf::Vector2f((m_context->m_window->getSize().x / 2) - play_x / 2,
			((m_context->m_window->getSize().y / 2) - play_y / 2) - 125.f));

		float exit_x = m_ExitButton.getLocalBounds().width;
		float exit_y = m_ExitButton.getLocalBounds().height;
		m_ExitButton.setPosition(sf::Vector2f((m_context->m_window->getSize().x / 2) - exit_x / 2,
			((m_context->m_window->getSize().y / 2) - exit_y / 2) + -100.f + 25.f));
	}
	else if (isExitButtonSelected) {
		m_ExitButton.setFillColor(sf::Color::Blue);
		m_PlayAgainButton.setFillColor(sf::Color::White);
		m_PlayAgainButton.setCharacterSize(30);
		m_ExitButton.setCharacterSize(40);
		float play_x = m_PlayAgainButton.getLocalBounds().width;
		float play_y = m_PlayAgainButton.getLocalBounds().height;
		m_PlayAgainButton.setPosition(sf::Vector2f((m_context->m_window->getSize().x / 2) - play_x / 2,
			((m_context->m_window->getSize().y / 2) - play_y / 2) - 125.f));

		float exit_x = m_ExitButton.getLocalBounds().width;
		float exit_y = m_ExitButton.getLocalBounds().height;
		m_ExitButton.setPosition(sf::Vector2f((m_context->m_window->getSize().x / 2) - exit_x / 2,
			((m_context->m_window->getSize().y / 2) - exit_y / 2) + -100.f + 25.f));
	}

	if (isPlayAgainButtonPressed) {
		//todo:
		// go to Play State:
		m_context->m_States->Add(std::make_unique<GamePlay>(m_context), true);

	}
	else if (isExitButtonPressed) {
		m_context->m_window->close();
	}
}

void GameOver::Render() {
	m_context->m_window->clear(sf::Color::Green);
	m_context->m_window->draw(m_gameOverTitle);
	m_context->m_window->draw(m_BackGoundImg);
	m_context->m_window->draw(m_PlayAgainButton);
	m_context->m_window->draw(m_ExitButton);
	m_context->m_window->display();
}


