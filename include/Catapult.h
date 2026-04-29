#pragma once
#include "DynamicObject.h"
#include "Slingshot.h"
#include <iostream>

class Catapult : public DynamicObject {
private:
	float xPos;
	float yPos;
	float halfWidth;
	float halfHeight;
	sf::Texture catapultTexture;
	sf::Sprite catapultSprite;
	Slingshot slingshot;
	b2Vec2 originPos;
	b2Vec2 targetPos;
	b2Vec2 launchVec;
	bool b_launched;

public:
	Catapult() = default;
	Catapult(b2World& world, float xPos, float yPos, float halfWidth, float halfHeight, std::string str_sprite, int i_initialTension, std::string str_birdType);
	~Catapult() = default;

	void render(sf::RenderWindow& window) override;
	void update() override;
	void aim(sf::RenderWindow& window);
	void launch();
	bool isLaunched();
};