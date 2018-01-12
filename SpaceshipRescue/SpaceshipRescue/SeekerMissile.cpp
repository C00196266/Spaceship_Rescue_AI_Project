#include "SeekerMissile.h"
using namespace std;

SeekerMissile::SeekerMissile() {}
SeekerMissile::~SeekerMissile() {} //deconstructor

void SeekerMissile::initialise(int i, sf::Vector2f pos)
{
	/********************************************//**
 *  ...  // initialise seekermissile variables
 ***********************************************/
	m_texture.loadFromFile("ai.png"); //reset relevant vars
	m_image.setTexture(m_texture); //apply texture to image
	m_position = pos; //offset each SeekerMissile (formerly i* 86) CONST

	m_isAlive = true; //for test only

	m_image.setOrigin(sf::Vector2f(m_image.getGlobalBounds().width / 2.0f, (m_image.getGlobalBounds().height / 2.0f)));

	minSpeed = 0;
	maxSpeed = 2;//8.2f;
	speed = 2;//8.2f;
	m_image.setScale(0.02f, 0.02f);
	m_image.rotate(180);

	offSetX = m_image.getGlobalBounds().width / 2.0f;
	offSetY = m_image.getGlobalBounds().height / 2.0f;

	lifetime = sf::Time::Zero;
	lifeClock.restart();
}

void SeekerMissile::Draw(sf::RenderWindow &window)
{
	/********************************************//**
  *  ...  // draw seekermissile object in game world
 ***********************************************/
	if (m_isAlive)
	{
		window.draw(m_image);// , sf::BlendAdd);
	}
}

void SeekerMissile::setAlive(bool alive)
{
	m_isAlive = alive;
}

//if enemies are alive, they should be doing stuff
void SeekerMissile::update(float i, Player* player, float deltaTime)
{
	/********************************************//**
*  ...  // update seeker missile 
	***********************************************/
	m_target = (*player).getPosition();

	lifetime += lifeClock.getElapsedTime();


	if (lifetime.asMilliseconds() > 350000)
	{
		std::cout << "timeout" << endl;

		m_isAlive = false;

		lifeClock.restart();
		lifetime = sf::Time::Zero;
	}

	if (m_isAlive && lifetime.asMilliseconds() > 100000)
	{
		delta = deltaTime;

		Seek(m_target, player);


		if (orient < 0)
		{
			orient = (360) - (-orient);
		}

		m_position += m_velocity;

		int tempOri = orient;

		tempOri += 360;

		tempOri = tempOri % 360;
		tempOri *= -1;

		m_image.setRotation((tempOri + 180));

	//	m_image.setRotation(tempOri); 

		m_image.setPosition(m_position); //set position of sprite
	}
}

bool SeekerMissile::getAlive()
{
	return m_isAlive;
}

float SeekerMissile::getOrient(float orientation, sf::Vector2f velocity, sf::Vector2f target)
{

	float bearingRad = atan2f(target.x - m_position.x, target.y - m_position.y);
	float bearingDegrees = bearingRad * (180 / 3.14);
	bearingDegrees = (bearingDegrees > 0.0 ? bearingDegrees : (360.0 + bearingDegrees));

	return bearingDegrees;

}

void SeekerMissile::setPosition(sf::Vector2f pos)
{
	m_position = pos;
}

float SeekerMissile::Arrive(sf::Vector2f target, Player* player)
{
	/********************************************//**
	*  ...  // detonate missile on arrival
	***********************************************/
	sf::Vector2f temp = sf::Vector2f(target.x + offSetX, target.y + offSetY) - sf::Vector2f(m_position.x + offSetX, m_position.y + offSetY);

	float mag = temp.x * temp.x + temp.y * temp.y;
	mag = sqrt(mag);

	if (mag < 20 && m_isAlive == true)//target.getRadius())
	{
		m_isAlive = false;

		cout << "kaboom" << endl;
		int temp = player->getHealth();

		if (player->getShielded() == false)
		{
			player->setHealth(1);
		}
		else
		{
			player->setShieled(false);
		}

		lifeClock.restart();
		lifetime = sf::Time::Zero;

		return 0;
	}
}

void SeekerMissile::Seek(sf::Vector2f target, Player* player)
{
	/********************************************//**
*  ...  // seek to player
***********************************************/
	m_velocity = sf::Vector2f(target.x + offSetX, target.y + offSetY) - sf::Vector2f(m_position.x + offSetX, m_position.y + offSetY); 

	float mag = m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y;

	mag = sqrt(mag); //length of vector

	if (mag != 0)
	{
		m_velocity = m_velocity / mag;
	}

	m_velocity = m_velocity * speed;

	orient = getOrient(orient, m_velocity, target);

	Arrive(target, player); //aka explode
}
