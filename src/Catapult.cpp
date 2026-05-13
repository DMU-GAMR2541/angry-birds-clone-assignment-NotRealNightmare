#include "Catapult.h"

Catapult::Catapult(b2World& world, float xPos, float yPos, float halfX, float halfY, std::string str_sprite)
    : DynamicObject(world, b2Vec2(xPos, yPos), str_sprite) 
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->halfX = halfX;
    this->halfY = halfY;
    this->shotPos = sf::Vector2f(xPos - 5.0f, yPos - 50.0f);

    b2_bodyDef.type = b2_staticBody;
    b2_bodyDef.position.Set(xPos / SCALE, yPos / SCALE);
    body = world.CreateBody(&b2_bodyDef);
    b2_polygonShape.SetAsBox(halfX / SCALE, halfY / SCALE);
}

void Catapult::render(sf::RenderWindow& window) {
    window.draw(sp_Sprite);
}

void Catapult::update() {
    sp_Sprite.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
    sp_Sprite.setRotation(body->GetAngle() * (180.0f / PI));
}