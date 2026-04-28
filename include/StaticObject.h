#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "GameObject.h"
#include <string>

class StaticObject : public GameObject {
protected:
	const float SCALE = 30.0f;
	const float PI = 3.1415927;


	b2Body* body;
	b2BodyDef b2_bodyDef;
	b2PolygonShape b2_shape;
	b2FixtureDef b2_fixtureDef;
	std::string str_sprite;

public:
	StaticObject() = default;
	~StaticObject() = default;

	StaticObject(b2World& world, b2Vec2 b2_Pos, float halfWidth, float halfHeight, std::string str_sprite);

	b2Body* getBody();

	virtual void render(sf::RenderWindow& window) {};
	virtual void update() {}
};