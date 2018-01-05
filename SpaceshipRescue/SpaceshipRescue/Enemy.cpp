
#include "Enemy.h"
using namespace std;

Enemy::Enemy() {}
Enemy::~Enemy() {} //deconstructor

void Enemy::initialise(int i)
{
	m_texture.loadFromFile("ai.png"); //reset relevant vars
	m_image.setTexture(m_texture); //apply texture to image
	m_position = sf::Vector2f(200, 200); //offset each enemy (formerly i* 86) CONST
	m_isAlive = false; //for test only

	m_image.setOrigin(sf::Vector2f(m_image.getGlobalBounds().width / 2.0f, (m_image.getGlobalBounds().height / 2.0f)));

	minSpeed = 0;
	maxSpeed = 4;
	speed = 2;
	m_image.setScale(0.3f, 0.3f);
	m_image.rotate(180);


	offSetX = m_image.getGlobalBounds().width / 2.0f;

	offSetY = m_image.getGlobalBounds().height / 2.0f;

	if (i == 0)
	{
		m_isAlive = true;
	}
	currentWaypoint = 0; //head to first waypoint at first.
	int hund = 100;
	m_waypoint.reserve(5);
	cout << std::to_string(m_waypoint.size()) << endl;


	random_device rando; //rng 
	mt19937 gen(rando());
	uniform_int_distribution<> dist(0, 1);
	uniform_int_distribution<> dist2(0, 2);
	rPath = dist(gen); //select 
	//m_image.setOrigin(16, 16);
	m_waypoint.clear(); //if game restarts we want a fresh vector
}


void Enemy::Draw(sf::RenderWindow &window)
{
	window.draw(m_image);
}

//if enemies are alive, they should be doing stuff
void Enemy::update(float i, sf::Vector2f target, float deltaTime)
{
	//timer += clocker.getElapsedTime();

	//lastUp = deltaTime;

	delta = deltaTime;

	if (i == 0)
	{
		//m_velocity.x =  //sin((3.14 / 180)*orient) * speed;// * t.asSeconds();

		//m_velocity.y =  //cos((3.14 / 180)*orient)* speed; //* t.asSeconds();

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


		if (i != 2)
		{
			m_image.setRotation((tempOri + 180));
		}

		else 
		{
			m_image.setRotation(tempOri); //flee points away
		}

		m_image.setPosition(m_position); //set position of sprite
	}


	//if (m_position.y > 1180)
	//{
	//	m_position.y = 0;
	//}
	//else if (m_position.y < -100)
	//{
	//	m_position.y = 1080;
	//}
	//if (m_position.x > 2020)
	//{
	//	m_position.x = 0;
	//}
	//else if (m_position.x < -100)
	//{
	//	m_position.x = 1920;
	//}

}

//flee Velocity = my.position - target.position

float Enemy::getOrient(float orientation, sf::Vector2f velocity, sf::Vector2f target)
{


	//CGPoint originPoint = CGPointMake(endingPoint.x - startingPoint.x, endingPoint.y - startingPoint.y); // get origin point to origin by subtracting end from start
	//float bearingRadians = atan2f(originPoint.y, originPoint.x); // get bearing in radians
	//float bearingDegrees = bearingRadians * (180.0 / M_PI); // convert to degrees
	//bearingDegrees = (bearingDegrees > 0.0 ? bearingDegrees : (360.0 + bearingDegrees)); // correct discontinuity
	//return bearingDegrees;


	///m_velocity = target - m_position; //getcentresmayb



	float bearingRad = atan2f(target.x - m_position.x, target.y - m_position.y);
	float bearingDegrees = bearingRad * (180 / 3.14);
	bearingDegrees = (bearingDegrees > 0.0 ? bearingDegrees : (360.0 + bearingDegrees));

	return bearingDegrees;


	//float mag = m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y;

	//
	//mag = sqrt(mag); //length of vector

	//if (mag > 0) //if valid vector, calc new ori
	//{
	//	cout << mag << endl;
	//	return atan2(target.y, target.x);
	//}

	//return 0; //else return same ori
}


void Enemy::Flee(sf::Vector2f target)
{

	m_velocity = sf::Vector2f(m_position.x + offSetX, m_position.y + offSetY) - sf::Vector2f(target.x + offSetX, target.y + offSetY); //getcentresmayb

																																								  //m_velocity =  m_position - target;

	float mag = m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y;
	mag = sqrt(mag); //length of vector
	m_velocity = m_velocity / mag;
	//orient = getOrient(orient, m_velocity, target);
	//m_velocity = normalize(velocity)
	m_velocity = m_velocity * speed;

	orient = getOrient(orient, m_velocity, target);
}


float Enemy::Arrive(sf::Vector2f target)
{
	sf::Vector2f temp = sf::Vector2f(target.x + offSetX, target.y + offSetY) - sf::Vector2f(m_position.x + offSetX, m_position.y + offSetY);

	float mag = temp.x * temp.x + temp.y * temp.y;
	mag = sqrt(mag);


	if (mag < 500)//target.getRadius())
	{
		m_velocity = sf::Vector2f(0, 0);
		return 0; //mayb this should be dist inverse or w/e
	}

	cout << "kaboom" << endl;


	//sf::Vector2f temp = sf::Vector2f(target.x + offSetX, target.y + offSetY) - sf::Vector2f(m_position.x + offSetX, m_position.y + offSetY); //getcentresmayb
	//float mag = temp.x * temp.x + temp.y * temp.y;
	//mag = sqrt(mag);


	//if (mag < 50)//target.getRadius())
	//{
	//	m_velocity = sf::Vector2f(0, 0);
	//	return 0; //mayb this should be dist inverse or w/e
	//}
	//else
	//{
	//	m_velocity = temp; //
	//	m_velocity = m_velocity / m_timeToTarget;
	//	if (mag > speed)
	//	{
	//		m_velocity = m_velocity / mag;
	//		m_velocity *= speed;
	//	}
	//	orient = getOrient(orient, m_velocity, target);
	//}

}

void Enemy::Seek(sf::Vector2f target)
{


	//m_velocity = target - m_position; //getcentresmayb
	m_velocity = sf::Vector2f(target.x + offSetX, target.y + offSetY) - sf::Vector2f(m_position.x + offSetX, m_position.y + offSetY); //getcentresmayb

	float mag = m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y;

	mag = sqrt(mag); //length of vector

	if (mag != 0)
	{
		m_velocity = m_velocity / mag;
	}


	//m_velocity = normalize(velocity)
	m_velocity = m_velocity * speed;

	orient = getOrient(orient, m_velocity, target);



	//Arrive(target);
}
