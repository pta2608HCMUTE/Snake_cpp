#pragma once
#include "Game.h"
#include "Snake.h"
#include "GameOver.h"

struct Context;

class GamePlay:public State
{
	
private:
	std::shared_ptr<Context> m_context;

	// All texture is 16x16 pixels
	sf::Sprite m_grass;
	sf::Sprite m_food;
	sf::Sound m_EatingSound;
	
	std::array<sf::Sprite, 5> m_walls;
	sf::Sprite m_ScoreBox;
	sf::Sprite m_LevelBox;
	sf::Sprite m_HighestBox;

	// We will use a list of multiple sprite object to represent the snake
	Snake m_snake;

	sf::Text m_scoreText;
	int m_score;
	sf::Text m_levelText;
	int m_level;
	sf::Text m_highestText;
	static int m_highestScore;

	sf::Vector2f m_snake_direction;

	sf::Vector2u size;

	// To control snake speed 
	sf::Time m_elapsedTime;

	float m_speed;

	int isMusicEna;

	bool IsPause;

public:

	GamePlay(std::shared_ptr<Context> &context);
	virtual ~GamePlay();

	//virtual functions
	virtual void Init() override;
	virtual void ProcessInput() override;
	virtual void Update(sf::Time deltaTime) override;
	virtual void Render() override;

	// This function is added because user can pause the game
	virtual void Pause() override;
	void LoadHighScore();
	void SaveHighScore();
	virtual void Start() override;


};

