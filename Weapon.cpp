#include "Weapon.h"

Weapon::Weapon()
{
	this->bullets = 5;
}

sf::CircleShape& Weapon::shoot(sf::Vector2f player)
{	
	sf::CircleShape bullet(5.f);
	if (this->bullets > 0)
	{		
		--this->bullets;
		bullet.setFillColor(sf::Color::White);
		bullet.setPosition(player);
	}
	return bullet;
}

int Weapon::get_bullets()
{
	return this->bullets;
}

void Weapon::set_bullets(int bullets)
{
	this->bullets = bullets;
}
