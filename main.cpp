#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

#pragma warning(disable : 4996)

std::vector<Enemy>& new_enemies(std::vector<Enemy>& v, int& count_enemy)
{
	v.clear();
	count_enemy = std::rand() % 3 + 2;
	for (int i = 0; i < count_enemy; ++i)
	{
		Enemy enemy;
		v.push_back(enemy);
	}
	return v;
}



int main()
{
	std::srand(std::time(nullptr));
	const float PI = atan(1) * 4;
	const int WIDTH = 1280;
	const int HEIGHT = 720;
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), L"Стреляй выше", sf::Style::Default);
	window.setVerticalSyncEnabled(true);


	sf::Font game_font;
	if (!game_font.loadFromFile("Fonts/calibri.ttf")) return 1;

	
	sf::Image icon;
	icon.loadFromFile("Image/я.jpg");
	
	window.setIcon(32,32, icon.getPixelsPtr());


	sf::Text lose_game(L"Вы проиграли", game_font, 45);
	sf::Text text_game_paused;

	lose_game.setFont(game_font);
	lose_game.setColor(sf::Color::Red);
	lose_game.setPosition(WIDTH / 2 - 100, HEIGHT / 2 - 50);

	text_game_paused.setString(L"ПАУЗА");
	text_game_paused.setFont(game_font);
	text_game_paused.setColor(sf::Color::Cyan);	
	text_game_paused.setCharacterSize(30);
	text_game_paused.setPosition(WIDTH / 2 - 50, HEIGHT / 2 - 50);


	sf::RectangleShape bullet_spot(sf::Vector2f(15.f, 15.f));
	sf::Texture bullet_texture;
	bullet_texture.loadFromFile("Image/loading.jpg");
	bullet_spot.setTexture(&bullet_texture);
	bullet_spot.setPosition(sf::Vector2f(rand() % 1260 + 20, rand() % 700 + 10));


	bool game_over = false, game_paused = false;
	int score = 0;

	sf::Clock clock;
	float time, time_player, time_enemy;

	
	Player player;
	Bullet bull;
	sf::Vector2f  dist_Shot_Position;

	int count_enemy;
	std::vector<Enemy> v;
	new_enemies(v, count_enemy);
	

	sf::Vector2f move_rec;


	while (window.isOpen())
	{
		
		time = clock.getElapsedTime().asMicroseconds();
		time_player = time / 6000;
		time_enemy = time / 10000;
		clock.restart();


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::W) move_rec.y = -time_player;
				if (event.key.code == sf::Keyboard::S) move_rec.y = time_player;
				if (event.key.code == sf::Keyboard::A) move_rec.x = -time_player;
				if (event.key.code == sf::Keyboard::D) move_rec.x = time_player;
				if (event.key.code == sf::Keyboard::P) 
				{
					if (game_paused == false)
						game_paused = true;
					else
						game_paused = false;
				}
				if (event.key.code == sf::Keyboard::R) 
				{
					if (game_over == false)
						game_over = true;
					else
					{
						game_over = false;
						lose_game.setString(L"Вы проиграли");
						score = 0;
					}
				}
				break;
			case sf::Event::KeyReleased:
				
				if (event.key.code == sf::Keyboard::W) move_rec.y = 0;
				if (event.key.code == sf::Keyboard::S) move_rec.y = 0;
				if (event.key.code == sf::Keyboard::A) move_rec.x = 0;
				if (event.key.code == sf::Keyboard::D) move_rec.x = 0;
				break;

			case sf::Event::MouseButtonReleased:
				if (event.key.code == sf::Mouse::Left)
				{
					sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
					float dx = mouse_pos.x - player.get_pos().x;
					float dy = mouse_pos.y - player.get_pos().y;
					float angle = atan2f(dy, dx);
					dist_Shot_Position.x = cos(angle) * time_player*5;				
					dist_Shot_Position.y = sin(angle) * time_player*5;
					bull.shoot(player.get_pos());
				}
			default:break;
			}
		}
		
		if (game_over)
		{			
			window.clear();
			
			window.draw(lose_game);															// отображение проигрыша
			
			new_enemies(v, count_enemy);
			bullet_spot.setPosition(sf::Vector2f(rand() % 1260 + 20, rand() % 700 + 10));

			player.restart(bull);																// перезапуск
			for (auto it = v.begin(); it != v.end(); ++it) it->restart();
		}
		else if (game_paused)
		{
			window.draw(text_game_paused);		// отображение паузы
		}
		else
		{
			window.clear();			
						
			player.draw(window, game_font, bull);
			player.move(move_rec);
						
			bull.draw(window);
			bull.move(dist_Shot_Position);

			window.draw(bullet_spot);

			for (auto it = v.begin(); it != v.end(); ++it)
			{
				it->move(time_enemy, player);
				it->draw(window);																			// отображение противников
				if (player.collision(it->get_enemy_bounds())) 
				{	
					game_over = player.die();
					if (game_over) lose_game.setString(lose_game.getString() + "\n" + L"Итог: " + std::to_string(score) + L" очков!");
				}				
				if (it->collision(bull.get_bullet_bounds()))
				{
					it->die();
					++score;
					--count_enemy;					
				}
			}
			if (count_enemy == 0) new_enemies(v, count_enemy);			
			if (player.collision(bullet_spot.getGlobalBounds())) 
			{ 
				bull.set_bullets(5); 
				bullet_spot.setPosition(sf::Vector2f(rand() % 1260 + 20, rand() % 700 + 10));
			}
			
		}			
				
		window.display();
	}
	return 0;
}