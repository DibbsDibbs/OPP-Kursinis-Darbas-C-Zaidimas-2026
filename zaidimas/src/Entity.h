#pragma once

#include <SFML/Graphics.hpp>

// Abstrakti baze visiems zaidimo objektams.
// Kiekvienas objektas privalo isigyvendinti update() ir draw().
class Entity
{
public:
	virtual ~Entity() = default;

	virtual void update()                        = 0;
	virtual void draw(sf::RenderWindow& window)  = 0;

	virtual sf::FloatRect getBounds() const      = 0;

	float getX() const { return m_x; }
	float getY() const { return m_y; }

protected:
	float m_x = 0.0f;
	float m_y = 0.0f;
};
