#include "MovingPlatform.h"

#include "defines.h"

MovingPlatform::MovingPlatform(const sf::Texture& texture, float x, float y, float speed)
	: Platform(texture, x, y), m_moveSpeed(speed), m_moveDir(1.0f)
{
	m_sprite.setColor(sf::Color(120, 180, 255));
}

void MovingPlatform::update()
{
	m_x += m_moveSpeed * m_moveDir;

	if (m_x <= 0.0f || m_x >= float(WINDOW_WIDTH - PLATES_WIDTH))
		m_moveDir *= -1.0f;

	m_sprite.setPosition(m_x, m_y);
}
