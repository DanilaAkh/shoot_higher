#include "Player.h"

Player::Player()
{
	this->player = sf::CircleShape(5.f);
	player.setFillColor(sf::Color::Green);	
	this->player.setPosition(sf::Vector2f(80,80));
	this->pos = this->player.getPosition();
}

sf::CircleShape& Player::get_shape()
{
	return this->player;
}

int Player::get_speed()
{
	return this->speed;
}

void Player::move(sf::Vector2f move_rec)
{
	this->player.move(move_rec);
	this->pos = this->player.getPosition();


	// Проверка рамок-----------------------------------------
	if (pos.x > 1260) player.setPosition(1260, pos.y);
	if (pos.x < 10) player.setPosition(10, pos.y);
	if (pos.y > 710) player.setPosition(pos.x, 710);
	if (pos.y < 10) player.setPosition(pos.x, 10);

	if ((pos.x > 1260) && (pos.y > 710)) player.setPosition(1260, 710);
	if ((pos.x > 1260) && (pos.y < 10)) player.setPosition(1260, 10);
	if ((pos.x < 10) && (pos.y > 710)) player.setPosition(10, 710);
	if ((pos.x < 10) && (pos.y < 10)) player.setPosition(10, 10);
}

sf::Vector2f Player::get_pos()
{
	return this->pos;
}

bool Player::collision(sf::FloatRect obj)
{
	if (this->player.getGlobalBounds().intersects(obj)) 
	{
		player.setPosition(640, 360);
		return true;
	}
		return false;
}

void Player::draw(sf::RenderWindow& win)
{
	win.draw(this->player);
}

bool Player::die()
{
	this->health_points -= 1;
	if (this->health_points <= 0)
		return true;	
	return false;
}

void Player::set_position(float x, float y)
{
	player.setPosition(x, y);
}

void Player::restart()
{
	player.setPosition(1260, 710);
	health_points = 3;
	bullets = 5;
}