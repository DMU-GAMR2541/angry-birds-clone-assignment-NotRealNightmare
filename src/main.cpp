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
#include "UI.h"

int main() {
    // --- 1. WINDOW SETUP ---
    sf::RenderWindow window(sf::VideoMode(800, 600), "Annoyed_Flocks");
    window.setFramerateLimit(60);

    //Box2D works in meters. SFML works in pixels.
    const float SCALE = 30.0f;

    //Can set a definition for PI.
    const float PI = 3.1415927;

    UI loadingScreen("../assets/Ang_Birds/LoadingScreen.png", 0.0f, 0.0f);


    bool gameStarted = false;
    while (!gameStarted && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    gameStarted = true;
                }
            }
        }
        window.clear();
        loadingScreen.render(window);
        window.display();
    }

    //setup world.
    b2Vec2 b2_gravity(0.0f, 9.8f); // Earth-like gravity
    b2World world(b2_gravity);

    // Create the listener instance.
    ContactListener contactListener;

    // Register it with the world
    world.SetContactListener(&contactListener);



    // PLANK
    //Rather than having an immovable wall, we can use the dynamic body type to create one that can have velocity etc.
    //Plank plank(world, 550.0f, 550.0f, 10.0f, 60.0f, "../assets/Ang_Birds/plank1.png");
    
    std::vector<std::shared_ptr<Plank>> vecPlank;

    vecPlank.push_back(std::make_shared<Plank>(world, 500.0f, 530.0f, 8.0f, 40.0f, "../assets/Ang_Birds/plank1.png"));  // pV1
    vecPlank.push_back(std::make_shared<Plank>(world, 600.0f, 530.0f, 8.0f, 40.0f, "../assets/Ang_Birds/plank1.png"));  // pV2
    vecPlank.push_back(std::make_shared<Plank>(world, 550.0f, 482.0f, 58.0f, 15.0f, "../assets/Ang_Birds/plank2.png")); // pH
    vecPlank.push_back(std::make_shared<Plank>(world, 500.0f, 420.0f, 8.0f, 28.0f, "../assets/Ang_Birds/plank1.png")); // pTopV1
    vecPlank.push_back(std::make_shared<Plank>(world, 600.0f, 420.0f, 8.0f, 28.0f, "../assets/Ang_Birds/plank1.png")); // pTopV2

    for (int i = 0; i < vecPlank.size(); i++) {
        vecPlank[i]->getBody()->GetUserData().pointer = 10 + i;
    }

    // GROUND (Non-interactable)
    // WALL (Non-interactable)
    std::vector<std::shared_ptr<Non_Interactable>> vecNonInteractable;
    vecNonInteractable.push_back(std::make_shared<Non_Interactable>(world, b2Vec2(400.0f / SCALE, 590.0f / SCALE), 400.0f, 10.0f, sf::Color(34, 139, 34), ""));  // ground
    vecNonInteractable.push_back(std::make_shared<Non_Interactable>(world, b2Vec2(750.0f / SCALE, 500.0f / SCALE), 10.0f, 80.0f, sf::Color::Red, ""));  // wall
    vecNonInteractable.push_back(std::make_shared<Non_Interactable>(world, b2Vec2(550.0f / SCALE, 325.0f / SCALE), 40.0f, 8.0f, sf::Color(139, 69, 19), ""));

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
    float xPositions[4] = { 550.0f, 550.0f, 390.0f, 550.0f };
    float yPositions[4] = { 455.0f, 510.0f, 555.0f, 310.0f };

    std::vector<std::shared_ptr<Pig>> vecPig;
    for (int i = 0; i < 4; i++) {
        PigType type;

        if (i == 0) { type = PigType::smallPig; }
        else if (i == 1) { type = PigType::mediumPig; }
        else if (i == 2) { type = PigType::corporalPig; }
        else { type = PigType::kingPig; }

        int health;
        if (i == 0) health = 50;
        else if (i == 1) health = 100;
        else if (i == 2) health = 150;
        else health = 200;

        float radius;
        if (i == 0)      radius = 12.0f;
        else if (i == 1) radius = 17.0f;
        else if (i == 2) radius = 20.0f;
        else             radius = 25.0f;

        auto pig = std::make_shared<Pig>(world, xPositions[i], yPositions[i], radius, "../assets/Ang_Birds/Pigs.png", type, health);
        // Give each pig a unique ID via user data (start from 10 so it's > 2)
        pig->getBody()->GetUserData().pointer = 3 + i;
        vecPig.push_back(pig);
    }

    
    Catapult catapult(world, 200.0f, 540.0f, 10.0f, 60.0f, "../assets/Ang_Birds/Slingshot.png");

    UI ui("../assets/Ang_Birds/LoadingScreen.png", 0.0f, 0.0f);
    ui.updatePigCount(vecPig.size());

    std::shared_ptr<Bird> lastLaunchedBird = nullptr;
    bool gameOver = false;
    // --- 7. MAIN LOOP ---
    while (window.isOpen() && !gameOver) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space && lastLaunchedBird != nullptr) {

                    if (lastLaunchedBird->getBirdType() == BirdType::Chuck) {
                        lastLaunchedBird->chuckAbility(b2Vec2(6.0f, 0.0f));
                    }

                    if (lastLaunchedBird->getBirdType() == BirdType::theBlues) {
                        auto clones = lastLaunchedBird->theBluesAbility(world);
                        for (auto& clone : clones) {
                            birdType.push_back(clone);
                        }
                    }

                    if (lastLaunchedBird->getBirdType() == BirdType::Bomb && !lastLaunchedBird->hasUsedAbility()) {
                        auto Bomb = lastLaunchedBird->bombAbility(world, 1.5f, vecPig);
                        world.DestroyBody(lastLaunchedBird->getBody());
                        birdType.remove(lastLaunchedBird);
                        lastLaunchedBird = nullptr;
                        for (auto& bird : Bomb) {
                            birdType.push_front(bird);
                        }
                    }
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (!birdType.empty() && !birdType.front()->getIsLaunched()) {
                    birdType.front()->dragging();
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (!birdType.empty() && birdType.front()->getDragging() && !birdType.front()->getIsLaunched()) {
                        birdType.front()->launch(catapult.getShotPos());
                        birdType.front()->setDestructionTime(3.0f);

                        lastLaunchedBird = birdType.front();

                        auto launchedBird = birdType.front();
                        birdType.pop_front();
                        birdType.push_back(launchedBird);
                    }
                }
            }
        }

        if (!birdType.empty() && birdType.front()->getDragging() && !birdType.front()->getIsLaunched()) {
            // gets position of the mouse in sfml pixels.
            sf::Vector2i mousePxl = sf::Mouse::getPosition(window);
            // takes x and y position of the mouse.
            sf::Vector2f mouseWorld(mousePxl.x, mousePxl.y);

            // stores the drag of the mouse position and the start position.
            sf::Vector2f dragVec(mouseWorld - catapult.getShotPos());

            // will stop players dragging towards the right
            // will stop players dragging upwards
            if (dragVec.x > 0) dragVec.x = 0;
            //if (dragVec.y < -30.0f) dragVec.y = -30.0f;

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
        std::set<uintptr_t>& s_p = contactListener.s_ptr;
        for (auto itPig = vecPig.begin(); itPig != vecPig.end(); ) {

            uintptr_t currentPigID = (*itPig)->getBody()->GetUserData().pointer;

            if (s_p.find(currentPigID) != s_p.end()) {
                if (!(*itPig)->isMarkedForDeletion()) {
                    std::cout << "Pig has: " << (*itPig)->getHealth() << "  Health" << std::endl;
                    
                    Pig* pigPtr = dynamic_cast<Pig*>((*itPig).get());
                    if (pigPtr) {
                        pigPtr->takeDamage(50);
                    }

                    s_p.erase(currentPigID);
                    if ((*itPig)->checkIfPopped()) {
                        std::cout << currentPigID << " Destroyed" << std::endl;
                        (*itPig)->markForDeletion();
                        world.DestroyBody((*itPig)->getBody());
                        itPig = vecPig.erase(itPig);
                        ui.updatePigCount(vecPig.size());
                        continue;
                    }
                }
                ++itPig;
            }
            else {
                ++itPig;
            }
        }

        for (auto itPlank = vecPlank.begin(); itPlank != vecPlank.end(); ) {
            uintptr_t currentPlankID = (*itPlank)->getBody()->GetUserData().pointer;
            if (s_p.find(currentPlankID) != s_p.end()) {
                std::cout << currentPlankID << " Plank Destroyed" << std::endl;
                world.DestroyBody((*itPlank)->getBody());
                itPlank = vecPlank.erase(itPlank);
            }
            else {
                ++itPlank;
            }
        }

        for (auto itBird = birdType.begin(); itBird != birdType.end(); ) {
            if ((*itBird)->shouldDelete()) {
                world.DestroyBody((*itBird)->getBody());
                itBird = birdType.erase(itBird);
            }
            else {
                ++itBird;
            }
        }

        if (vecPig.empty()) {
            gameOver = true;
        }

        //plank.update();
       

        catapult.update();

        for (auto itPlank = vecPlank.begin(); itPlank != vecPlank.end(); itPlank++) {
            (*itPlank)->update();
        }

        for (std::list<std::shared_ptr<Bird>>::iterator itBird = birdType.begin(); itBird != birdType.end(); itBird++) {
            (*itBird)->update();
        }

        for (std::vector<std::shared_ptr<Pig>>::iterator itPig = vecPig.begin(); itPig != vecPig.end(); itPig++) {
            (*itPig)->update();
        }



        //Render all of the content at each frame. Remember you need to clear the screen each iteration or artefacts remain.
        window.clear(sf::Color(135, 206, 235)); // Sky Blue


        //plank.render(window);
     
        for (auto itPlank = vecPlank.begin(); itPlank != vecPlank.end(); itPlank++) {
            (*itPlank)->render(window);
        }

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

        ui.renderHUD(window);

        window.display();
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    window.close();
                }
            }
        }
        window.clear(sf::Color(135, 206, 235));
        ui.renderWin(window);
        window.display();
    }


    return 0;
}