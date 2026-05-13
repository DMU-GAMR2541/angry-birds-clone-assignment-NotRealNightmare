#pragma once
#include "DynamicObject.h"
#include "Enemy.h"
#include <iostream>

enum class PigType {
	smallPig,
	mediumPig,
	corporalPig,
	kingPing
};

class Pig : public DynamicObject {
private:
	float xPos;
	float yPos;
	float radius;
	PigType pigType;
	Enemy enemy;

public:
	Pig() = default;
	Pig(b2World& world, float xPos, float yPos, float radius, std::string str_sprite, PigType pigType, int Health);
	~Pig() = default;

	void render(sf::RenderWindow& window) override;
	void update() override;
	void takeDamage(int damage);
	bool isDestroyed();

};

