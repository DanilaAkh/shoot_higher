#pragma once
#include <SFML/Graphics.hpp>


#pragma warning(disable : 4996)

class Weapon
{
public:
	Weapon();
	sf::CircleShape& shoot(sf::Vector2f);
	int get_bullets();
	void set_bullets(int bullets);

private:
	int bullets = 5;
};

