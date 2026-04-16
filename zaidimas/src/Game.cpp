#include "Game.h"
#include "utils.h"

#include <cstdlib>
#include <ctime>
#include <string>

Game::Game()
	: m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Doodle Jump"),
	m_sprBackground(m_tBackground),
	m_sprPlayer(m_tPlayer1),
	m_dy(0.0f),
	m_score(0.0f),
	m_state(GameState::Playing)
{
	std::srand(static_cast<unsigned>(std::time(nullptr)));
	m_window.setFramerateLimit(60);

	m_tBackground.loadFromFile("resources/background.png");
	m_tPlayer1.loadFromFile("resources/doodle1.png");
	m_tPlayer2.loadFromFile("resources/doodle2.png");
	m_tPlatform.loadFromFile("resources/platform.png");
	m_font.loadFromFile("resources/arialbd.ttf");

	m_sprBackground.setTexture(m_tBackground);
	m_sprPlayer.setTexture(m_tPlayer1);

	m_scoreText.setFont(m_font);
	m_scoreText.setCharacterSize(40);
	m_scoreText.setFillColor(sf::Color::Red);
	m_scoreText.setOutlineThickness(1);
	m_scoreText.setOutlineColor(sf::Color::Black);
	m_scoreText.setPosition(WINDOW_WIDTH / 2.0f - 25.f, 10.f);

	m_gameOverText.setFont(m_font);
	m_gameOverText.setString("Game Over");
	m_gameOverText.setCharacterSize(52);
	m_gameOverText.setFillColor(sf::Color::White);
	m_gameOverText.setOutlineThickness(2);
	m_gameOverText.setOutlineColor(sf::Color::Black);
	m_gameOverText.setPosition(70.f, 180.f);

	m_restartText.setFont(m_font);
	m_restartText.setString("Press R to restart");
	m_restartText.setCharacterSize(26);
	m_restartText.setFillColor(sf::Color::Yellow);
	m_restartText.setOutlineThickness(1);
	m_restartText.setOutlineColor(sf::Color::Black);
	m_restartText.setPosition(85.f, 250.f);

	m_platforms.reserve(PLATES_AMOUNT);
	for (int i = 0; i < PLATES_AMOUNT; ++i)
	{
		const int type = i % 5;
		if (type == 1)
			m_platforms.push_back(new BreakingPlatform(m_tPlatform, 0.0f, 0.0f));
		else if (type == 2)
			m_platforms.push_back(new MovingPlatform(m_tPlatform, 0.0f, 0.0f, 1.8f));
		else if (type == 3)
			m_platforms.push_back(new SpringPlatform(m_tPlatform, 0.0f, 0.0f));
		else
			m_platforms.push_back(new Platform(m_tPlatform, 0.0f, 0.0f));
	}

	m_enemy = new Enemy(20.0f, 400.0f, 1.5f);

	reset();
}

Game::~Game()
{
	for (Platform* p : m_platforms)
		delete p;

	delete m_enemy;
}

void Game::run()
{
	while (m_window.isOpen())
	{
		processEvents();
		update();
		draw();
	}
}

void Game::processEvents()
{
	sf::Event e;
	while (m_window.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
			m_window.close();
	}

	if (m_state == GameState::GameOver)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			reset();
			m_state = GameState::Playing;
		}
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
		m_sprPlayer.setTexture(m_tPlayer1);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
	{
		m_sprPlayer.setTexture(m_tPlayer2);
		m_dy -= 0.21f;
	}
}

void Game::update()
{
	if (m_state == GameState::GameOver)
		return;

	const float dx = 3.5f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_player.move(-dx, 0.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_player.move(dx, 0.0f);

	if (m_player.getX() + PLAYER_WIDTH / 2 > WINDOW_WIDTH)
		m_player.setX(-PLAYER_WIDTH / 2);
	if (m_player.getX() + PLAYER_WIDTH / 2 < 0)
		m_player.setX(WINDOW_WIDTH - PLAYER_WIDTH / 2);

	m_dy += 0.2f;
	m_player.move(0.0f, m_dy);

	if (m_player.getY() > WINDOW_HEIGHT)
	{
		m_state = GameState::GameOver;
		return;
	}

	if (m_player.getY() < MAX_PLAYER_Y)
	{
		m_player.setY(MAX_PLAYER_Y);
		m_score -= 0.05f * m_dy;

		for (Platform* p : m_platforms)
			p->scrollBy(m_dy);

		m_enemy->scrollBy(m_dy);
	}

	for (Platform* p : m_platforms)
	{
		p->update();

		if (p->isActive() && utils::IsOnPlatform(m_player, *p) && m_dy > 0)
		{
			m_dy = p->getJumpVelocity();
			p->onLand();
		}
	}

	m_enemy->chasePlayer(m_player.getX());
	m_enemy->update();

	if (m_enemy->getBounds().intersects(
		sf::FloatRect(m_player.getX(), m_player.getY(), PLAYER_WIDTH, PLAYER_WIDTH)))
	{
		m_state = GameState::GameOver;
	}
}

void Game::draw()
{
	m_window.draw(m_sprBackground);

	for (Platform* p : m_platforms)
		p->draw(m_window);

	m_enemy->draw(m_window);

	m_sprPlayer.setPosition(m_player.getX(), m_player.getY());
	m_window.draw(m_sprPlayer);

	m_scoreText.setString(std::to_string(static_cast<int>(m_score)));
	m_window.draw(m_scoreText);

	if (m_state == GameState::GameOver)
	{
		m_window.draw(m_gameOverText);
		m_window.draw(m_restartText);
	}

	m_window.display();
}

void Game::reset()
{
	m_player.reset();
	m_dy = 0.0f;
	m_score = 0.0f;

	for (int i = 0; i < static_cast<int>(m_platforms.size()); ++i)
		m_platforms[i]->reset(i);

	// Garantuojame platformą tiesiai po žaidėjo pradinės pozicijos
	m_platforms[0]->setPosition(
		WINDOW_WIDTH / 2.0f - PLATES_WIDTH / 2.0f,
		MAX_PLAYER_Y + PLAYER_WIDTH + 10.0f
	);

	Enemy fresh(20.0f, 400.0f, 1.5f);
	*m_enemy = Enemy(fresh);
}
