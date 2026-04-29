#include "Catapult.h"
#include <iostream>

Catapult::Catapult(b2World& world, float xPos, float yPos, float halfWidth, float halfHeight, std::string str_sprite, int i_initialTension, std::string str_birdType)
    : DynamicObject(world, b2Vec2(xPos / SCALE, yPos / SCALE), str_sprite), slingshot(i_initialTension, str_birdType)
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->halfWidth = halfWidth;
    this->halfHeight = halfHeight;
    this->b_launched = false;

    // Origin position of the catapult
    originPos = b2Vec2(xPos / SCALE, yPos / SCALE);

    b2_bodyDef.type = b2_dynamicBody;
    b2_bodyDef.position.Set(xPos / SCALE, yPos / SCALE);
    body = world.CreateBody(&b2_bodyDef);

    b2PolygonShape b2_catapultBox;
    b2_catapultBox.SetAsBox(halfWidth / SCALE, halfHeight / SCALE);

    b2_fixtureDef.shape = &b2_catapultBox;
    b2_fixtureDef.density = 1.5f;
    b2_fixtureDef.friction = 0.3f;
    body->CreateFixture(&b2_fixtureDef);

    // 1. TEXTURE CREATION
    if (!catapultTexture.loadFromFile(str_sprite)) {
        std::cout << "Error loading catapult texture" << std::endl;
    }

    // 2. SPRITE CREATION
    catapultSprite = sf::Sprite(catapultTexture);
    catapultSprite.setPosition(xPos, yPos);
    catapultSprite.setOrigin(halfWidth, halfHeight);
}

void Catapult::render(sf::RenderWindow& window) {
    window.draw(catapultSprite);
}

void Catapult::update() {
    catapultSprite.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
    catapultSprite.setRotation(body->GetAngle() * (180.0f / PI));
}

void Catapult::aim(sf::RenderWindow& window) {
    if (!b_launched) {
        // Get mouse position in world coordinates
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        b2Vec2 mouseWorld(mousePos.x / SCALE, mousePos.y / SCALE);

        // Calculate launch vector: target - origin
        targetPos = mouseWorld;
        launchVec.x = targetPos.x - originPos.x;
        launchVec.y = targetPos.y - originPos.y;

        // Pull back slingshot based on mouse distance
        float distance = sqrt(launchVec.x * launchVec.x + launchVec.y * launchVec.y);
        slingshot.pullBack(static_cast<int>(distance));
    }
}

void Catapult::launch() {
    if (!b_launched) {
        // Use tension and launch vector for impulse
        float speedMultiplier = slingshot.getTension() * 0.5f;
        b2Vec2 impulseMagnitude(launchVec.x * speedMultiplier, launchVec.y * speedMultiplier);
        body->ApplyLinearImpulseToCenter(impulseMagnitude, true);

        slingshot.release();
        b_launched = true;
        std::cout << "Launched! Tension: " << slingshot.getTension() << std::endl;
    }
}

bool Catapult::isLaunched() {
    return b_launched;
}