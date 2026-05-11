#pragma once
#include "DynamicObject.h"

enum class BirdType {
	Red,
	Yellow,
	Black
};

class Bird : public DynamicObject {
private:
	float xPos;
	float yPos;
	float radius;
	BirdType birdType;
	//float launchForceX;
	//float launchForceY;
	

public:
	Bird() = default;
	Bird(b2World& world, float xPos, float yPos, float radius, std::string str_sprite, BirdType birdType);
	~Bird() = default;

	void render(sf::RenderWindow& window) override;
	void update() override;
	void launch();

};