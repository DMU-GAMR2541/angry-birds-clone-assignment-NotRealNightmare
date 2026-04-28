#pragma once
#include "DynamicObject.h"

class Bird : public DynamicObject {
private:
	float xPos;
	float yPos;
	float radius;
	sf::Texture birdTexture;
	sf::Sprite birdSprite;

public:
	Bird() = default;
	Bird(b2World& world, float xPos, float yPos, float radius, std::string str_sprite);
	~Bird() = default;

	void render(sf::RenderWindow& window) override;
	void update() override;
	void launch();

};