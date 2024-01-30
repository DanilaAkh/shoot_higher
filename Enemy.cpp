#include "Enemy.h"


Enemy::Enemy()
{
	this->enemy = sf::CircleShape(10.f);
	enemy.setFillColor(sf::Color::Red);
	this->enemy.setPosition(sf::Vector2f(rand() % 1260 + 20, rand() % 700 + 10));
}

sf::CircleShape& Enemy::get_shape()
{
	return this->enemy;
}

void Enemy::move(float time, Player player)
{
	sf::Vector2f move_rec;
	float angle = atan2f(player.get_pos().y - this->pos.y, player.get_pos().x - this->pos.x);

	move_rec.x = cos(angle) * time;
	move_rec.y = sin(angle) * time;


	//if (razn.x >= 0 && razn.y >= 0) { move_rec.x = time; move_rec.y = time; }
	//else if (razn.x < 0 && razn.y >= 0) { move_rec.x = -time; move_rec.y = time; }
	//else if (razn.x >= 0 && razn.y < 0) { move_rec.x = time; move_rec.y = -time; }
	//else if (razn.x < 0 && razn.y < 0) { move_rec.x = -time; move_rec.y = -time; }


	this->enemy.move(move_rec);
	this->pos = this->enemy.getPosition();


	// Проверка рамок-----------------------------------------
	if (pos.x > 1260) enemy.setPosition(1260, pos.y);
	if (pos.x < 10) enemy.setPosition(10, pos.y);
	if (pos.y > 710) enemy.setPosition(pos.x, 710);
	if (pos.y < 10) enemy.setPosition(pos.x, 10);

	if ((pos.x > 1260) && (pos.y > 710)) enemy.setPosition(1260, 710);
	if ((pos.x > 1260) && (pos.y < 10)) enemy.setPosition(1260, 10);
	if ((pos.x < 10) && (pos.y > 710)) enemy.setPosition(10, 710);
	if ((pos.x < 10) && (pos.y < 10)) enemy.setPosition(10, 10);
	//---------------------------------------------------------
}

bool Enemy::collision(sf::FloatRect obj)
{
	if (this->enemy.getGlobalBounds().intersects(obj)) return true;
	return false;
}

void Enemy::draw(sf::RenderWindow& win)
{
	win.draw(this->enemy);
}

sf::FloatRect Enemy::get_enemy_bounds()
{
	return enemy.getGlobalBounds();
}

void Enemy::restart()
{
	this->enemy.setPosition(sf::Vector2f(rand() % 1260 + 20, rand() % 700 + 10));
}

bool Enemy::die()
{
	enemy.setRadius(0);
	return false;
}
