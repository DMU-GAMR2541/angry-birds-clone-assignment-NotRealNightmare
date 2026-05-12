#include "Bird.h"
#include <iostream>

Bird::Bird(b2World& world, float xPos, float yPos, float radius, std::string str_sprite, BirdType birdType)
	: DynamicObject(world, b2Vec2(xPos, yPos), str_sprite) 
{
	this->xPos = xPos;
	this->yPos = yPos;
	this->radius = radius;
	this->birdType = birdType;

	/*b2_bodyDef.position.Set(xPos / SCALE, yPos / SCALE);
	b2_bodyDef.type = b2_dynamicBody;
	body = world.CreateBody(&b2_bodyDef);*/

	b2_circleShape.m_radius = radius / SCALE;
	b2_fixtureDef.shape = &b2_circleShape;

	switch (birdType) {
		case BirdType::Red:
			b2_fixtureDef.density = 1.0f;
			b2_fixtureDef.restitution = 0.5f;
			//launchForceX = 3.0f;
			//launchForceX = -3.0f;
			body->SetGravityScale(1.0f);
			sp_Sprite.setTextureRect(sf::IntRect(770, 173, 65, 63));
			sp_Sprite.setScale(0.5f, 0.5f);
			break;
		case BirdType::Yellow:
			b2_fixtureDef.density = 0.5f;		// lighter
			b2_fixtureDef.restitution = 0.3f;
			//launchForceX = 9.0f;				// faster
			//launchForceY = -7.0f;
			body->SetGravityScale(0.5f);		// less gravity
			sp_Sprite.setTextureRect(sf::IntRect(150, 767, 82, 76));
			sp_Sprite.setScale(0.5f, 0.5f);
			break;
		case BirdType::Black:
			b2_fixtureDef.density = 3.0f;		// heavier
			b2_fixtureDef.restitution = 0.1f;
			//launchForceX = 4.0f;				// slower
			//launchForceY = -4.0f;
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

void Bird::launch() {
	//b2_bodyDef.position.Set(100.0f / SCALE, 500.0f / SCALE);
	body->SetTransform(b2Vec2(100.0f / SCALE, 500.0f / SCALE), 0);
	body->SetLinearVelocity(b2Vec2(0, 0));
	body->SetAngularVelocity(0);
	body->ApplyLinearImpulse(b2Vec2(5.0f, -5.0f), body->GetWorldCenter(), true);
	std::cout << "Firing!!!!" << std::endl;
}