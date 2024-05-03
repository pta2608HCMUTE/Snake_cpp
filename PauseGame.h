#pragma once

#include "State.h"
#include "Game.h"

class PauseGame : public State
{
private:
	std::shared_ptr<Context> m_context;
	sf::Text m_PauseTitle;
	sf::Sprite m_MusicEna;
	sf::Sprite m_MusicDis;
	sf::IntRect m_SoundArea;


public:
	PauseGame(std::shared_ptr<Context>& context);
	~PauseGame();

	// Virtual functions
	virtual void Init() override;
	virtual void ProcessInput() override;
	virtual void Update(sf::Time deltaTime) override;
	virtual void Render() override;
};

