#pragma once
#include "StaticObject.h"
#include <iostream>

class Catapult : public StaticObject {
private:
    float xPos;
    float yPos;
    float halfWidth;
    float halfHeight;

public:
    Catapult() = default;
    Catapult(b2World& world, float xPos, float yPos, float halfWidth, float halfHeight, std::string str_sprite);
    ~Catapult() = default;
    void render(sf::RenderWindow& window) override;
    void update() override;
};