#pragma once
#include "SFML/Graphics.hpp"
#include "Include/Module.h"
#include <map>
#include <iostream>
#include <SFML/Audio.hpp>
#include <filesystem>

class RessourceModule : public Module
{
	/*module qui enregistre une seule fois les chose a charger comme les textures et les fonts (prochainement les buffers)*/
private:
	std::map<std::string, sf::Texture*>textures;
	std::map<std::string, sf::Font*>fonts;
	std::map<std::string, sf::SoundBuffer*>buffers;

public:
	sf::Texture* GetTexture(std::string name) {	return textures[name]; }
	void AddTexture(std::string name, std::filesystem::path path);
	sf::Font* GetFont(std::string name) { return fonts[name]; }
	void AddFont(std::string name, std::filesystem::path path);
	sf::SoundBuffer* GetBuffer(std::string name) { return buffers[name]; }
	void AddBuffer(std::string name, std::filesystem::path path);
	void Destroy()override;
};

