#include "Platform.h"

#include "defines.h"

#include <cstdlib>

Platform::Platform(const sf::Texture& texture, float x, float y)
{
	m_x = x;
	m_y = y;
	m_sprite.setTexture(texture);
	m_sprite.setPosition(m_x, m_y);
}

void Platform::update()
{
	m_sprite.setPosition(m_x, m_y);
}

void Platform::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

sf::FloatRect Platform::getBounds() const
{
	return m_sprite.getGlobalBounds();
}

void Platform::scrollBy(float dy)
{
	m_y -= dy;

	if (m_y > WINDOW_HEIGHT)
	{
		m_y = float(std::rand() % 10);
		m_x = float(std::rand() % (WINDOW_WIDTH - PLATES_WIDTH));
	}

	m_sprite.setPosition(m_x, m_y);
}

void Platform::reset(int index)
{
	m_x = float(std::rand() % (WINDOW_WIDTH - PLATES_WIDTH));
	m_y = float(WINDOW_HEIGHT) / PLATES_AMOUNT * index;
	m_sprite.setPosition(m_x, m_y);
}

float Platform::getJumpVelocity() const { return PLAYER_JUMP_V; }
void  Platform::onLand() {}
bool  Platform::isActive() const { return true; }

float Platform::StartX()  const { return m_x; }
float Platform::EndX()    const { return m_x + PLATES_WIDTH; }
float Platform::TopY()    const { return m_y; }
float Platform::BottomY() const { return m_y + PLATES_HEIGHT; }
