#pragma once

#include "Platform.h"

// Platforma kuri ismeta zaideju dvigubai auksciau
class SpringPlatform : public Platform
{
public:
	SpringPlatform(const sf::Texture& texture, float x, float y);

	void  draw(sf::RenderWindow& window) override;
	float getJumpVelocity() const override;

};
