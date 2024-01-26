﻿#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>

#include "Player.h"
#include "Enemy.h"

#pragma warning(disable : 4996)



int main()
{
	std::srand(std::time(nullptr));
	const int WIDTH = 1280;
	const int HEIGHT = 720;
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), L"Стреляй выше", sf::Style::Default);
	window.setVerticalSyncEnabled(true);


	sf::Font game_font;
	if (!game_font.loadFromFile("Fonts/calibri.ttf")) return 1;

	
	sf::Image icon;
	icon.loadFromFile("Image/я.jpg");
	
	window.setIcon(32,32, icon.getPixelsPtr());


	sf::Text lose_game(L"Вы проиграли", game_font, 32);
	sf::Text text_game_paused;

	lose_game.setFont(game_font);
	lose_game.setColor(sf::Color::Red);
	lose_game.setPosition(WIDTH / 2 - 85, HEIGHT / 2 - 50);

	text_game_paused.setString(L"ПАУЗА");
	text_game_paused.setFont(game_font);
	text_game_paused.setColor(sf::Color::Cyan);	
	text_game_paused.setCharacterSize(30);
	text_game_paused.setPosition(WIDTH / 2 - 50, HEIGHT / 2 - 50);



	bool game_over = false, game_paused = false;


	sf::Clock clock;
	float time, time_player, time_enemy;

	
	Player player;
	

	std::vector<Enemy> v;
	int count_enemy = std::rand() % 3 + 2;

	for (int i = 0; i < count_enemy; ++i)
	{
		Enemy enemy;
		v.push_back(enemy);
	}

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
						game_over = false;
				}
				break;
			case sf::Event::KeyReleased:
				
				if (event.key.code == sf::Keyboard::W) move_rec.y = 0;
				if (event.key.code == sf::Keyboard::S) move_rec.y = 0;
				if (event.key.code == sf::Keyboard::A) move_rec.x = 0;
				if (event.key.code == sf::Keyboard::D) move_rec.x = 0;
				break;

			case sf::Event::MouseButtonPressed:
				if (event.key.code == sf::Mouse::Left) player.shoot(game_font, window);
			default:break;
			}
		}
		
		if (game_over)
		{			
			window.clear();
			window.draw(lose_game);				// отображение проигрыша

			player.restart();					// перезапуск
			for (auto it = v.begin(); it != v.end(); ++it) it->restart();
		}
		else if (game_paused)
		{
			window.draw(text_game_paused);		// отображение паузы
		}
		else
		{
			window.clear();			
			
			player.move(move_rec);
			window.draw(player.get_shape());
			for (auto it = v.begin(); it != v.end(); ++it)
			{
				it->move(time_enemy, player);
				if (player.collision(it->get_enemy_bounds())) game_over = player.die();		// Проверка на столкновение с противником
			}
			player.draw(window);															//отображение игрока
			for (auto it = v.begin(); it != v.end(); ++it) it->draw(window);				// отображение противников		
		}			
		
		
		window.display();
	}
	return 0;
}