#pragma once

#include "State.h"
#include "Game.h"

class HowToPlay : public State
{
private:
	std::shared_ptr<Context> m_context;
	std::array<sf::Text, 2> m_HTPTitle;
	std::array<sf::Text, 5> m_HTPText;
	sf::Sprite m_BackGoundImg;

public:
	HowToPlay(std::shared_ptr<Context>& context);
	~HowToPlay();

	// Virtual functions
	virtual void Init() override;
	virtual void ProcessInput() override;
	virtual void Update(sf::Time deltaTime) override;
	virtual void Render() override;
};

