#include "State_Management.h"

State_Management::State_Management() : m_add{ false }, m_replace{ false }, m_remove{ false } {

}

State_Management::~State_Management() {

}

void State_Management::Add(std::unique_ptr<State> toAdd, bool replace) {
	m_add = true;

	m_New_State = std::move(toAdd); // because it is a unique ptr, so we use add

	m_replace = replace;
} 

void State_Management::Pop_Current() {
	m_remove = true;
}

void State_Management::Process_State_Change() {
	if (m_remove && !(m_State_Stack.empty())) {		// m_remove is true and make sure stack is not empty
		m_State_Stack.pop();
		if (!m_State_Stack.empty()) {	// Check if Stack is empty or not, if not do the thing
			m_State_Stack.top()->Start();
		}
		m_remove = false;
	}

	if (m_add) {
		if (m_replace && (m_State_Stack.empty())) {	
			m_State_Stack.pop();
			m_replace = false;
		}
		if (!m_State_Stack.empty()) {
			m_State_Stack.top()->Pause();
		}
		m_State_Stack.push(std::move(m_New_State));

		// This will make sure the new state complete its initialization before the update
		// cycle start
		m_State_Stack.top()->Init();
		m_State_Stack.top()->Start();
		m_add = false;
	}
}

std::unique_ptr<State>& State_Management::Get_Current_State() {
	return this->m_State_Stack.top();
}








