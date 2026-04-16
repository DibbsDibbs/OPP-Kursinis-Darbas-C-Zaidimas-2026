#include "Enemy.h"

#include "defines.h"

#include <cstdlib>

static const float ENEMY_RADIUS = 10.0f;

Enemy::Enemy(float x, float y, float speed)
	: m_speed(speed), m_direction(1.0f)
{
	m_x = x;
	m_y = y;

	m_shape.setRadius(ENEMY_RADIUS);
	m_shape.setFillColor(sf::Color(220, 50, 50));
	m_shape.setOutlineColor(sf::Color(120, 0, 0));
	m_shape.setOutlineThickness(1.5f);
	m_shape.setPosition(m_x, m_y);
}

Enemy::Enemy(const Enemy& other)
	: m_speed(other.m_speed), m_direction(other.m_direction)
{
	m_x = other.m_x;
	m_y = other.m_y;

	m_shape.setRadius(ENEMY_RADIUS);
	m_shape.setFillColor(other.m_shape.getFillColor());
	m_shape.setOutlineColor(sf::Color(120, 0, 0));
	m_shape.setOutlineThickness(1.5f);
	m_shape.setPosition(m_x, m_y);
}

void Enemy::update()
{
	m_x += m_speed * m_direction;

	if (m_x <= 0.0f || m_x >= float(WINDOW_WIDTH) - ENEMY_RADIUS * 2)
		m_direction *= -1.0f;

	m_shape.setPosition(m_x, m_y);
}

void Enemy::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}

sf::FloatRect Enemy::getBounds() const
{
	return m_shape.getGlobalBounds();
}

void Enemy::scrollBy(float dy)
{
	m_y -= dy;

	if (m_y > WINDOW_HEIGHT)
	{
		// Reappear at a random position above the screen
		m_y = -float(std::rand() % (WINDOW_HEIGHT / 2) + 40);
		m_x = float(std::rand() % (WINDOW_WIDTH - int(ENEMY_RADIUS * 2)));
		m_direction = (std::rand() % 2 == 0) ? 1.0f : -1.0f;
	}

	m_shape.setPosition(m_x, m_y);
}
