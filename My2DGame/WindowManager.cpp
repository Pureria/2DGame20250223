#include "WindowManager.h"

bool WindowManager::Initialize(sf::VideoMode mode, const sf::String title)
{
	_window.create(mode, title);
	return true;
}

bool WindowManager::CheckWindowEvent()
{
	sf::Event event;
	while (_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			_window.close();
			return false;
		}
	}
	return true;
}

bool WindowManager::WindowUpdate()
{
	_window.display();
	return true;
}

bool WindowManager::Release()
{
	_window.close();
	return true;
}