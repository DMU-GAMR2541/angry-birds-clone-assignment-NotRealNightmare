#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "GameObject.h"

class DynamicObject : public GameObject {
protected:
	const float SCALE = 30.0f;
	const float PI = 3.1415927;

	b2Body* body;
	b2World* world;
	
public:
	DynamicObject() = default;
	~DynamicObject() = default;
	
	b2Body* getBody() { return body; }

	void initDynamicBody(b2World* worldRef, float x, float y, float halfWidth, float halfHeight, float density, float friction, float restitution) {
		world = worldRef;
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(x / SCALE, y / SCALE);
		body = worldRef->CreateBody(&bodyDef);

		b2PolygonShape shape;
		shape.SetAsBox(halfWidth / SCALE, halfHeight / SCALE);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = density;
		fixtureDef.friction = friction;
		fixtureDef.restitution = restitution;
		body->CreateFixture(&fixtureDef);

	}

	virtual void render(sf::RenderWindow& window) {};

};
