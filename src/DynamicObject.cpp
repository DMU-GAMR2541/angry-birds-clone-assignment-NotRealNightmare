#include "DynamicObject.h"
#include <iostream>

DynamicObject::DynamicObject(b2World& world, b2Vec2 b2_Pos, std::string str_sprite) {
	
	this->str_sprite = str_sprite;

	b2_bodyDef.type = b2_dynamicBody;
	b2_bodyDef.position.Set(b2_Pos.x / SCALE, b2_Pos.y / SCALE);

	body = world.CreateBody(&b2_bodyDef);

	b2_fixtureDef.shape = &b2_circleShape;
	body->CreateFixture(&b2_fixtureDef);

	// creating texture
	if (!te_Texture.loadFromFile(str_sprite)) {
		std::cout << "Error loading plank texture" << std::endl;
	}

	// Creating the sprite
	sp_Sprite = sf::Sprite(te_Texture);
	sp_Sprite.setPosition(b2_bodyDef.position.x * SCALE, b2_bodyDef.position.y * SCALE);
	sp_Sprite.setOrigin(te_Texture.getSize().x / 2.0f, te_Texture.getSize().y / 2.0f);
}

b2Body* DynamicObject::getBody() { return body; }
