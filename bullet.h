#pragma once
#include <SFML/Graphics.hpp>


#pragma warning(disable : 4996)

class Bullet
{
public:
	Bullet();
	sf::CircleShape& shoot(sf::Vector2f);
	int get_bullets();
	void set_bullets(int bullets);
	sf::FloatRect get_bullet_bounds();
	void draw(sf::RenderWindow& win);
	void move(sf::Vector2f move_rec);

private:
	sf::CircleShape bullet;
	int bullets;
};

