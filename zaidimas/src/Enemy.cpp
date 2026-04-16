#include "Enemy.h"

#include "defines.h"

#include <cmath>
#include <cstdlib>

static const float ENEMY_RADIUS    = 18.0f;
static const float VISION_DISTANCE = 130.0f;

Enemy::Enemy(float x, float y, float speed)
	: m_speed(speed), m_direction(1.0f)
{
	m_x = x;
	m_y = y;

	m_shape.setRadius(ENEMY_RADIUS);
	m_shape.setFillColor(sf::Color(200, 40, 40));
	m_shape.setOutlineColor(sf::Color::Black);
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
	m_shape.setOutlineColor(sf::Color::Black);
	m_shape.setOutlineThickness(1.5f);
	m_shape.setPosition(m_x, m_y);
}

void Enemy::update()
{
	m_x += m_speed * m_direction;

	if (m_x <= 0.0f || m_x >= WINDOW_WIDTH - ENEMY_RADIUS * 2)
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
		m_y = -float(std::rand() % 80 + 20);
		m_x = float(std::rand() % (WINDOW_WIDTH - int(ENEMY_RADIUS * 2)));
	}

	m_shape.setPosition(m_x, m_y);
}

void Enemy::chasePlayer(float playerX)
{
	const float distance = std::abs(playerX - m_x);

	if (distance < VISION_DISTANCE)
	{
		const float chaseDir = (playerX > m_x) ? 1.0f : -1.0f;
		m_x += m_speed * chaseDir * 1.8f;
		m_shape.setFillColor(sf::Color(255, 60, 0));
	}
	else
	{
		m_shape.setFillColor(sf::Color(200, 40, 40));
	}

	m_shape.setPosition(m_x, m_y);
}
