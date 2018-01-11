
#include "Projectile.h"
using namespace std;
Projectile::Projectile() {};

Projectile::Projectile(sf::Vector2f pos, float rot, float mag, sf::Vector2f velocity)
{
	m_position = pos;
	rotation = rot;
	if (mag > 0)
	{
		m_velocity = velocity / mag;
	}
	else
	{
		m_isAlive = false;
	}
	m_velocity.x *= 12;
	m_velocity.y *= 12;
	m_texture.loadFromFile("missile.png");
	m_image.setOrigin(sf::Vector2f(m_image.getGlobalBounds().width / 2.0f, (m_image.getGlobalBounds().height / 2.0f)));
	m_image.setTexture(m_texture); //apply texture to image}
	m_image.setScale(0.01f, 0.01f);

}; //reset relevant vars


Projectile::~Projectile() {} //deconstructor

void Projectile::initialise(sf::Vector2f pos, float rot, sf::Vector2f velocity)
{
	//float mag = velocity.x * velocity.x + velocity.y * velocity.y;
	//if (mag > 0)
	//{
	//	m_velocity = velocity / mag;
	//}
	//else
	//{
	//	m_isAlive = false;
	//}
	//m_velocity.x *= 12;
	//m_velocity.y *= 12;
	
	m_position = pos; //offset each Projectile (formerly i* 86) CONST

	//m_isAlive = true; //for test only



	minSpeed = 0;
	maxSpeed = 7;//8.2f;
	speed = 7;//8.2f;

	m_image.rotate(180);

	offSetX = m_image.getGlobalBounds().width / 2.0f;
	offSetY = m_image.getGlobalBounds().height / 2.0f;

	lifetime = sf::Time::Zero;
	lifeClock.restart();
}


void Projectile::Draw(sf::RenderWindow &window)
{
	if (m_isAlive)
	{
 		window.draw(m_image);// , sf::BlendAdd);
	}
}

void Projectile::setAlive(bool alive)
{
	m_isAlive = alive;
}

//if enemies are alive, they should be doing stuff
void Projectile::update(float deltaTime)
{
	//float mag = m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y;

	//if (mag <= 0)
	//{
	//	m_isAlive = false;
	//}

	lifetime += lifeClock.getElapsedTime();

	//m_position += m_velocity;

	if (lifetime.asMilliseconds() > 50000)
	{
		//std::cout << "bullet timeout" << endl;

		m_isAlive = false;

		lifeClock.restart();
		lifetime = sf::Time::Zero;
	}

	if (m_isAlive)
	{
		delta = deltaTime;

		//SSeek(target);


		if (orient < 0)
		{
			orient = (360) - (-orient);
		}

		m_position += m_velocity;

		//int tempOri = orient;

		//tempOri += 360;

		//tempOri = tempOri % 360;
		//tempOri *= -1;

		m_image.setRotation((rotation));

	//	m_image.setRotation(tempOri);

		m_image.setPosition(m_position); //set position of sprite
	}
	else
	{
		//explode

		//	delete this;
	}
	
}


bool Projectile::getAlive()
{
	return m_isAlive;
}

float Projectile::getOrient(float orientation, sf::Vector2f velocity, sf::Vector2f target)
{
	float bearingRad = atan2f(target.x - m_position.x, target.y - m_position.y);
	float bearingDegrees = bearingRad * (180 / 3.14);
	bearingDegrees = (bearingDegrees > 0.0 ? bearingDegrees : (360.0 + bearingDegrees));

	return bearingDegrees;
}



void Projectile::setPosition(sf::Vector2f pos)
{
	m_position = pos;
}


