#include "Bird.h"
#include <iostream>

Bird::Bird(b2World& world, float xPos, float yPos, float radius)
	: DynamicObject(world, b2Vec2(xPos / SCALE, yPos / SCALE), "") 
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

	circle.setOrigin(radius, radius);
	circle.setFillColor(sf::Color::Yellow);
	circle.setRadius(radius);
}

void Bird::render(sf::RenderWindow& window) { 
	window.draw(circle);
}

void Bird::update() {
	circle.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
	circle.setRotation(body->GetAngle() * (180.0f / PI));
}

void Bird::launch() {
	b2_bodyDef.position.Set(100.0f / SCALE, 500.0f / SCALE);
	body->SetTransform(b2Vec2(100.0f / SCALE, 500.0f / SCALE), 0);
	body->SetLinearVelocity(b2Vec2(0, 0));
	body->SetAngularVelocity(0);
	body->ApplyLinearImpulse(b2Vec2(5.0, -5.0), body->GetWorldCenter(), true);
	std::cout << "Firing!!!!" << std::endl;
}