#pragma once


#include "State.h"




class Asset_Manegement
{
private:
	std::map<int, std::unique_ptr<sf::Texture>> m_textures;
	std::map<int, std::unique_ptr<sf::Font>> m_fonts;
	std::map<int, std::unique_ptr<sf::SoundBuffer>> m_sounds;
public:
	Asset_Manegement();
	~Asset_Manegement();

	void Add_Texture(int id, const std::string &filePath, bool isRepeated = false);
	void Add_Font(int id, const std::string &filePath);
	void Add_Sound(int id, const std::string& filePath);

	const sf::Texture& Get_Texture(int id) const;
	const sf::Font& Get_Font(int id) const;
	const sf::SoundBuffer& Get_Sound(int id) const;
};

