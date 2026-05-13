#pragma once
#include "DynamicObject.h"
#include "Enemy.h"
#include <iostream>

enum class PigType {
	smallPig,
	mediumPig,
	corporalPig,
	kingPig
};

class Pig : public DynamicObject {
private:
	float xPos;
	float yPos;
	float radius;
	PigType pigType;
	Enemy enemy;
	bool markedForDeletion = false;

public:
	Pig() = default;
	Pig(b2World& world, float xPos, float yPos, float radius, std::string str_sprite, PigType pigType, int Health);
	~Pig() = default;

	void render(sf::RenderWindow& window) override;
	void update() override;

	void takeDamage(int damage) { enemy.takeDamage(damage); }
	int getHealth() const { return enemy.getHealth(); }
	bool checkIfPopped() const { return enemy.checkIfPopped(); }
	void markForDeletion() { markedForDeletion = true; }
	bool isMarkedForDeletion() const { return markedForDeletion; }
};

