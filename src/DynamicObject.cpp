#include "DynamicObject.h"

DynamicObject::DynamicObject(b2World& world, b2Vec2 b2_Pos, std::string str_sprite) {
	this->str_sprite = str_sprite;

	b2_bodyDef.type = b2_dynamicBody;
	b2_bodyDef.position = b2_Pos;

	body = world.CreateBody(&b2_bodyDef);

	b2_fixtureDef.shape = &b2_circleShape;
	body->CreateFixture(&b2_fixtureDef);
}

b2Body* DynamicObject::getBody() { return body; }
