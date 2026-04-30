#pragma once
#include "DynamicObject.h"
#include <iostream>

class Plank : public DynamicObject {
private:
    float xPos;
    float yPos;
    float halfWidth;
    float halfHeight;
    sf::Texture plankTexture;
    sf::Sprite plankSprite;

public:
    Plank() = default;
    Plank(b2World& world, float xPos, float yPos, float halfWidth, float halfHeight, std::string str_sprite)
        : DynamicObject(world, b2Vec2(xPos / SCALE, yPos / SCALE), str_sprite)
    {
        this->xPos = xPos;
        this->yPos = yPos;
        this->halfWidth = halfWidth;
        this->halfHeight = halfHeight;

        b2_bodyDef.type = b2_dynamicBody;
        b2_bodyDef.position.Set(xPos / SCALE, yPos / SCALE);
        body = world.CreateBody(&b2_bodyDef);

        b2PolygonShape b2_plankBox;
        b2_plankBox.SetAsBox(halfWidth / SCALE, halfHeight / SCALE);

        b2_fixtureDef.shape = &b2_plankBox;
        b2_fixtureDef.density = 1.5f;
        b2_fixtureDef.friction = 0.3f;
        body->CreateFixture(&b2_fixtureDef);

        // creating texture
        if (!plankTexture.loadFromFile(str_sprite)) {
            std::cout << "Error loading plank texture" << std::endl;
        }

        // creating the sprite
        plankSprite = sf::Sprite(plankTexture);
        plankSprite.setPosition(b2_bodyDef.position.x * SCALE, b2_bodyDef.position.y * SCALE);
        plankSprite.setOrigin(plankTexture.getSize().x / 2.0f, plankTexture.getSize().y / 2.0f);
        plankSprite.setScale(0.75f, 1.0f);


    }

    void render(sf::RenderWindow& window) override {
        window.draw(plankSprite);
    }

    void update() override {
        plankSprite.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
        plankSprite.setRotation(body->GetAngle() * (180.0f / PI) + 90.0f);
        
    }
};