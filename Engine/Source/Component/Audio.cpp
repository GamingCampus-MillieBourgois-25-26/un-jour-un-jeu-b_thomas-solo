#include "pch.h"
#include "Include/Component/Audio.h"
#include <iostream>
#include <Include/Engine.h>
#include "Include/Module/RessourceModule.h"

void Audio::load(std::string name) {
    sounds[name] = new sf::Sound(*ressourceModule->GetBuffer(name));
}

void Audio::play(std::string name)
{
    sounds[name]->play();
}

void Audio::stop(std::string name)
{
    sounds[name]->stop();
}

void Audio::loop(std::string name)
{
    sounds[name]->setLooping(!sounds[name]->isLooping());
}

void Audio::Destroy()
{
    for (auto& paire : sounds) {
        delete paire.second;
    }
}

Audio::Audio()
{
    ressourceModule = Engine::GetInstance()->GetModuleManager()->GetModule<RessourceModule>();
}





