#include "Enemy.h"


Enemy::Enemy()
{
	this->enemy = sf::CircleShape(5.f);
	enemy.setFillColor(sf::Color::Red);
	this->enemy.setPosition(sf::Vector2f(rand() % 1260 + 20, rand() % 700 + 10));
}

sf::CircleShape& Enemy::get_shape()
{
	return this->enemy;
}

void Enemy::move(float time, Player player)
{
	sf::Vector2f pos1 = player.get_pos();
	sf::Vector2f razn = sf::Vector2f(pos1.x - this->pos.x, pos1.y - this->pos.y);
	sf::Vector2f move_rec(-1 + (int(razn.x) % 3) * time, (-1 + int(razn.y) % 3) * time); //  ���������� ��� ���������� �� �������

	


	this->enemy.move(move_rec);
	this->pos = this->enemy.getPosition();


	// �������� �����-----------------------------------------
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
