#pragma once

#include "Entity.h"

class Platform : public Entity
{
public:
	Platform(const sf::Texture& texture, float x, float y);

	void update() override;
	void draw(sf::RenderWindow& window) override;
	sf::FloatRect getBounds() const override;

	void scrollBy(float dy);
	void reset(int index);

	float StartX()  const;
	float EndX()    const;
	float TopY()    const;
	float BottomY() const;

private:
	sf::Sprite m_sprite;
};
