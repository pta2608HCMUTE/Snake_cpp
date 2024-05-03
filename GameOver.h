#pragma once

#include "Game.h"

struct Context;


class GameOver : public State
{
private:
	std::shared_ptr<Context> m_context;
	sf::Text m_gameOverTitle;
	sf::Text m_PlayAgainButton;
	sf::Text m_ExitButton;
	sf::Sprite m_BackGoundImg;

	bool isPlayAgainButtonSelected;
	bool isPlayAgainButtonPressed;

	bool isExitButtonSelected;
	bool isExitButtonPressed;

public:
	GameOver(std::shared_ptr<Context>& context);
	virtual ~GameOver();

	// Virtual functions
	virtual void Init() override;
	virtual void ProcessInput() override;
	virtual void Update(sf::Time deltaTime) override;
	virtual void Render() override;


};