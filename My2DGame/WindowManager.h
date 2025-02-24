#pragma once
#include "Singleton.h"
#include "SFML/Graphics.hpp"

class WindowManager :public Singleton<WindowManager>
{
private:
	sf::RenderWindow _window;
public:
	bool Initialize(sf::VideoMode, const sf::String);
	bool CheckWindowEvent();
	bool WindowUpdate();
	bool IsOpen() const;

	bool Release() override;

	sf::RenderWindow& GetWindow() const;
	sf::Vector2u GetWindowSize() const;
};

inline sf::RenderWindow& WindowManager::GetWindow() const
{
	return const_cast<sf::RenderWindow&>(_window);
}

inline bool WindowManager::IsOpen() const
{
	return _window.isOpen();
}

inline sf::Vector2u WindowManager::GetWindowSize() const
{
	return _window.getSize();
}