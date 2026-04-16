#pragma once

#include "Entity.h"

class Enemy : public Entity
{
public:
	Enemy(float x, float y, float speed);
	Enemy(const Enemy& other);

	void update() override;
	void draw(sf::RenderWindow& window) override;
	sf::FloatRect getBounds() const override;

	void scrollBy(float dy);

private:
	sf::CircleShape m_shape;
	float m_speed;
	float m_direction;
};
