#pragma once
#include "DynamicObject.h"
#include "ContactListener.h"
#include "Pig.h"

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
	bool isLaunched = false;
	bool  abilityUsed = false;
	sf::Clock bombTimer;
	float bombDeletionTime = -1.0f;
	sf::Vector2f startPos;
	BirdType birdType;

	

public:
	Bird() = default;
	Bird(b2World& world, float xPos, float yPos, float radius, float shotPower, std::string str_sprite, BirdType birdType);
	~Bird() = default;

	void chuckAbility(b2Vec2 speedBoost);
	std::vector<std::shared_ptr<Bird>> theBluesAbility(b2World& world);
	std::vector<std::shared_ptr<Bird>> bombAbility(b2World& world, float DestuctionTime, std::vector<std::shared_ptr<Pig>>& vecPig);

	void setDestructionTime(float seconds) {
		bombDeletionTime = seconds;
		bombTimer.restart();
	}

	bool shouldDelete() {
		if (bombDeletionTime < 0) return false;
		return bombTimer.getElapsedTime().asSeconds() >= bombDeletionTime;
	}

	void resetTextureRect() {
		sp_Sprite.setTextureRect(sf::IntRect(0, 0, te_Texture.getSize().x, te_Texture.getSize().y));
		sp_Sprite.setOrigin(te_Texture.getSize().x / 2.0f, te_Texture.getSize().y / 2.0f);
	}

	bool hasUsedAbility() const { return abilityUsed; }
	bool getIsLaunched() const { return isLaunched; }
	void setDragging(bool dragging);
	bool getDragging();
	sf::Vector2f getStartPos();
	BirdType getBirdType();

	void render(sf::RenderWindow& window) override;
	void update() override;
	void dragging();
	void launch(sf::Vector2f shotPos);
	
};