#include "BreakingPlatform.h"

#include "defines.h"

#include <cstdlib>

BreakingPlatform::BreakingPlatform(const sf::Texture& texture, float x, float y)
	: Platform(texture, x, y), m_broken(false)
{
	m_sprite.setColor(sf::Color(255, 120, 120));
}

void BreakingPlatform::draw(sf::RenderWindow& window)
{
	if (!m_broken)
		window.draw(m_sprite);
}

void BreakingPlatform::onLand()
{
	m_broken = true;
}

bool BreakingPlatform::isActive() const
{
	return !m_broken;
}

void BreakingPlatform::reset(int index)
{
	m_broken = false;
	Platform::reset(index);
}

void BreakingPlatform::scrollBy(float dy)
{
	Platform::scrollBy(dy);

	// Reset broken state when platform wraps back from above screen
	if (m_y < 0.0f)
		m_broken = false;
}
