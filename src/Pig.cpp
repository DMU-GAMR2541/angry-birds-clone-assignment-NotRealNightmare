#include "Pig.h"
#include <iostream>

Pig::Pig(b2World& world, float xPos, float yPos, float radius, std::string str_sprite, int Health)
	: DynamicObject(world, b2Vec2(xPos, yPos), str_sprite), enemy(Health)
{
	this->xPos = xPos;
	this->yPos = yPos;
	this->radius = radius;

	/*b2_bodyDef.position.Set(xPos / SCALE, yPos / SCALE);
	b2_bodyDef.type = b2_dynamicBody;
	body = world.CreateBody(&b2_bodyDef);*/

	b2_circleShape.m_radius = radius / SCALE;

	b2_fixtureDef.shape = &b2_circleShape;
	b2_fixtureDef.density = 1.0f;
	b2_fixtureDef.friction = 0.5f;
	b2_fixtureDef.restitution = 0.6f;
	body->CreateFixture(&b2_fixtureDef);


	// scales the pig sprite
	sp_Sprite.setScale(0.73f, 0.73f);
}

void Pig::render(sf::RenderWindow& window) {
	if (!enemy.checkIfPopped()) {
		window.draw(sp_Sprite);
	}	
}

void Pig::update() {
	sp_Sprite.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
	sp_Sprite.setRotation(body->GetAngle() * (180.0f / PI));
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
