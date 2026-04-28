#include "StaticObject.h"

StaticObject::StaticObject(b2World& world, b2Vec2 b2_Pos, float halfWidth, float halfHeight, std::string str_sprite) {
    this->str_sprite = str_sprite;

    b2_bodyDef.position = b2_Pos;
    body = world.CreateBody(&b2_bodyDef);

    b2_shape.SetAsBox(halfWidth / SCALE, halfHeight / SCALE);

    b2_fixtureDef.shape = &b2_shape;
    b2_fixtureDef.density = 0.0f;
    body->CreateFixture(&b2_fixtureDef);
}

b2Body* StaticObject::getBody() { return body; }
    