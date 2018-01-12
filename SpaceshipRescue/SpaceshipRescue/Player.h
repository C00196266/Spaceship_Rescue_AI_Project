#pragma once

#include "stdafx.h"
#include "Wall.h"
#include "Projectile.h"
//Class definition for the Player game object
class Player {
private:
	sf::View m_view;
	sf::Texture m_texture;
	sf::Texture* m_pTexture;
	float m_speed = 0.5;
	AnimatedSprite m_sprite;
	Animation m_animation;

	sf::Clock fireClock;
	sf::Time fireTime;
	bool canFire;
	float fireRate = 1;

	sf::Sprite radarSprite;
	sf::Texture radarTexture;
	sf::Sprite m_shieldSprite;
	sf::Texture m_shieldTexture;

	std::vector<Wall*>& m_walls;
	int minSpeed;
	int maxSpeed;
	float angle;
	int m_size;
	sf::Vector2f m_position; //position of Player
	const float m_maxHealth = 10; //max Player health
	float m_health = m_maxHealth; //Player health
	bool m_isAlive = false; //is Player alive
	sf::Vector2f m_velocity;
	float speed;
	sf::CircleShape circle;

	Projectile* bulletArray[30];

	std::vector<Projectile*> bulletVector;

	std::vector<Projectile*>::iterator bulletIterator;

	float m_width = 48;
	float m_height = 47;

	bool m_shielded;
public:
	Player(std::vector<Wall*> &walls);
	~Player();


	void Init();
	void Draw(sf::RenderWindow &window);
	float getFireRate();

	void update(float time);

	sf::Vector2f getPosition();
	sf::Vector2f& getPositionRef();
	bool getAlive();
	float getHealth();
	void setFireRate(float rate);
	void checkCollisions(Wall* wall, float deltaTime);
	void setPosition(sf::Vector2f position);
	void setAlive(bool alive);
	void setHealth(float healthChange);
	void setVelocity(sf::Vector2f velocity);
	void DrawRadar(sf::RenderWindow &window);
	std::vector<Projectile*> getBullets();
	sf::FloatRect getRect();

	sf::Vector2f getVelocity();

	bool getShielded();
	void setShieled(bool shielded);
};






