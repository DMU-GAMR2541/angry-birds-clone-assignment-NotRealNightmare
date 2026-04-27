#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "GameObject.h"

class StaticObject : public GameObject {
protected:
	const float SCALE = 30.0f;
	const float PI = 3.1415927;


	b2Body* body;
	b2World* world;

public:
	StaticObject() = default;
	~StaticObject() = default;

	b2Body* getBody() { return body; }

	void initStaticBody(b2World* worldRef, float x, float y, float halfWidth, float halfHeight) {
		world = worldRef;
		b2BodyDef bodyDef;
		bodyDef.position.Set(x / SCALE, y / SCALE);
		body = worldRef->CreateBody(&bodyDef);

		b2PolygonShape shape;
		shape.SetAsBox(halfWidth / SCALE, halfHeight / SCALE);
		body->CreateFixture(&shape, 0.0f);

	}

	virtual void render(sf::RenderWindow& window) {};
};