#pragma once
#include "DynamicObject.h"
#include "ContactListener.h"

enum class BirdType {
	Red,
	Chuck,
	theBlues,
	Bomb
};

class Bird : public DynamicObject, public ContactListener {
private:
	float xPos = 100.0f;
	float yPos = 500.0f;
	float radius = 15.0f;
	float shotPower = 5.0f;
	bool  isDragging = false;
	bool  abilityUsed = false;
	sf::Vector2f startPos;
	BirdType birdType;

	

public:
	Bird() = default;
	Bird(b2World& world, float xPos, float yPos, float radius, float shotPower, std::string str_sprite, BirdType birdType);
	~Bird() = default;

	void chuckAbility(b2Vec2 speedBoost);
	std::vector<std::shared_ptr<Bird>> theBluesAbility(b2World& world);

	bool hasUsedAbility() const { return abilityUsed; }
	void setDragging(bool dragging);
	bool getDragging();
	sf::Vector2f getStartPos();
	BirdType getBirdType();

	void render(sf::RenderWindow& window) override;
	void update() override;
	void dragging();
	void launch(sf::Vector2f shotPos);
	
};