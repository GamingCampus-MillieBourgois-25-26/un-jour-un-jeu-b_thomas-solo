#include "pch.h"
#include "Include/Module/RessourceModule.h"

void RessourceModule::AddTexture(std::string name, std::filesystem::path path)
{
	if(textures[name] == nullptr)
	{
		textures[name] = new sf::Texture();
		if (!textures[name]->loadFromFile(path))
			std::cout << "erreur chargement de : " << name << " avec " << path;
	}
	else
		std::cout << "oui";
}

void RessourceModule::AddFont(std::string name, std::filesystem::path path)
{
	if (fonts[name] == nullptr)
	{
		fonts[name] = new sf::Font();
		if (!fonts[name]->openFromFile(path))
			std::cout << "erreur chargement de : " << name << " avec " << path;
	}
}

void RessourceModule::AddBuffer(std::string name, std::filesystem::path path)
{
	if (buffers[name] == nullptr)
	{
		buffers[name] = new sf::SoundBuffer();
		if (!buffers[name]->loadFromFile(path))
			std::cout << "erreur chargement de : " << name << " avec " << path;
	}
}

void RessourceModule::Destroy()
{
	for (auto& paire : textures) {
		delete paire.second;
	}
	for (auto& paire : fonts) {
		delete paire.second;
	}
	for (auto& paire : buffers) {
		delete paire.second;
	}
}
