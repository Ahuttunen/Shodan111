#include "Enemy.h"
#include <random>
#include <time.h>

Enemy::Enemy()
{
	srand((rand()&540+100));
	Sprites.setPosition((rand()%520+100), - Sprites.getGlobalBounds().height-200.f);
	EnemyHealth = 3;
	srand(time(NULL));
	a = rand() % 2;
}
Enemy::~Enemy(void)
{
}
void Enemy::loadTextures()
{
Textures.loadFromFile("Textures/tankki.png");
Sprites.setTexture(Textures);
Sprites.setOrigin(Textures.getSize().x*0.5,Textures.getSize().y*0.5);
EnemyisAlive = true;
}
void Enemy::update(sf::Time deltatime)
{
	if (EnemyisAlive)
	{
		sf::Vector2f movement(0, 0);
		movement.y += 500;
		Sprites.move(movement * deltatime.asSeconds());

	}
	
	std::vector<Bullet>::iterator it = shots.begin();
	while (it !=shots.end())
	{
		it->update(deltatime);
		it++;
	}
}
void Enemy::draw(sf::RenderWindow& myWindow)
{
	std::vector<Bullet>::iterator it = shots.begin();
	while (it != shots.end())
	{
		it->loadTexture();
		it->draw(myWindow);
		it++;
	}
	loadTextures();
	myWindow.draw(Sprites);
}
bool Enemy::checkBullet(GameObjects& a)
{
	std::vector<Bullet>::iterator it = shots.begin();

	while (it != shots.end())
	{
		if ((*it).getPos().y < 0)
		{
			it = shots.erase(it);
		}
		else if (it->bounds().intersects(a.bounds()))
		{
			it = shots.erase(it);
			return true;
		}
		else
		{
			it++;
		}
	}
	return false;
}
void Enemy::Attack()
{
	Bullet newshot(getPos(), -500);
	shots.push_back(newshot);
}
void Enemy::GettingHit()
{
	EnemyHealth--;
}
int Enemy::GetEnemyHealth()
{
	return EnemyHealth;
}
void Enemy::DeathtoEnemy()
{
	EnemyisAlive = false;
}
bool Enemy::Check()
{
	return EnemyisAlive;
}