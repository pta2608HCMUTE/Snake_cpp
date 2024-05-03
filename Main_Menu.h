#pragma once

#include "Game.h"

struct Context;


class Main_Menu: public State
{
private:
	std::shared_ptr<Context> m_context;
	sf::Text m_gameTitle;
	sf::Text m_PlayButton;
	sf::Text m_ExitButton;
	sf::Text m_HowToPlay;
	sf::Sprite m_BackGoundImg;
	sf::Sound m_MenuBGS;
	sf::Sprite m_MusicEna;
	sf::Sprite m_MusicDis;
	sf::IntRect m_SoundArea;

	bool isPlayButtonSelected;
	bool isPlayButtonPressed;

	bool isExitButtonSelected;
	bool isExitButtonPressed;

	bool isHowToPlaySelected;
	bool isHowToPlayPressed;


public:
	Main_Menu(std::shared_ptr<Context> &context);
	virtual ~Main_Menu();

	// Virtual functions
	virtual void Init() override;
	virtual void ProcessInput() override;
	virtual void Update(sf::Time deltaTime) override;
	virtual void Render() override;
};

