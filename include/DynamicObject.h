#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "GameObject.h"
#include <string>

class DynamicObject : public GameObject {
protected:
	const float SCALE = 30.0f;
	const float PI = 3.1415927;

	b2Body* body;
	b2BodyDef b2_bodyDef;
	b2FixtureDef b2_fixtureDef;
	b2CircleShape b2_circleShape;
	std::string str_sprite;
	
public:
	DynamicObject() = default;
	~DynamicObject() = default;
	
	DynamicObject(b2World& world, b2Vec2 b2_Pos, std::string str_sprite);

	b2Body* getBody();

	virtual void render(sf::RenderWindow& window) {};
	virtual void update() {}
};
