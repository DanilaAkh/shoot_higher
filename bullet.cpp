#include "Bullet.h"

Bullet::Bullet()
{
	this->bullets = 5;
	this->bullet = sf::CircleShape(5.f);
}

sf::CircleShape& Bullet::shoot(sf::Vector2f player)
{
	bullet.setRadius(0);
	if (this->bullets > 0)
	{		
		--this->bullets;
		bullet.setRadius(5.f);
		bullet.setFillColor(sf::Color::White);
		bullet.setPosition(player);
	}
	
	return bullet;
}

int Bullet::get_bullets()
{
	return this->bullets;
}

void Bullet::set_bullets(int bullets)
{
	this->bullets = bullets;
}

sf::FloatRect Bullet::get_bullet_bounds()
{
	return bullet.getGlobalBounds();
}

void Bullet::draw(sf::RenderWindow& win)
{
	win.draw(bullet);
}

void Bullet::move(sf::Vector2f move_rec)
{
	bullet.move(move_rec);
}
