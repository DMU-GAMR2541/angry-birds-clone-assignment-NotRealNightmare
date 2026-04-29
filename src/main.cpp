#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include "Non_Interactable.h"
#include "Bird.h"
#include "Pig.h"
#include "Plank.h"

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

    // PLANK
    //Rather than having an immovable wall, we can use the dynamic body type to create one that can have velocity etc.
    Plank plank(world, 550.0f, 550.0f, 10.0f, 60.0f, "../assets/Ang_Birds/plank1.png");

    // BIRD 
    //Create a bird that is fired when space is pressed. We need to first have a dynamic ball to do it.
    Bird bird(world, 100.0f, 150.0f, 15.0f, "../assets/Ang_Birds/redbord.png");

    // PIG
    Pig pig(world, 400.0f, 200.0f, 20.0f, "../assets/Ang_Birds/Pig.png", 100);

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
        pig.update();

        plank.update();
        

        //Render all of the content at each frame. Remember you need to clear the screen each iteration or artefacts remain.
        window.clear(sf::Color(135, 206, 235)); // Sky Blue

        ground.render(window);
        wall.render(window);
        plank.render(window);
        bird.render(window);
        pig.render(window);

        window.display();
    }

    return 0;
}