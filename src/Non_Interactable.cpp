#include "Non_Interactable.h"

Non_Interactable::Non_Interactable(b2World& world, b2Vec2 b2_Pos, float halfWidth, float halfHeight, sf::Color color, std::string str_sprite)
	: StaticObject(world, b2_Pos, halfWidth, halfHeight, str_sprite)
{
	sf_shape.setSize(sf::Vector2f(halfWidth * 2, halfHeight * 2));
	sf_shape.setOrigin(halfWidth, halfHeight);
	sf_shape.setFillColor(color);
}

void Non_Interactable::render(sf::RenderWindow& window) {
	sf_shape.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
	window.draw(sf_shape);
}

void Non_Interactable::update() {}