#include "Catapult.h"

Catapult::Catapult(b2World& world, float xPos, float yPos, float halfWidth, float halfHeight, std::string str_sprite)
    : StaticObject(world, b2Vec2(xPos / SCALE, yPos / SCALE), halfWidth, halfHeight, str_sprite)
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->halfWidth = halfWidth;
    this->halfHeight = halfHeight;

    sp_Sprite.setPosition(xPos, yPos);
    sp_Sprite.setOrigin(te_Texture.getSize().x / 2.0f, te_Texture.getSize().y / 2.0f);
    sp_Sprite.setScale(0.7f, 0.7f);
}

void Catapult::render(sf::RenderWindow& window) {
    window.draw(sp_Sprite);
}

void Catapult::update() {
    
}