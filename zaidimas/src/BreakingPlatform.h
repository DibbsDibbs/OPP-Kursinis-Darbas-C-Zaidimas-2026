#pragma once

#include "Platform.h"

// Platforma kuri isnysta uzlipus ant jos
class BreakingPlatform : public Platform
{
public:
	BreakingPlatform(const sf::Texture& texture, float x, float y);

	void draw(sf::RenderWindow& window) override;

	void onLand() override;
	bool isActive() const override;
	void reset(int index) override;
	void scrollBy(float dy) override;

private:
	bool m_broken;
};
