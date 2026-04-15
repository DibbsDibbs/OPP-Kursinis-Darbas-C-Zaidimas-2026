#pragma once

#include "Entity.h"

class Platform : public Entity
{
public:
	Platform(const sf::Texture& texture, float x, float y);

	void update() override;
	void draw(sf::RenderWindow& window) override;
	sf::FloatRect getBounds() const override;

	virtual void scrollBy(float dy);
	virtual void reset(int index);

	virtual float getJumpVelocity() const;
	virtual void  onLand();
	virtual bool  isActive() const;

	float StartX()  const;
	float EndX()    const;
	float TopY()    const;
	float BottomY() const;

protected:
	sf::Sprite m_sprite;
};
