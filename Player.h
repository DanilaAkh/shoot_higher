#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Weapon.h"

#pragma warning(disable : 4996)

class Player
{
public:
	Player();
	sf::CircleShape& get_shape();
	int get_speed();
	void move(sf::Vector2f);
	sf::Vector2f get_pos();
	bool collision(sf::FloatRect);
	void draw(sf::RenderWindow& win, sf::Font&);
	bool die();
	void set_position(float, float);
	void restart();
	sf::CircleShape& shoot();

private:
	sf::Vector2f pos;
	int speed = 2;
	int health_points = 3;
	Weapon weapon;
	sf::CircleShape player;
};

