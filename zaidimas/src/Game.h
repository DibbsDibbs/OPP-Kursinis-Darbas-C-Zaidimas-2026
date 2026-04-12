#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "defines.h"
#include "objects.h"
#include "Platform.h"

class Game
{
public:
	Game();
	~Game();

	void run();

private:
	void processEvents();
	void update();
	void draw();
	void reset();

	sf::RenderWindow m_window;

	sf::Texture m_tBackground;
	sf::Texture m_tPlayer1;
	sf::Texture m_tPlayer2;
	sf::Texture m_tPlatform;
	sf::Font    m_font;

	sf::Sprite m_sprBackground;
	sf::Sprite m_sprPlayer;
	sf::Sprite m_sprPlatform;

	sf::Text m_scoreText;
	sf::Text m_gameOverText;
	sf::Text m_restartText;

	Player   m_player;
	Platform* m_platforms[PLATES_AMOUNT];

	float     m_dy;
	float     m_score;
	GameState m_state;
};
