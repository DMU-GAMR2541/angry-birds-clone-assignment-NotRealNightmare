#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include "DynamicObject.h"
#include "StaticObject.h"

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

    
    //GROUND (StaticObject)
    //Setup ground for the circle to move / bounce on.  
    StaticObject ground;
    ground.initStaticBody(&world, 400.0f, 590.0f, 400.0f, 10.0f);
    //set up the ground visualisation
    sf::RectangleShape sf_groundVisual(sf::Vector2f(800.0f, 20.0f));
    sf_groundVisual.setOrigin(400.0f, 10.0f);
    sf_groundVisual.setFillColor(sf::Color(34, 139, 34)); // Forest Green

    

    // WALL (StaticObject)
    //Setup wall for the ball to hit
    StaticObject wall;
    wall.initStaticBody(&world, 750.0f, 500.0f, 10.0f, 80.0f);
    //set up the wall visualisation
    sf::RectangleShape sf_wallVisual(sf::Vector2f(20.0f, 160.0f));
    sf_wallVisual.setOrigin(10.0f, 80.0f);
    sf_wallVisual.setFillColor(sf::Color::Red);

    // PLANK (DynamicObject)
    //Setup plank, rather than having an immovable wall, we can use the dynamic body type to create one that can have velocity etc.
    DynamicObject plank;
    plank.initDynamicBody(&world, 550.0f, 450.0f, 10.0f, 60.0f, 1.5f, 0.3f, 0.0f);
    sf::RectangleShape sf_plankVisual(sf::Vector2f(20.0f, 120.0f));
    sf_plankVisual.setOrigin(10.0f, 60.0f);
    sf_plankVisual.setFillColor(sf::Color(139, 69, 19)); // Brown
    
    // BALL (DynamicObject)
    //Create a ball that is fired when space is pressed. We need to first have a dynamic ball to do it.
    DynamicObject ball;
    ball.initDynamicBody(&world, 100.0f, 500.0f, 15.0f, 15.0f, 1.0f, 0.0f, 0.5f);
    sf::CircleShape sf_ballVisual(15.0f);
    sf_ballVisual.setOrigin(15.0f, 15.0f);
    sf_ballVisual.setFillColor(sf::Color::Yellow);
   
    // --- 7. MAIN LOOP ---
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // INPUT HANDLING: Press SPACE to launch
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    // Reset position of the ball so that it can be fired again from its original poisition.
                    ball.getBody()->SetTransform(b2Vec2(100.0f / 30.0f, 500 / 30.0f), 0);
                    ball.getBody()->SetLinearVelocity(b2Vec2(0, 0));
                    ball.getBody()->SetAngularVelocity(0);

                    // Apply impulse (X-axis, Y-axis) Negative Y is UP in Box2D because gravity is positive.
                    ball.getBody()->ApplyLinearImpulse(b2Vec2(5.0f, -5.0f), ball.getBody()->GetWorldCenter(), true);

                    std::cout << "Firing!!!!" << std::endl;
                }
            }
        }

        // Update Physics
        world.Step(1.0f / 60.0f, 8, 3);

        //All of the visuals needs to be synced with the physics.

        //Static
        sf_groundVisual.setPosition(ground.getBody()->GetPosition().x * 30.0f, ground.getBody()->GetPosition().y * 30.0f);
        sf_wallVisual.setPosition(wall.getBody()->GetPosition().x * 30.0f, wall.getBody()->GetPosition().y * 30.0f);

        //Dynamic
        sf_plankVisual.setPosition(plank.getBody()->GetPosition().x * 30.0f, plank.getBody()->GetPosition().y * 30.0f);
        sf_plankVisual.setRotation(plank.getBody()->GetAngle() * (180.0f / PI));

        sf_ballVisual.setPosition(ball.getBody()->GetPosition().x * 30.0f, ball.getBody()->GetPosition().y * 30.0f);
        sf_ballVisual.setRotation(ball.getBody()->GetAngle() * (180.0f / PI));


        //Render all of the content at each frame. Remember you need to clear the screen each iteration or artefacts remain.
        window.clear(sf::Color(135, 206, 235)); // Sky Blue

        window.draw(sf_groundVisual);
        window.draw(sf_wallVisual);
        window.draw(sf_plankVisual);
        window.draw(sf_ballVisual);

        window.display();
    }

    return 0;
}