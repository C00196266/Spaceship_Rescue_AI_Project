#pragma once


#ifndef SeekerMissile_H
#define SeekerMissile_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>

//Class used for our SeekerMissile

class SeekerMissile
{
public:
	SeekerMissile();
	~SeekerMissile();

	void initialise(int i);
	
	
	void update(float i, sf::Vector2f target, float deltaTime);
	
	
	sf::Vector2f getPosition();
	bool getAlive();
	float getHealth();
	sf::Vector2f getVelocity();
	
	
	void Flee(sf::Vector2f target);
	void Seek(sf::Vector2f target);
	void Wander(sf::Vector2f target);
	
	float Arrive(sf::Vector2f target);
	
	void rotateOverTime(sf::Vector2f vec, sf::Time timespan, sf::Time elapsedTimeSinceStart);
	
	
	void setPosition(sf::Vector2f position);
	void setAlive(bool alive);
	void setHealth(float healthChange);
	void setVelocity(sf::Vector2f velocity);
	float getOrient(float orientation, sf::Vector2f velocity, sf::Vector2f target);
	void Draw(sf::RenderWindow &window);

private:

	float delta;
	sf::Sprite m_image; //SeekerMissile sprite
	sf::Texture m_texture;  //SeekerMissile texture
	int m_size;
	sf::Vector2f m_position; //position of SeekerMissile
	const float m_maxHealth = 1; //max SeekerMissile health
	float m_health = m_maxHealth; //SeekerMissile health
	bool m_isAlive = false; //is SeekerMissile alive
	std::vector<sf::Vector2f> m_waypoint; //vector of vector2s that hold the waypoints set for the SeekerMissile
	int currentWaypoint; //the current waypoint in a vector
	const int maxWaypoint = 5; //the maximum number of waypoints in a vector
	int rPath; //random path
	sf::Vector2f m_velocity; //SeekerMissile velocity
	int SeekerMissileType; //fed a random distrubution to see if SeekerMissile is type 1, 2 or 3
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
