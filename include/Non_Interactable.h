#pragma once
#include "StaticObject.h"

class Non_Interactable : public StaticObject {
private:
	sf::RectangleShape sf_shape;

public:
	Non_Interactable(b2World& world, b2Vec2 b2_Pos, float halfWidth, float halfHeight, sf::Color color, std::string str_sprite);
	~Non_Interactable() = default;

	void render(sf::RenderWindow& window) override;
	void update() override;
};