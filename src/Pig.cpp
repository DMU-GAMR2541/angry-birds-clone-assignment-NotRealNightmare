#include "Pig.h"
#include <iostream>

Pig::Pig(b2World& world, float xPos, float yPos, float radius, std::string str_sprite, PigType pigType, int Health)
	: DynamicObject(world, b2Vec2(xPos, yPos), str_sprite), enemy(Health)
{
	this->xPos = xPos;
	this->yPos = yPos;
	this->radius = radius;
	this->pigType = pigType;
	

	b2_circleShape.m_radius = radius / SCALE;
	b2_fixtureDef.shape = &b2_circleShape;

	switch (pigType) {
	case PigType::smallPig:
		b2_fixtureDef.density = 0.5f;
		b2_fixtureDef.friction = 0.3f;
		b2_fixtureDef.restitution = 0.7f;

		body->SetGravityScale(1.0f);
		sp_Sprite.setTextureRect(sf::IntRect(50, 65, 52, 49));
		sp_Sprite.setScale(0.8f, 0.8f);
		break;
	case PigType::mediumPig:
		b2_fixtureDef.density = 1.0f;
		b2_fixtureDef.friction = 0.4f;
		b2_fixtureDef.restitution = 0.5f;

		body->SetGravityScale(1.0f);
		sp_Sprite.setTextureRect(sf::IntRect(49, 120, 82, 80));
		sp_Sprite.setScale(0.7f, 0.7f);
		break;
	case PigType::corporalPig:
		b2_fixtureDef.density = 2.0f;
		b2_fixtureDef.friction = 0.5f;		
		b2_fixtureDef.restitution = 0.3f;
	
		body->SetGravityScale(1.0f);		
		sp_Sprite.setTextureRect(sf::IntRect(51, 208, 97, 87));
		sp_Sprite.setScale(0.7f, 0.7f);
		break;
	case PigType::kingPig:
		b2_fixtureDef.density = 4.0f;
		b2_fixtureDef.friction = 0.8f;		
		b2_fixtureDef.restitution = 0.1f;
		
		body->SetGravityScale(1.2f);		
		sp_Sprite.setTextureRect(sf::IntRect(44, 523, 130, 156));
		sp_Sprite.setScale(0.4f, 0.4f);
		break;

	}
	
	body->CreateFixture(&b2_fixtureDef);
	sp_Sprite.setOrigin(sp_Sprite.getTextureRect().width / 2.0f, sp_Sprite.getTextureRect().height / 2.0f);
	
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


