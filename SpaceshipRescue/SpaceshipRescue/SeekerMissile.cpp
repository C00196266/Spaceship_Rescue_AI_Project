
#include "SeekerMissile.h"
using namespace std;

SeekerMissile::SeekerMissile() {}
SeekerMissile::~SeekerMissile() {} //deconstructor

void SeekerMissile::initialise(int i)
{
	m_texture.loadFromFile("ai.png"); //reset relevant vars
	m_image.setTexture(m_texture); //apply texture to image
	m_position = sf::Vector2f(100, 100); //offset each SeekerMissile (formerly i* 86) CONST

	m_isAlive = true; //for test only

	m_image.setOrigin(sf::Vector2f(m_image.getGlobalBounds().width / 2.0f, (m_image.getGlobalBounds().height / 2.0f)));

	minSpeed = 0;
	maxSpeed = 8.2f;
	speed = 8.2f;
	m_image.setScale(0.5f, 0.5f);
	m_image.rotate(180);

	offSetX = m_image.getGlobalBounds().width / 2.0f;
	offSetY = m_image.getGlobalBounds().height / 2.0f;

	//currentWaypoint = 0; //head to first waypoint at first.
	//int hund = 100;
	//m_waypoint.reserve(5);
	//cout << std::to_string(m_waypoint.size()) << endl;

	//random_device rando; //rng 
	//mt19937 gen(rando());
	//uniform_int_distribution<> dist(0, 1);
	//uniform_int_distribution<> dist2(0, 2);
	//rPath = dist(gen); //select 
	//m_waypoint.clear(); //if game restarts we want a fresh vector
}


void SeekerMissile::Draw(sf::RenderWindow &window)
{
	if (m_isAlive)
	{
		window.draw(m_image, sf::BlendAdd);
	}
}

//if enemies are alive, they should be doing stuff
void SeekerMissile::update(float i, sf::Vector2f target, float deltaTime)
{
	if (m_isAlive)
	{


		delta = deltaTime;

		Seek(target);


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

		m_image.setRotation(tempOri); 

		m_image.setPosition(m_position); //set position of sprite
	}
	else
	{
		//explode

	//	delete this;
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


float SeekerMissile::Arrive(sf::Vector2f target)
{
	sf::Vector2f temp = sf::Vector2f(target.x + offSetX, target.y + offSetY) - sf::Vector2f(m_position.x + offSetX, m_position.y + offSetY);

	float mag = temp.x * temp.x + temp.y * temp.y;
	mag = sqrt(mag);


	if (mag < 10)//target.getRadius())
	{
		m_isAlive = false;


		cout << "kaboom" << endl;


		return 0; 
	}
}

void SeekerMissile::Seek(sf::Vector2f target)
{
	m_velocity = sf::Vector2f(target.x + offSetX, target.y + offSetY) - sf::Vector2f(m_position.x + offSetX, m_position.y + offSetY); 

	float mag = m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y;

	mag = sqrt(mag); //length of vector

	if (mag != 0)
	{
		m_velocity = m_velocity / mag;
	}

	m_velocity = m_velocity * speed;

	orient = getOrient(orient, m_velocity, target);

	Arrive(target); //aka explode
}
