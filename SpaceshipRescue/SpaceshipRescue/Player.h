#include "stdafx.h"
#include "Projectile.h"

//Class definition for the Player game object
class Player {
private:
	sf::View m_view;
	sf::Vector2f m_bufferVector;
	sf::Texture m_texture;
	sf::Texture* m_pTexture;
	sf::Clock m_frameClock;
	sf::Time m_frameTime;
	sf::Event m_event;
	float m_speed = 0.5;
	AnimatedSprite m_sprite;
	Animation m_animation;
	bool keyUp;

	Projectile* bulletArray[30];

	std::vector<Projectile*> bulletVector;

//	Projectile ProjectileArray[50];

	//std::vector<Projectile> ProjectileVector;

	std::vector<Projectile*>::iterator bulletIterator;

	sf::Vector2f maxVelo;
	sf::Vector2f minVelo;
	int minSpeed;
	int maxSpeed;
	float angle;
	int m_size;
	sf::Vector2f m_position; //position of Player
	const float m_maxHealth = 1; //max Player health
	float m_health = m_maxHealth; //Player health
	bool m_isAlive = false; //is Player alive
	std::vector<sf::Vector2f> m_waypoint; //vector of vector2s that hold the waypoints set for the Player
	int currentWaypoint; //the current waypoint in a vector
	const int maxWaypoint = 5; //the maximum number of waypoints in a vector
	int rPath; //random path
	sf::Vector2f m_velocity; //Player velocity
	int PlayerType; //fed a random distrubution to see if Player is type 1, 2 or 3
	float speed;

//	sf::View m_radar;

public:
	Player();
	~Player();


	void Init();
	//void Update();
	void Draw(sf::RenderWindow &window);


	void update(float time);

	sf::Vector2f getPosition();
	sf::Vector2f& getPositionRef();
	bool getAlive();
	float getHealth();
	//sf::Vector2f getPosition();
	sf::Vector2f getVelocity();

	void setPosition(sf::Vector2f position);
	void setAlive(bool alive);
	void setHealth(float healthChange);
	void setVelocity(sf::Vector2f velocity);

	sf::FloatRect getRect();

};






