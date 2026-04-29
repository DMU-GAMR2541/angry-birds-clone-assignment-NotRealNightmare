#include "Bird.h"
#include <iostream>

Bird::Bird(b2World& world, float xPos, float yPos, float radius, std::string str_sprite)
	: DynamicObject(world, b2Vec2(xPos / SCALE, yPos / SCALE), str_sprite) 
{
	this->xPos = xPos;
	this->yPos = yPos;
	this->radius = radius;

	b2_bodyDef.position.Set(xPos / SCALE, yPos / SCALE);
	b2_bodyDef.type = b2_dynamicBody;
	body = world.CreateBody(&b2_bodyDef);

	b2_circleShape.m_radius = radius / SCALE;

	b2_fixtureDef.shape = &b2_circleShape;
	b2_fixtureDef.density = 1.0f;
	b2_fixtureDef.restitution = 0.5f;
	body->CreateFixture(&b2_fixtureDef);

	// Texture
	if (!birdTexture.loadFromFile(str_sprite)) {
		std::cout << "Error loading bird texture" << std::endl;
	}

	// Creating the sprite
	birdSprite = sf::Sprite(birdTexture);
	birdSprite.setPosition(b2_bodyDef.position.x * SCALE, b2_bodyDef.position.y * SCALE);
	birdSprite.setOrigin(birdTexture.getSize().x / 2.0f, birdTexture.getSize().y / 2.0f);

	
}


void Bird::render(sf::RenderWindow& window) { 
	window.draw(birdSprite);
}

void Bird::update() {
	birdSprite.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
	birdSprite.setRotation(body->GetAngle() * (180.0f / PI));
}

void Bird::launch() {
	b2_bodyDef.position.Set(100.0f / SCALE, 500.0f / SCALE);
	body->SetTransform(b2Vec2(100.0f / SCALE, 500.0f / SCALE), 0);
	body->SetLinearVelocity(b2Vec2(0, 0));
	body->SetAngularVelocity(0);
	body->ApplyLinearImpulse(b2Vec2(5.0, -5.0), body->GetWorldCenter(), true);
	std::cout << "Firing!!!!" << std::endl;
}