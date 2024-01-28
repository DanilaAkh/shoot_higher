#include "Player.h"

Player::Player()
{
	this->player = sf::CircleShape(10.f);
	player.setFillColor(sf::Color::Green);	
	this->player.setPosition(sf::Vector2f(80,80));
	this->pos = this->player.getPosition();
	this->weapon = Weapon();
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
	return this->player.getPosition();
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

void Player::draw(sf::RenderWindow& win, sf::Font& font)
{
	win.draw(this->player);
	sf::Text bullets_count, health;
	int bullets = this->weapon.get_bullets();
	if (bullets == 0)
	{
		bullets_count.setPosition(1100, 10);
		std::wstring str(L"Нет патронов");
		bullets_count.setString(str);
		bullets_count.setColor(sf::Color::Red);
		bullets_count.setFont(font);
		bullets_count.setCharacterSize(30);
	}
	else 
	{
		bullets_count.setPosition(1000, 10);
		std::wstring str(L"Осталось " + std::to_wstring(this->weapon.get_bullets()) + L" патронов");
		bullets_count.setFont(font);
		bullets_count.setCharacterSize(30);
		bullets_count.setString(str);
		bullets_count.setColor(sf::Color::Blue);
	}
	win.draw(bullets_count);
	health.setFont(font);
	health.setCharacterSize(30);
	health.setString(L"Осталось " + std::to_wstring(this->health_points) + L" ХП");
	health.setCharacterSize(30);
	health.setColor(sf::Color::Green);
	health.setPosition(10, 10);
	win.draw(health);
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
	this->weapon.set_bullets(5);
}

sf::CircleShape Player::shoot(sf::Vector2i mouse_pos)
{
	return this->weapon.shoot(this->pos, mouse_pos);
}

