#include "SpringPlatform.h"

#include "defines.h"

SpringPlatform::SpringPlatform(const sf::Texture& texture, float x, float y)
	: Platform(texture, x, y)
{
	m_sprite.setColor(sf::Color(120, 255, 140));
}

void SpringPlatform::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

float SpringPlatform::getJumpVelocity() const
{
	return PLAYER_JUMP_V * 1.9f;
}
