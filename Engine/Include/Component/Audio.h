#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <vector>
#include "Include/Component.h"
class RessourceModule;
class Audio : public Component{
    /*Component de base du moteur
    permet de jouer des sons avec sfml audio*/
private:
    RessourceModule* ressourceModule = nullptr;
public:
    std::map<std::string,sf::Sound*> sounds;
    void load(std::string name);
    void play(std::string name);
    void stop(std::string name);
    void loop(std::string name);
    void Destroy()override;

    Audio();
};
