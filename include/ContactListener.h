#pragma once
#include "DynamicObject.h"
#include <box2d/box2d.h>
#include <iostream>
#include <list>
#include <set>

/// \brief Custom contact listener to handle collision events in Box2D. Overrides the default contact listener to provide custom behaviour when collisions occur.

class ContactListener : public b2ContactListener {

public:
    std::set<uintptr_t> s_ptr;

    ContactListener() = default;

    // Called when two fixtures begin to touch
    void BeginContact(b2Contact* contact) override {
        // Get the two fixtures involved
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();

        uintptr_t ptrA = fixtureA->GetBody()->GetUserData().pointer;
        uintptr_t ptrB = fixtureB->GetBody()->GetUserData().pointer;

        if (fixtureA->GetBody()->GetUserData().pointer == 100 && fixtureB->GetBody()->GetUserData().pointer > 2) {
            s_ptr.insert(fixtureB->GetBody()->GetUserData().pointer);
            std::cout << fixtureA->GetBody()->GetUserData().pointer << " and " << fixtureB->GetBody()->GetUserData().pointer << " hit " << std::endl;
        }

        if (ptrB == 100 && ptrA > 2) {
            s_ptr.insert(ptrA);
            std::cout << ptrB << " and " << ptrA << " hit" << std::endl;
        }
    }

    // Called when two fixtures cease to touch
    void EndContact(b2Contact* contact) override {
     
    }

    std::set<uintptr_t> getPointer() {
        return s_ptr;
    }

};