#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

class GameObject {
public:
	GameObject() = default;
	~GameObject() = default;

protected:
	virtual void render(sf::RenderWindow& window);

};

