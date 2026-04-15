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

	if (m_y <= float(std::rand() % 10))
		m_broken = false;
}
