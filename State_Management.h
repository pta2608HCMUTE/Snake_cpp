#pragma once

#include "State.h"



class State_Management
{
private:
	/*
	* Stack is LIFO (last in first out) 
	*/
	std::stack<std::unique_ptr<State>> m_State_Stack;

	// State stack should only be modified at the start of next update cycle
	std::unique_ptr<State> m_New_State;

	/*
	* These 3 boolean value will be modified by Add() and Pop()
	* And depending on their values the Process_State_Change() will modified
	*/
	bool m_add;
	bool m_replace;
	bool m_remove;


public:
	State_Management();
	virtual ~State_Management();

	/*
	* This will take two args, first one will be a unique ptr to stack obj being added 
	* the second one is boolean to control whether we want to simply add a new state
	* or do we want to replace the current one to the new one
	*/

	void Add(std::unique_ptr<State> toAdd, bool replace = false);

	/*
	* This function will pop the current state from stack
	*/
	void Pop_Current();

	/*
	* This is actually is the place where state stack will actually be modified
	*/
	void Process_State_Change();

	std::unique_ptr<State>& Get_Current_State();

};

