#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "GameObject.h"

class DynamicObject : public GameObject {
	DynamicObject() = default;
	~DynamicObject() = default;


public:
	const float SCALE = 30.0f;
	const float PI = 3.1415927;

	b2World world;

	b2BodyDef b2_wallDef;
	b2PolygonShape b2_wallBox;
	b2BodyDef b2_plankDef;
	b2PolygonShape b2_plankBox;
	b2FixtureDef b2_plankFixture;
	b2BodyDef b2_ballDef;


};
