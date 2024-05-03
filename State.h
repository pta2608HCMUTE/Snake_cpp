#pragma once

#include <stack>
#include <memory>
#include <string>
#include <map>
#include <iostream>
#include <array>
#include <list>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>




class State
{
protected:
	static int isMusicEna;
public:
	State() {}
	virtual ~State() {}
	static sf::Sound m_BGS;

	/*
	* All setup of a state will happen in this method, like setting up sprites,
	* text, and their positions
	*/
	virtual void Init() = 0; // Pure virtual method

	/*
	* This function will handle the events like key press, mouse clicks
	*/
	virtual void ProcessInput() = 0; 

	/*
	* This function will react to the inputs handled in process input and
	* we make changes in this state like recalculating the position of sprites and texts
	* @ parameter: deltaTime
	* this basically will be the elapsed time since the last Update() call, 
	* this is making sure that our game runs at same fps on every machine
	*/
	virtual void Update(sf::Time deltaTime) = 0; 

	/*
	* This function will draw all the sprites and text of the state on the 
	* Rendering Window
	*/
	virtual void Render() = 0;
	
	/*
	* These methods are optional, so give them a blank implementation
	*/
	virtual void Pause(){}
	virtual void Start(){}
};








