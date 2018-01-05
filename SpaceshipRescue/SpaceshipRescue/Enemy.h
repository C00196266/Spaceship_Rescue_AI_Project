#pragma once


#ifndef Enemy_H
#define Enemy_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>

//Class used for our Enemy

class Enemy
{
public:
	Enemy();
	~Enemy();

	//void initialise(int i);

	//void Seek(float deltaTime, sf::Vector2f target);

	//void update(float i, sf::Vector2f target, float deltaTime);


	//sf::Vector2f getPosition();
	//bool getAlive();
	//float getHealth();
	//sf::Vector2f getVelocity();

	//void setPosition(sf::Vector2f position);
	//void setAlive(bool alive);
	//void setHealth(float healthChange);
	//void setVelocity(sf::Vector2f velocity);

	//sf::Vector2f normalise(sf::Vector2f distanceVec);


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
	//sf::Sprite m_image; //enemy sprite
	//sf::Texture m_texture;  //enemy texture
	//int m_size;
	//sf::Vector2f m_position; //position of enemy
	//const float m_maxHealth = 1; //max enemy health
	//float m_health = m_maxHealth; //enemy health
	//bool m_isAlive = false; //is enemy alive
	//std::vector<sf::Vector2f> m_waypoint; //vector of vector2s that hold the waypoints set for the enemy
	//int currentWaypoint; //the current waypoint in a vector
	//const int maxWaypoint = 5; //the maximum number of waypoints in a vector
	//int rPath; //random path
	//sf::Vector2f m_velocity; //enemy velocity
	//int enemyType; //fed a random distrubution to see if enemy is type 1, 2 or 3
	//float angle;
	//float minSpeed;
	//float maxSpeed;
	//float speed;


	float delta;

	sf::Sprite m_image; //enemy sprite
	sf::Texture m_texture;  //enemy texture
	int m_size;
	sf::Vector2f m_position; //position of enemy
	const float m_maxHealth = 1; //max enemy health
	float m_health = m_maxHealth; //enemy health
	bool m_isAlive = false; //is enemy alive
	std::vector<sf::Vector2f> m_waypoint; //vector of vector2s that hold the waypoints set for the enemy
	int currentWaypoint; //the current waypoint in a vector
	const int maxWaypoint = 5; //the maximum number of waypoints in a vector
	int rPath; //random path
	sf::Vector2f m_velocity; //enemy velocity
	int enemyType; //fed a random distrubution to see if enemy is type 1, 2 or 3
	float rotation;
	int offSetX;
	int offSetY;
	float m_radius;
	float m_timeToTarget;
	sf::Time lastUp;
	
	sf::Clock clocker;
	sf::Time timer;
	
	
	//int rPath;
	
	//mt19937 gen();
	//uniform_int_distribution<> dist(-1, 1);
	
	
	float lastDegrees;
	float endDegrees;
	
	float minSpeed;
	float maxSpeed;
	float speed;
	float orient;
};

#endif









///////$$$$$$$$$$


//
//
//#pragma once
//
//
//#ifndef Enemy_H
//#define Enemy_H
//#include <iostream>
//#include <SFML/Graphics.hpp>
//#include <random>
////Class used for our Enemy
//#include "player.h"
//class Enemy
//{
//public:
//	Enemy();
//	~Enemy();
//
//	void initialise(int i);
//
//
//	void update(sf::RenderWindow& window, float i, Player target, sf::Time t);
//
//
//	sf::Vector2f getPosition();
//	bool getAlive();
//	float getHealth();
//	sf::Vector2f getVelocity();
//
//
//	void Flee(Player target);
//	void Seek(Player target);
//	void Wander(Player target);
//
//	float Arrive(Player target);
//
//	void rotateOverTime(sf::Vector2f vec, sf::Time timespan, sf::Time elapsedTimeSinceStart);
//
//
//	void setPosition(sf::Vector2f position);
//	void setAlive(bool alive);
//	void setHealth(float healthChange);
//	void setVelocity(sf::Vector2f velocity);
//	float getOrient(float orientation, sf::Vector2f velocity, Player target);
//private:
//
//	sf::Sprite m_image; //enemy sprite
//	sf::Texture m_texture;  //enemy texture
//	int m_size;
//	sf::Vector2f m_position; //position of enemy
//	const float m_maxHealth = 1; //max enemy health
//	float m_health = m_maxHealth; //enemy health
//	bool m_isAlive = false; //is enemy alive
//	std::vector<sf::Vector2f> m_waypoint; //vector of vector2s that hold the waypoints set for the enemy
//	int currentWaypoint; //the current waypoint in a vector
//	const int maxWaypoint = 5; //the maximum number of waypoints in a vector
//	int rPath; //random path
//	sf::Vector2f m_velocity; //enemy velocity
//	int enemyType; //fed a random distrubution to see if enemy is type 1, 2 or 3
//	float rotation;
//	int offSetX;
//	int offSetY;
//	float m_radius;
//	float m_timeToTarget;
//	sf::Time lastUp;
//
//	sf::Clock clocker;
//	sf::Time timer;
//
//
//	//int rPath;
//
//	//mt19937 gen();
//	//uniform_int_distribution<> dist(-1, 1);
//
//
//	float lastDegrees;
//	float endDegrees;
//
//	float minSpeed;
//	float maxSpeed;
//	float speed;
//	float orient;
//};
//
//#endif
