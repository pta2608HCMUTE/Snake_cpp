#include "Asset_Manegement.h"


Asset_Manegement::Asset_Manegement() {

}

Asset_Manegement::~Asset_Manegement() {

}

void Asset_Manegement::Add_Texture(int id, const std::string& filePath, bool isRepeated) {
	auto texture = std::make_unique<sf::Texture>();

	if (texture->loadFromFile(filePath)) {
		texture->setRepeated(isRepeated);
		m_textures[id] = std::move(texture);
	}
}
void Asset_Manegement::Add_Font(int id, const std::string& filePath) {
	auto font = std::make_unique<sf::Font>();

	if (font->loadFromFile(filePath)) {
		m_fonts[id] = std::move(font);
	}
}

void Asset_Manegement::Add_Sound(int id, const std::string& filePath) {
	auto sound = std::make_unique<sf::SoundBuffer>();
	if (sound->loadFromFile(filePath)) {
		m_sounds[id] = std::move(sound);
	}
}

const sf::Texture& Asset_Manegement::Get_Texture(int id) const {
	return *(this->m_textures.at(id));	// using get() method for get raw pointer
}

const sf::Font& Asset_Manegement::Get_Font(int id) const {
	return *(this->m_fonts.at(id));
}
const sf::SoundBuffer& Asset_Manegement::Get_Sound(int id) const {
	return *(this->m_sounds.at(id));
}
