#pragma once

#include "Platform.h"

// Platforma kuri juda kairyn ir desinen
class MovingPlatform : public Platform
{
public:
	MovingPlatform(const sf::Texture& texture, float x, float y, float speed);

	void update() override;

private:
	float m_moveSpeed;
	float m_moveDir;
};
