#pragma once
#include "DynamicObject.h"

class Bird : public DynamicObject {
private:
	float xPos;
	float yPos;
	float radius;
	sf::CircleShape circle;
	sf::Texture texture;
	sf::Sprite sprite;

public:
	Bird() = default;
	Bird(b2World& world, float xPos, float yPos, float radius);
	~Bird() = default;

	void render(sf::RenderWindow& window) override;
	void update() override;
	void launch();

};