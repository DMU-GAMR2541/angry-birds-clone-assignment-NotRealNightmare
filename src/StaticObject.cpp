#include "StaticObject.h"
#include <iostream>

StaticObject::StaticObject(b2World& world, b2Vec2 b2_Pos, float halfWidth, float halfHeight, std::string str_sprite) {
    this->str_sprite = str_sprite;

    b2_bodyDef.position = b2_Pos;
    body = world.CreateBody(&b2_bodyDef);

    // creating texture
    if (!str_sprite.empty()) {
        if (!te_Texture.loadFromFile(str_sprite)) {
            std::cout << "Error loading texture" << std::endl;
        }
        sp_Sprite = sf::Sprite(te_Texture);
        sp_Sprite.setPosition(b2_bodyDef.position.x * SCALE, b2_bodyDef.position.y * SCALE);
        sp_Sprite.setOrigin(te_Texture.getSize().x / 2.0f, te_Texture.getSize().y / 2.0f);
    }

    b2_shape.SetAsBox(halfWidth / SCALE, halfHeight / SCALE);

    b2_fixtureDef.shape = &b2_shape;
    b2_fixtureDef.density = 0.0f;
    body->CreateFixture(&b2_fixtureDef);
}

b2Body* StaticObject::getBody() { return body; }
    