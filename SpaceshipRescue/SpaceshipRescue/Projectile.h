#pragma once


#ifndef Projectile_H
#define Projectile_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>

//Class used for our Projectile

class Projectile
{
public:
	Projectile();
	Projectile(sf::Vector2f pos, float rot, float mag, sf::Vector2f velocity);
	~Projectile();

	void initialise(sf::Vector2f pos, float rot, sf::Vector2f velocity);


	void update(float i, float deltaTime);

	sf::Time lifetime;
	sf::Clock lifeClock;

	sf::Vector2f getPosition();

	bool getAlive();
	float getHealth();

	sf::Vector2f getVelocity();
	float getOrient(float orientation, sf::Vector2f velocity, sf::Vector2f target);

	void setPosition(sf::Vector2f position);
	void setAlive(bool alive);

	void setVelocity(sf::Vector2f velocity);

	void Draw(sf::RenderWindow &window);

private:

	float delta;
	sf::Sprite m_image; //Projectile sprite
	sf::Texture m_texture;  //Projectile texture
	int m_size;
	sf::Vector2f m_position; //position of Projectile
	const float m_maxHealth = 1; //max Projectile health
	float m_health = m_maxHealth; //Projectile health
	bool m_isAlive = true; //is Projectile alive
	std::vector<sf::Vector2f> m_waypoint; //vector of vector2s that hold the waypoints set for the Projectile
	int currentWaypoint; //the current waypoint in a vector
	const int maxWaypoint = 5; //the maximum number of waypoints in a vector
	int rPath; //random path
	sf::Vector2f m_velocity; //Projectile velocity
	int ProjectileType; //fed a random distrubution to see if Projectile is type 1, 2 or 3
	float rotation;
	int offSetX;
	int offSetY;
	float m_radius;
	float m_timeToTarget;
	sf::Time lastUp;

	sf::Clock clocker;
	sf::Time timer;

	float lastDegrees;
	float endDegrees;
	float minSpeed;
	float maxSpeed;
	float speed;
	float orient;
};

#endif
