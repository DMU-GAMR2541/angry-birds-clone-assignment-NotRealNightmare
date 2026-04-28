#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include "Non_Interactable.h"
#include "Bird.h"

int main() {
    // --- 1. WINDOW SETUP ---
    sf::RenderWindow window(sf::VideoMode(800, 600), "Annoyed_Flocks");
    window.setFramerateLimit(60);

    //Box2D works in meters. SFML works in pixels.
    const float SCALE = 30.0f;

    //Can set a definition for PI.
    const float PI = 3.1415927;

    //setup world.
    b2Vec2 b2_gravity(0.0f, 9.8f); // Earth-like gravity
    b2World world(b2_gravity);

    // GROUND (Non-interactable)
    //Setup ground for the bird to move / bounce on.
    Non_Interactable ground(world, b2Vec2(400.0f / SCALE, 590.0f / SCALE), 400.0f, 10.0f, sf::Color(34, 139, 34), "");

    // WALL (Non-interactable)
    //Setting up a wall for the ball to hit.
    Non_Interactable wall(world, b2Vec2(750.0f / SCALE, 500.0f / SCALE), 10.0f, 80.0f, sf::Color::Red, "");


    //Rather than having an immovable wall, we can use the dynamic body type to create one that can have velocity etc.
    b2BodyDef b2_plankDef;

    b2_plankDef.type = b2_dynamicBody;
    b2_plankDef.position.Set(550.0f / SCALE, 450.0f / SCALE);
    b2Body* b2_plankBody = world.CreateBody(&b2_plankDef);

    b2PolygonShape b2_plankBox;
    b2_plankBox.SetAsBox(10.0f / SCALE, 60.0f / SCALE);

    b2FixtureDef b2_plankFixture;
    b2_plankFixture.shape = &b2_plankBox;
    b2_plankFixture.density = 1.5f;   // Light wood
    b2_plankFixture.friction = 0.3f;
    b2_plankBody->CreateFixture(&b2_plankFixture);

    sf::RectangleShape sf_plankVisual(sf::Vector2f(20.0f, 120.0f));
    sf_plankVisual.setOrigin(10.0f, 60.0f);
    sf_plankVisual.setFillColor(sf::Color(139, 69, 19)); // Brown

    // BIRD 
    //Create a bird that is fired when space is pressed. We need to first have a dynamic ball to do it.
    Bird bird(world, 100.0f, 500.0f, 15.0f);

    // --- 7. MAIN LOOP ---
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // INPUT HANDLING: Press SPACE to launch
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    bird.launch(); 
                }
            }
        }

        // Update Physics
        world.Step(1.0f / 60.0f, 8, 3);


        bird.update();

        //All of the visuals needs to be synced with the physics.
        sf_plankVisual.setPosition(b2_plankBody->GetPosition().x * SCALE, b2_plankBody->GetPosition().y * SCALE);
        sf_plankVisual.setRotation(b2_plankBody->GetAngle() * (180.0f / PI));

        //Render all of the content at each frame. Remember you need to clear the screen each iteration or artefacts remain.
        window.clear(sf::Color(135, 206, 235)); // Sky Blue

        ground.render(window);
        wall.render(window);
        window.draw(sf_plankVisual);
        bird.render(window);

        window.display();
    }

    return 0;
}