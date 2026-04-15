#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

#include "defines.h"
#include "objects.h"
#include "Enemy.h"
#include "Platform.h"
#include "BreakingPlatform.h"
#include "MovingPlatform.h"
#include "SpringPlatform.h"

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

	Player                   m_player;
	std::vector<Platform*>   m_platforms;
	Enemy*                   m_enemy;

	float     m_dy;
	float     m_score;
	GameState m_state;
};
