#include "Pig.h"
#include <iostream>

Pig::Pig(b2World& world, float xPos, float yPos, float radius, std::string str_sprite, int Health)
	: DynamicObject(world, b2Vec2(xPos / SCALE, yPos / SCALE), str_sprite), enemy(Health)
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
	b2_fixtureDef.friction = 0.5f;
	b2_fixtureDef.restitution = 0.6f;
	body->CreateFixture(&b2_fixtureDef);

	// Texture
	if (!pigTexture.loadFromFile(str_sprite)) {
		std::cout << "Error loading pig texture" << std::endl;
	}

	// Creating the sprite
	pigSprite = sf::Sprite(pigTexture);
	pigSprite.setPosition(b2_bodyDef.position.x * SCALE, b2_bodyDef.position.y * SCALE);
	pigSprite.setOrigin(pigTexture.getSize().x / 2.0f, pigTexture.getSize().y / 2.0f);
}

void Pig::render(sf::RenderWindow& window) {
	if (!enemy.checkIfPopped()) {
		window.draw(pigSprite);
	}	
}

void Pig::update() {
	pigSprite.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
	pigSprite.setRotation(body->GetAngle() * (180.0f / PI));
}

void Pig::takeDamage(int damage) {
	enemy.takeDamage(damage);
	if (enemy.checkIfPopped()) {
		std::cout << "Pig Destroyed!" << std::endl;
	}
}

bool Pig::isDestroyed() {
	return enemy.checkIfPopped();
}
