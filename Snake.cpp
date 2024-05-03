#include "Snake.h"

Snake::Snake() : m_body{std::list<sf::Sprite>(4)} {	// it means at begin snake length 4: [0][1][2][3]
	m_head = --m_body.end();
	m_tail = m_body.begin();
}

Snake::~Snake() {

}

void Snake::Init(const sf::Texture &texture) {
	float x = 16.f;
	for (auto& a : m_body) {
		a.setTexture(texture);
		a.setPosition(x, 16.f);
		x += 16.f;
	}
}

void Snake::Move(const sf::Vector2f& direction) {
	m_tail->setPosition(m_head->getPosition() + direction); 
	m_head = m_tail;
	m_tail++;
	
	if (m_tail == m_body.end()) {
		m_tail = m_body.begin();
	}
}


bool Snake::IsOn(const sf::Sprite& other) const {
	return other.getGlobalBounds().intersects(m_head->getGlobalBounds());
}

bool Snake::IsOnItself() const {
	bool flag = false;
	for (auto piece = m_body.begin(); piece != m_body.end(); ++piece) {
		if (m_head != piece) {
			flag = IsOn(*piece);
			if (flag) {
				break;
			}
		}
	}
	return flag;
}

void Snake::Grow(const sf::Vector2f& direction) {
	sf::Sprite newPiece;
	newPiece.setTexture(*(m_body.begin()->getTexture()));	// We can get texture on available body
	newPiece.setPosition(m_head->getPosition() + direction); // this will add the next to head
	m_head = m_body.insert(++m_head, newPiece);
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto& a : m_body) {
		target.draw(a);
	}
}
