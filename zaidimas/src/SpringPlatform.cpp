#include "SpringPlatform.h"

#include "defines.h"

SpringPlatform::SpringPlatform(const sf::Texture& texture, float x, float y)
	: Platform(texture, x, y)
{
	m_sprite.setColor(sf::Color(120, 255, 140));

	m_spring.setRadius(6.0f);
	m_spring.setFillColor(sf::Color(255, 220, 0));
	m_spring.setOutlineColor(sf::Color(180, 140, 0));
	m_spring.setOutlineThickness(1.0f);
}

void SpringPlatform::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);

	m_spring.setPosition(m_x + PLATES_WIDTH / 2.0f - 6.0f, m_y - 12.0f);
	window.draw(m_spring);
}

float SpringPlatform::getJumpVelocity() const
{
	return PLAYER_JUMP_V * 1.9f;
}
