#include "Bird.h"
#include <iostream>

Bird::Bird(b2World& world, float xPos, float yPos, float radius, float shotPower, std::string str_sprite, BirdType birdType)
	: DynamicObject(world, b2Vec2(xPos, yPos), str_sprite) 
{
	this->xPos = xPos;
	this->yPos = yPos;
	this->radius = radius;
	this->shotPower = shotPower;
	this->startPos = sf::Vector2f(xPos, yPos);
	this->birdType = birdType;


	b2_circleShape.m_radius = radius / SCALE;
	b2_fixtureDef.shape = &b2_circleShape;

	switch (birdType) {
		case BirdType::Red:
			b2_fixtureDef.density = 1.0f;
			b2_fixtureDef.restitution = 0.5f;

			body->SetGravityScale(1.0f);
			sp_Sprite.setTextureRect(sf::IntRect(770, 173, 65, 63));
			sp_Sprite.setScale(0.5f, 0.5f);
			break;
		case BirdType::Chuck:
			b2_fixtureDef.density = 1.0f;		// lighter
			b2_fixtureDef.restitution = 0.5f;
			
			body->SetGravityScale(0.5f);		// less gravity
			sp_Sprite.setTextureRect(sf::IntRect(150, 767, 82, 76));
			sp_Sprite.setScale(0.5f, 0.5f);
			break;
		case BirdType::theBlues:
			b2_fixtureDef.density = 1.0f;		// lighter
			b2_fixtureDef.restitution = 0.5f;
		
			body->SetGravityScale(0.5f);		// less gravity
			sp_Sprite.setTextureRect(sf::IntRect(766, 244, 45, 45));
			sp_Sprite.setScale(0.5f, 0.5f);
			break;
		case BirdType::Bomb:
			b2_fixtureDef.density = 3.0f;		// heavier
			b2_fixtureDef.restitution = 0.1f;
		
			body->SetGravityScale(1.5f);		// more gravity
			sp_Sprite.setTextureRect(sf::IntRect(721, 13, 93, 124));
			sp_Sprite.setScale(0.4, 0.4f);
			break;

	}
	body->CreateFixture(&b2_fixtureDef);
	sp_Sprite.setOrigin(sp_Sprite.getTextureRect().width / 2.0f, sp_Sprite.getTextureRect().height / 2.0f);
}


void Bird::render(sf::RenderWindow& window) { 
	window.draw(sp_Sprite);
}


void Bird::update() {
	sp_Sprite.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
	sp_Sprite.setRotation(body->GetAngle() * (180.0f / PI));
}

void Bird::setDragging(bool dragging) { isDragging = dragging; }
bool Bird::getDragging() { return isDragging; }
sf::Vector2f Bird::getStartPos() { return startPos; }
BirdType Bird::getBirdType() { return birdType; }

void Bird::dragging() {
	isDragging = true;
	body->SetGravityScale(0);
	body->SetLinearVelocity(b2Vec2(0, 0));
	body->SetAngularVelocity(0);
}

void Bird::launch(sf::Vector2f shotPos) {
	isDragging = false;
	body->SetGravityScale(1.0f);
	sf::Vector2f targetPos{ body->GetPosition().x * SCALE, body->GetPosition().y * SCALE };
	sf::Vector2f launchVector = (targetPos - shotPos) / SCALE;
	b2Vec2 impulseMagnitude(-launchVector.x * shotPower, -launchVector.y * shotPower);
	body->ApplyLinearImpulseToCenter(impulseMagnitude, true);
	std::cout << "Firing!!!!" << std::endl;
}

void Bird::chuckAbility(b2Vec2 speedBoost) {
	body->ApplyLinearImpulseToCenter(b2Vec2 (speedBoost.x, speedBoost.y), true);
	std::cout << "Chuck ability activated! " << std::endl;
}

std::vector<std::shared_ptr<Bird>> Bird::theBluesAbility(b2World& world) {
	std::vector<std::shared_ptr<Bird>> newBirds;

	// only trigger once
	if (abilityUsed) return newBirds;
	abilityUsed = true;

	b2Vec2 vel = body->GetLinearVelocity();

	// dont trigger if bird hasnt been launched yet
	if (vel.x == 0 && vel.y == 0) return newBirds;

	// two clones, one angled up and one angled down
	float angles[2] = { -2.5f, 2.5f };

	for (float offset : angles) {
		float bx = body->GetPosition().x * SCALE;
		float by = body->GetPosition().y * SCALE;

		auto clone = std::make_shared<Bird>(world, bx, by, radius, shotPower,
			"../assets/Ang_Birds/Angry_Birds2.png",
			BirdType::theBlues);
		clone->getBody()->GetUserData().pointer = 100;
		clone->abilityUsed = true;

		clone->getBody()->SetLinearVelocity(b2Vec2(vel.x, vel.y + offset));
		newBirds.push_back(clone);
	}

	return newBirds;
}