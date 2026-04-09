#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "objects.h"
#include "utils.h"

using namespace sf;
using namespace std;

void ResetGame(Player& player, Plate plates[], float& dy, float& score)
{
	player.reset();
	dy = 0.0f;
	score = 0.0f;

	for (int i = 0; i < PLATES_AMOUNT; ++i)
		plates[i].reset(i);
}

void UpdatePositions(Player& player, Plate plates[], float& dy, float& score, GameState& state)
{
	const float dx = 3.5f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		player.move(-dx, 0.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		player.move(dx, 0.0f);

	if (player.getX() + PLAYER_WIDTH / 2 > WINDOW_WIDTH)
		player.setX(-PLAYER_WIDTH / 2);
	if (player.getX() + PLAYER_WIDTH / 2 < 0)
		player.setX(WINDOW_WIDTH - PLAYER_WIDTH / 2);

	dy += 0.2f;
	player.move(0.0f, dy);

	if (player.getY() > WINDOW_HEIGHT)
	{
		state = GameState::GameOver;
		return;
	}

	if (player.getY() < MAX_PLAYER_Y)
	{
		player.setY(MAX_PLAYER_Y);
		score -= 0.05f * dy;

		for (int i = 0; i < PLATES_AMOUNT; ++i)
		{
			plates[i].y -= dy;

			if (plates[i].y > WINDOW_HEIGHT)
			{
				plates[i].y = float(rand() % 10);
				plates[i].x = float(rand() % (WINDOW_WIDTH - PLATES_WIDTH));
			}
		}
	}

	for (int i = 0; i < PLATES_AMOUNT; ++i)
	{
		if (utils::InOnPlate(player, plates[i]) && dy > 0)
			dy = PLAYER_JUMP_V;
	}
}

int main()
{
	srand((unsigned)time(nullptr));
	RenderWindow app(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Doodle Jump");
	app.setFramerateLimit(60);

	Texture tBackground, tPlayer1, tPlatform, tPlayer2;
	tBackground.loadFromFile("resources/background.png");
	tPlayer1.loadFromFile("resources/doodle1.png");
	tPlayer2.loadFromFile("resources/doodle2.png");
	tPlatform.loadFromFile("resources/platform.png");

	sf::Font font;
	font.loadFromFile("resources/arialbd.ttf");

	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(40);
	scoreText.setFillColor(Color::Red);
	scoreText.setOutlineThickness(1);
	scoreText.setOutlineColor(Color::Black);
	scoreText.setPosition(WINDOW_WIDTH / 2.0f - 25.f, 10.f);

	sf::Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setString("Game Over");
	gameOverText.setCharacterSize(52);
	gameOverText.setFillColor(Color::White);
	gameOverText.setOutlineThickness(2);
	gameOverText.setOutlineColor(Color::Black);
	gameOverText.setPosition(70.f, 180.f);

	sf::Text restartText;
	restartText.setFont(font);
	restartText.setString("Press R to restart");
	restartText.setCharacterSize(26);
	restartText.setFillColor(Color::Yellow);
	restartText.setOutlineThickness(1);
	restartText.setOutlineColor(Color::Black);
	restartText.setPosition(85.f, 250.f);

	Sprite sprBackground(tBackground);
	Sprite sprPlayer(tPlayer1);
	Sprite sprPlatform(tPlatform);

#ifdef SOUND_ON
	sf::SoundBuffer buffer;
	buffer.loadFromFile("resources/music.wav");

	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.play();
	sound.setLoop(true);
#endif

	Player player;
	Plate plates[PLATES_AMOUNT];

	float dy = 0;
	float score = 0;
	GameState state = GameState::Playing;

	ResetGame(player, plates, dy, score);

	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();
		}

		if (state == GameState::GameOver)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				ResetGame(player, plates, dy, score);
				state = GameState::Playing;
			}
		}
		else
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
				sprPlayer.setTexture(tPlayer1);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
			{
				sprPlayer.setTexture(tPlayer2);
				dy -= 0.21f;
			}

			UpdatePositions(player, plates, dy, score, state);
		}

		app.draw(sprBackground);

		for (int i = 0; i < PLATES_AMOUNT; ++i)
		{
			sprPlatform.setPosition(plates[i].x, plates[i].y);
			app.draw(sprPlatform);
		}

		sprPlayer.setPosition(player.getX(), player.getY());
		app.draw(sprPlayer);

		scoreText.setString(to_string((int)score));
		app.draw(scoreText);

		if (state == GameState::GameOver)
		{
			app.draw(gameOverText);
			app.draw(restartText);
		}

		app.display();
	}

	return 0;
}
