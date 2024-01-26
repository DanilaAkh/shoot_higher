#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#pragma warning(disable : 4996)

class Enemy
{
public:
	Enemy();
	sf::CircleShape& get_shape();
	void move(float, Player);
	bool collision(sf::FloatRect);
	void draw(sf::RenderWindow& win);
	sf::FloatRect get_enemy_bounds();
	void restart();

private:
	sf::Vector2f pos;
	int speed = 1;
	int health_points = 1;
	sf::CircleShape enemy;
};

