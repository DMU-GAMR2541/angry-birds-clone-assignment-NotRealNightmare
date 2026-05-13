#pragma once
#include "DynamicObject.h"
#include <iostream>

class Catapult : public DynamicObject {
private:
    float xPos = 150.0f;
    float yPos = 500.0f;
    float halfX = 7.0f;
    float halfY = 60.0f;
    sf::Vector2f shotPos;


public:
    Catapult() = default;
    Catapult(b2World& world, float xPos, float yPos, float halfWidth, float halfHeight, std::string str_sprite);
    ~Catapult() = default;

    sf::Vector2f getShotPos() { return shotPos; }

    void render(sf::RenderWindow& window) override;
    void update() override;
};