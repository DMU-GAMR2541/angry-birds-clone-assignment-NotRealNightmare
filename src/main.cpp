#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include "Non_Interactable.h"
#include "Bird.h"
#include "Pig.h"
#include "Plank.h"
#include "Catapult.h"
#include "ContactListener.h"
#include <memory>
#include <vector>
#include <list>
#include <set>

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

    // Create the listener instance.
    ContactListener contactListener;

    // Register it with the world
    world.SetContactListener(&contactListener);



    // PLANK
    //Rather than having an immovable wall, we can use the dynamic body type to create one that can have velocity etc.
    Plank plank(world, 550.0f, 550.0f, 10.0f, 60.0f, "../assets/Ang_Birds/plank1.png");

    // GROUND (Non-interactable)
    // WALL (Non-interactable)
    std::vector<std::shared_ptr<Non_Interactable>> vecNonInteractable;
    vecNonInteractable.push_back(std::make_shared<Non_Interactable>(world, b2Vec2(400.0f / SCALE, 590.0f / SCALE), 400.0f, 10.0f, sf::Color(34, 139, 34), ""));  // ground
    vecNonInteractable.push_back(std::make_shared<Non_Interactable>(world, b2Vec2(750.0f / SCALE, 500.0f / SCALE), 10.0f, 80.0f, sf::Color::Red, ""));  // wall


    // BIRD
    std::list<std::shared_ptr<Bird>> birdType;
    for (int i = 0; i < 4; i++) {
        BirdType type;
        
        if (i == 0) { type = BirdType::Red; }
        else if (i == 1) { type = BirdType::Chuck; }
        else if (i == 2) { type = BirdType::theBlues; }
        else { type = BirdType::Bomb; }

        birdType.push_back(std::make_shared<Bird>(world, 150.0f - (i * 40.0f), 540.0f, 15.0f, 5.0f, "../assets/Ang_Birds/Angry_Birds2.png", type));
    }


    for (auto& bird : birdType) {
        bird->getBody()->GetUserData().pointer = 100;
    }

    // PIG
    std::vector<std::shared_ptr<Pig>> vecPig;
    for (int i = 0; i < 4; i++) {
        PigType type;

        if (i == 0) { type = PigType::smallPig; }
        else if (i == 1) { type = PigType::mediumPig; }
        else if (i == 2) { type = PigType::corporalPig; }
        else { type = PigType::kingPing; }

        auto pig = std::make_shared<Pig>(world, 200.0f + (i * 120.0f), 455.0f, 20.0f, "../assets/Ang_Birds/Pigs.png", type, 100);
        // Give each pig a unique ID via user data (start from 10 so it's > 2)
        pig->getBody()->GetUserData().pointer = 3 + i;
        vecPig.push_back(pig);
    }

    
    Catapult catapult(world, 150.0f, 520.0f, 10.0f, 60.0f, "../assets/Ang_Birds/Slingshot.png");


    // --- 7. MAIN LOOP ---
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (!birdType.empty()) {
                    auto& currentBird = birdType.front();
                    
                    if (event.key.code == sf::Keyboard::B) {
                        world.DestroyBody(birdType.front()->getBody());
                        birdType.pop_front();
                    }

                    if (event.key.code == sf::Keyboard::Space) {
                        if (birdType.front()->getBirdType() == BirdType::Chuck) {
                            birdType.front()->chuckAbility(b2Vec2 (6.0f, 0.0f));
                        }
                        if (birdType.front()->getBirdType() == BirdType::theBlues) {
                            auto clones = birdType.front()->theBluesAbility(world);
                            for (auto& clone : clones) {
                                birdType.push_front(clone);
                            }
                        }
                    }
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (!birdType.empty()) {
                        birdType.front()->dragging();
                    }
                }
            }

            // Mouse released — launch bird
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (!birdType.empty() && birdType.front()->getDragging()) {
                        birdType.front()->launch(catapult.getShotPos());
                    }
                }
            }
           
        }

        if (!birdType.empty() && birdType.front()->getDragging()) {

            // gets position of the mouse in sfml pixels.
            sf::Vector2i mousePxl = sf::Mouse::getPosition(window);
            // takes x and y position of the mouse.
            sf::Vector2f mouseWorld(mousePxl.x, mousePxl.y);

            // stores the drag of the mouse position and the start position.
            sf::Vector2f dragVec(mouseWorld - catapult.getShotPos());

            // stops player dragging towards the right
            if (dragVec.x > 0) {
                dragVec.x = 0;
            }

            // stops player dragging upwards
            if (dragVec.y < 0) {
                dragVec.y = 0;
            }

            // makes a distance for how much you can drag, preventing player from dragging out of the screen.
            float length = std::sqrt(dragVec.x * dragVec.x + dragVec.y * dragVec.y);
            float maxDrag = 100.0f;

            if (length > maxDrag) {
                dragVec /= length;
                dragVec *= maxDrag;
            }

            // moves the bird to the catapults position when dragging.
            sf::Vector2f finalPos = catapult.getShotPos() + dragVec;

            birdType.front()->getBody()->SetTransform(b2Vec2(finalPos.x / SCALE, finalPos.y / SCALE), 0);
            birdType.front()->dragging();
        }

        // Update Physics
        world.Step(1.0f / 60.0f, 8, 3);

        

        // Check contact listener for hit pigs and destroy them
        std::set<uintptr_t> s_p = contactListener.getPointer();
        for (auto itPig = vecPig.begin(); itPig != vecPig.end(); ) {
            uintptr_t currentPigID = (*itPig)->getBody()->GetUserData().pointer;

            // Check if this pig's ID exists in the hit list
            if (s_p.find(currentPigID) != s_p.end()) {
                std::cout << currentPigID << " Destroyed" << std::endl;

                // Remove from Box2D world first
                world.DestroyBody((*itPig)->getBody());

                // Update iterator by catching return value of erase
                itPig = vecPig.erase(itPig);
            }
            else {
                // Only increment if we didn't erase anything
                ++itPig;
            }
        }


        plank.update();
        catapult.update();

        for (std::list<std::shared_ptr<Bird>>::iterator itBird = birdType.begin(); itBird != birdType.end(); itBird++) {
            (*itBird)->update();
        }

        for (std::vector<std::shared_ptr<Pig>>::iterator itPig = vecPig.begin(); itPig != vecPig.end(); itPig++) {
            (*itPig)->update();
        }
        
        

        //Render all of the content at each frame. Remember you need to clear the screen each iteration or artefacts remain.
        window.clear(sf::Color(135, 206, 235)); // Sky Blue

    
        plank.render(window);

        for (std::vector<std::shared_ptr<Non_Interactable>>::iterator itNonInteractable = vecNonInteractable.begin(); itNonInteractable != vecNonInteractable.end(); itNonInteractable++) {
            (*itNonInteractable)->render(window);
        }

        for (std::list<std::shared_ptr<Bird>>::iterator itBird = birdType.begin(); itBird != birdType.end(); itBird++) {
            (*itBird)->render(window);
        }

        for (std::vector<std::shared_ptr<Pig>>::iterator itPig = vecPig.begin(); itPig != vecPig.end(); itPig++) {
            (*itPig)->render(window);
        }

        
        catapult.render(window);

        window.display();


    }
    return 0;
}