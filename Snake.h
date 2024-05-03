#pragma once
#include <list>
#include <SFML/Graphics.hpp>


class Snake : public sf::Drawable
{
private:
	// we dont use vector because it require reallocate when it exceeds the capacity,
	// then the old address is no more valid, whereas list is contrast

	std::list<sf::Sprite> m_body;

	// Iterator point to head and tail
	std::list<sf::Sprite>::iterator m_head;
	std::list<sf::Sprite>::iterator m_tail;

public:
	Snake();
	~Snake();

	void Init(const sf::Texture& texture);

	// This method will move the snake and gives direction
	void Move(const sf::Vector2f& direction);

	// This method will detect if snake has collided with some other object
	bool IsOn(const sf::Sprite& other) const;

	// This method will detect if snake has collided with itself
	bool IsOnItself() const;

	// this method will grow the body of snake
	void Grow(const sf::Vector2f& direction);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

