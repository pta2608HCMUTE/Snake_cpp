#include "GamePlay.h"
#include <fstream>
#include <string>


int GamePlay::m_highestScore = 0;
sf::Sound State::m_BGS;
GamePlay::GamePlay(std::shared_ptr<Context>& context)
	:m_context{ context }, m_snake_direction{16.f,0.f}, m_elapsedTime{sf::Time::Zero},
	m_score{ 0 }, IsPause{false}, m_level{1}, m_speed{0.1}
{
	LoadHighScore();
}

GamePlay::~GamePlay() {
	SaveHighScore();
}

void GamePlay::Init() {

	size = m_context->m_window->getSize();

	m_ScoreBox.setTexture(m_context->m_Assets->Get_Texture(SCOREBOX));
	m_ScoreBox.setPosition(sf::Vector2f(size.x-234, size.y-600));
	m_ScoreBox.setScale(sf::Vector2f(1.3, 1));

	m_scoreText.setFont(m_context->m_Assets->Get_Font(MAIN_FONT));
	m_scoreText.setString("Score : " + std::to_string(m_score));
	m_scoreText.setPosition(sf::Vector2f(size.x - 196, size.y - 600 + 14));
	m_scoreText.setCharacterSize(30);

	m_LevelBox.setTexture(m_context->m_Assets->Get_Texture(SCOREBOX));
	m_LevelBox.setPosition(sf::Vector2f(size.x - 234, size.y - 570 + 80));
	m_LevelBox.setScale(sf::Vector2f(1.3, 1));

	m_levelText.setFont(m_context->m_Assets->Get_Font(MAIN_FONT));
	m_levelText.setString("Level : " + std::to_string(m_level));
	m_levelText.setPosition(sf::Vector2f(size.x - 196, size.y - 570 + 14 + 80));
	m_levelText.setCharacterSize(30);

	m_HighestBox.setTexture(m_context->m_Assets->Get_Texture(SCOREBOX));
	m_HighestBox.setPosition(sf::Vector2f(size.x - 234, size.y - 570 + 180));
	m_HighestBox.setScale(sf::Vector2f(1.3, 1));

	m_highestText.setFont(m_context->m_Assets->Get_Font(MAIN_FONT));
	m_highestText.setString("Highest : " + std::to_string(m_highestScore));
	m_highestText.setPosition(sf::Vector2f(size.x - 212, size.y - 570 + 14 + 180));
	m_highestText.setCharacterSize(30);
	
	
	m_grass.setTexture(m_context->m_Assets->Get_Texture(GRASS));
	// if we set getviewport
	m_grass.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));
	//m_grass.setTextureRect(sf::IntRect (0,0,400,200));
	m_EatingSound.setBuffer(m_context->m_Assets->Get_Sound(EATINGSOUND));
	
	m_BGS.setBuffer(m_context->m_Assets->Get_Sound(BGS));
	m_BGS.setLoop(true);
	m_BGS.setVolume(50);
	if (m_context->isMusicEna) {
		m_BGS.play();
	}
	

	

	for (auto& walls : m_walls) {
		walls.setTexture(m_context->m_Assets->Get_Texture(WALL));
	}

	m_walls[0].setTextureRect(sf::IntRect(0, 0, size.x, 16));
	m_walls[1].setTextureRect(sf::IntRect(0, 0, 16, size.y));  // x, y, width, height

	m_walls[2].setPosition(sf::Vector2f(size.x - 16, 0));
	m_walls[2].setTextureRect(sf::IntRect(0, 0, 16, size.y));

	m_walls[3].setPosition(sf::Vector2f(0, size.y -16));
	m_walls[3].setTextureRect(sf::IntRect(0, 0, size.x, 16));

	m_walls[4].setPosition(sf::Vector2f(size.x - 280 - 16, 0));
	m_walls[4].setTextureRect(sf::IntRect(0, 0, 16, size.y));

	m_food.setTexture(m_context->m_Assets->Get_Texture(FOOD));
	//m_food.setOrigin(sf::Vector2f(32.f, 32.f));
	m_food.setPosition((m_context->m_window->getSize().x / 2)-140,
		m_context->m_window->getSize().y / 2);

	m_snake.Init(m_context->m_Assets->Get_Texture(SNAKE));

}

void GamePlay::ProcessInput() {
	sf::Event ev;
	while (m_context->m_window->pollEvent(ev)) {
		if (ev.type == sf::Event::Closed)
			m_context->m_window->close();
		else if (ev.type == sf::Event::KeyPressed) {
			sf::Vector2f newDirection = m_snake_direction; 
			switch (ev.key.code) {
				case sf::Keyboard::Up: {
					newDirection = sf::Vector2f(0, -16.f);
					break;
				}
				case sf::Keyboard::Down: {
					newDirection = sf::Vector2f(0, 16.f);
					break;
				}
				case sf::Keyboard::Left: {
					newDirection = sf::Vector2f(-16.f, 0.f);
					break;
				}
				case sf::Keyboard::Right: {
					newDirection = sf::Vector2f(16.f, 0.f);
					break;
				}
				case sf::Keyboard::Escape: {
					// Pause
					m_context->m_States->Add(std::make_unique<PauseGame>(m_context));
					break;
				}
			}
			if (!((newDirection + m_snake_direction) == sf::Vector2f(0, 0))) {
				m_snake_direction = newDirection;
			}
		}
	}
}

void GamePlay::Update(sf::Time deltaTime) {

	if (!this->IsPause) {
		m_elapsedTime += deltaTime;

		if (m_score >= 50) {
			m_level = 6;
			m_speed = 0.01;
		}
		else if (m_score >= 40) {
			m_level = 5;
			m_speed = 0.02;
		}
		else if (m_score >= 30) {
			m_level = 4;
			m_speed = 0.04;
		}
		else if (m_score >= 20) {
			m_level = 3;
			m_speed = 0.06;
		}
		else if (m_score >= 10) {
			m_level = 2;
			m_speed = 0.08;
		}

		if (m_elapsedTime.asSeconds() > m_speed) {	// it will call function move at 0.1ms (snake speed)

			bool isOnWall = false;
			for (auto& wall : m_walls) {
				if (m_snake.IsOn(wall)) {
					// Change to GameOver State;
					m_context->m_States->Add(std::make_unique<GameOver>(m_context), true);
					m_BGS.stop();
					break;
				}
			}

			if (m_snake.IsOn(m_food)) {
				int maxX = static_cast<int>(this->m_context->m_window->getSize().x - 32 - 280);
				int maxY = static_cast<int>(this->m_context->m_window->getSize().y - 32);

				int foodX = 16 + ((rand() % (maxX / 16)) * 16);
				int foodY = 16 + ((rand() % (maxY / 16)) * 16);
				this->m_food.setPosition(foodX, foodY);
				m_EatingSound.play();
				m_score++;
				if (m_score >= m_highestScore) {
					m_highestScore = m_score;
				}
				m_highestText.setString("Highest : " + std::to_string(m_highestScore));
				m_scoreText.setString("Score : " + std::to_string(m_score));
				m_snake.Grow(m_snake_direction);
			}
			else {
				//if (m_elapsedTime.asSeconds() > 0.1) {
				m_snake.Move(m_snake_direction); // snake speed
				//}
			}
			if (m_snake.IsOnItself()) {
				m_context->m_States->Add(std::make_unique<GameOver>(m_context), true);
				m_BGS.stop();
			}
			m_levelText.setString("Level : " + std::to_string(m_level));
			m_elapsedTime = sf::Time::Zero;
		}
	}
	
}

void GamePlay::Render() {
	m_context->m_window->clear();
	m_context->m_window->draw(m_grass);
	for(auto &wall : m_walls)
		m_context->m_window->draw(wall);
	
	m_context->m_window->draw(m_food);
	m_context->m_window->draw(m_snake);
	m_context->m_window->draw(m_ScoreBox);
	m_context->m_window->draw(m_scoreText);

	m_context->m_window->draw(m_LevelBox);
	m_context->m_window->draw(m_levelText);

	m_context->m_window->draw(m_HighestBox);
	m_context->m_window->draw(m_highestText);

	m_context->m_window->display();
}

void GamePlay::Start() {
	this->IsPause = false;
	/*if (m_context->isMusicEna) {
		m_BGS.play();
	}
	else {
		m_BGS.pause();
	}*/

}

void GamePlay::Pause() {
	this->IsPause = true;
	SaveHighScore();
}

void GamePlay::LoadHighScore() {
	std::ifstream file("highscore.txt");
	if (file.is_open()) {
		file >> m_highestScore;
		file.close();
		std::cout << "High score loaded: " << m_highestScore << std::endl;
	}
	else {
		std::cerr << "Unable to load high score!" << std::endl;
	}
}
void GamePlay::SaveHighScore() {
    std::ofstream file("highscore.txt");

    if (file.is_open()) {
        file << m_highestScore;
        file.close();
    } else {
        std::cerr << "Unable to save high score!" << std::endl;
    }
}





