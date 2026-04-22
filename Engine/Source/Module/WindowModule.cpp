#include "pch.h"
#include "Include/Module/WindowModule.h"

void WindowModule::Awake()
{
    window = new sf::RenderWindow(sf::VideoMode({ 600,400 }), "default");
}

void WindowModule::Clear()
{
    window->clear();
}

void WindowModule::Display()
{
    window->display();
}

void WindowModule::SetWindowSize(sf::Vector2u size)
{
    window->close();
    delete window;
    window = new sf::RenderWindow(sf::VideoMode(size), "default");
}

void WindowModule::SetWindowName(std::string name)
{
    window->setTitle(name);
}

sf::RenderWindow* WindowModule::GetWindow()
{
    return window;
}
