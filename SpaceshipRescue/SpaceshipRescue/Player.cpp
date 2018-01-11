#include "Player.h"
#include <iostream>
using namespace std;

Player::Player(std::vector<Wall*> &walls) : m_walls(walls)
{
	m_velocity	= sf::Vector2f(0, 6); //Player velocity
}

Player::~Player()
{

}

void Player::Init()
{

	m_isAlive = true; //for test only
	speed = 1;
	maxVelo = sf::Vector2f(0, -2);
	minVelo = sf::Vector2f(0, 0);
	angle = 0;
	minSpeed = 0;
	maxSpeed = 6;



	//initialization logic for player
	keyUp = true;
	

	radarTexture.loadFromFile("assets/blip.png");
	radarSprite.setTexture(radarTexture);
	radarSprite.setOrigin(radarTexture.getSize().x / 2.0f, radarTexture.getSize().y / 2.0f);
	radarSprite.setScale(0.2f, 0.2f);

	m_view = sf::View(m_position, sf::Vector2f(360, 240));
	m_texture.loadFromFile("playertrans.png");
	m_texture.setSmooth(true);
	m_pTexture = &m_texture;

	m_animation.setSpriteSheet(*m_pTexture);

	m_animation.addFrame(sf::IntRect(0, 0, 48, 47));
	m_animation.addFrame(sf::IntRect(49, 0, 48, 47));
	m_animation.addFrame(sf::IntRect(98, 0, 48, 47));
	m_animation.addFrame(sf::IntRect(147, 0, 48, 47));
	m_animation.addFrame(sf::IntRect(196, 0, 48, 47));

	m_animation.addFrame(sf::IntRect(245, 0, 48, 47));
	m_animation.addFrame(sf::IntRect(294, 0, 48, 47));
	m_animation.addFrame(sf::IntRect(343, 0, 48, 47));
	m_animation.addFrame(sf::IntRect(392, 0, 48, 47));
	m_animation.addFrame(sf::IntRect(441, 0, 48, 47));

	m_animation.addFrame(sf::IntRect(490, 0, 48, 47));
	m_animation.addFrame(sf::IntRect(539, 0, 48, 47));
	m_animation.addFrame(sf::IntRect(588, 0, 48, 47));
	m_animation.addFrame(sf::IntRect(637, 0, 48, 47));


	m_sprite.setAnimation(m_animation);
	m_sprite.setLooped(true);

	m_sprite.setOrigin(24, 23.5f);
	m_position = sf::Vector2f(300, 300);

	m_sprite.setRotation(180);

	m_sprite.setAnimation(m_animation);
	m_sprite.setScale(0.5f, 0.5f); //was 0.2

	m_view.zoom(1);
	m_view.setCenter(m_sprite.getPosition());

	fireClock.restart();
	fireTime = sf::Time::Zero;

	m_health = m_maxHealth;
	m_shielded = false;
}

//Draw method used to draw the animated sprite and also to set the view of the render window to center on the player object.
void Player::DrawRadar(sf::RenderWindow &window)
{

		window.draw(radarSprite);

		window.setView(m_view);

}


//Draw method used to draw the animated sprite and also to set the view of the render window to center on the player object.
void Player::Draw(sf::RenderWindow &window)
{
	if (m_isAlive)
	{
		window.draw(m_sprite);

		window.setView(m_view);

		for (bulletIterator = bulletVector.begin(); bulletIterator != bulletVector.end(); ++bulletIterator)
		{
			if ((*bulletIterator)->getAlive())
			{
				(*bulletIterator)->Draw(window);
				//	cout << "bull update" << endl;
			}
		}
	}
}

float Player::getFireRate()
{
	return fireRate;
}

void Player::setFireRate(float rate)
{
	fireRate = rate;
}

void Player::update(float time)
{
	if (m_health <= 0)
	{
		m_isAlive = false;
	}
	if (m_isAlive)
	{
		fireTime += fireClock.getElapsedTime();

		//m_position += m_velocity;

		if (fireTime.asMilliseconds() > (5000 / fireRate))
		{
			//	std::cout << "bullet timeout" << endl;

			//	m_isAlive = false;
			canFire = true;

		}
		else
		{
			canFire = false;
		}


		//m_view.setCenter(m_sprite.getPosition());

		m_sprite.update(sf::seconds(0.05));

		m_sprite.setPosition(m_position);

		// check collisions with wall
		auto iter = m_walls.begin();
		auto endIter = m_walls.end();

		for (; iter != endIter; iter++) {
			checkCollisions((*iter), time);
		}


		m_velocity.x = sin((3.14 / 180)*angle) * speed;// * t.asSeconds();


		m_velocity.y = cos((3.14 / 180)*angle)* speed; //* t.asSeconds();

		if (speed < 0.2f)
		{
			speed = 0.2f;
		}


		m_position = m_position + m_velocity;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			if (speed < maxSpeed)
			{
				speed += 1;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			if (speed > minSpeed)
			{
				speed -= 0.1;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			angle += 5;
			m_sprite.rotate(-5);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			angle -= 5;
			m_sprite.rotate(5);
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			if (canFire == true)
			{

				float mag = m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y;

				mag = sqrt(mag); //length of vector

				bulletVector.push_back(new Projectile(m_position, m_sprite.getRotation(), mag, m_velocity));
				//	bulletVector.front()->initialise(m_position, angle, m_velocity);

				std::cout << "bang" << endl;

				fireClock.restart();
				fireTime = sf::Time::Zero;
			}
		}


		if (angle > 360)
		{
			angle -= 360;
		}
		if (angle < -360)
		{
			angle += 360;
		}



		m_sprite.setPosition(m_position); //set position of sprite

										  //if (m_position.x > 0 && m_position.x < 1000) {
		m_view.setCenter(m_position);
		//}

		int count = 0;

		for (bulletIterator = bulletVector.begin(); bulletIterator != bulletVector.end(); ++bulletIterator)
		{
			if ((*bulletIterator)->getAlive())
			{
				(*bulletIterator)->update(time);
				//	cout << "bull update" << endl;
			}
		//	cout << "bull update" << endl;
		}

		radarSprite.setPosition(m_position);
	}
}


void Player::checkCollisions(Wall* wall, float deltaTime) {
	// checks for intersection between the predator and the wall

	if (m_sprite.getGlobalBounds().intersects(wall->getSprite().getGlobalBounds()))
	{
		m_position -= m_velocity;

	//	cout << "intersect" << endl;

	}




}

std::vector<Projectile*> Player::getBullets()
{
	return bulletVector;
}

float Player::getHealth()
{
	return m_health;
}

bool Player::getAlive()
{
	return m_isAlive;
}

sf::Vector2f Player::getPosition()
{
	return m_position;
}

sf::Vector2f& Player::getPositionRef()
{
	return m_position;
}

sf::Vector2f Player::getVelocity()
{
	return m_velocity;
}

void Player::setAlive(bool alive)
{
	m_isAlive = alive;
}

void Player::setHealth(float healthChange)
{
	m_health += healthChange;

	if (m_health < 1) {
		m_isAlive = false;
	}
	else if (m_health > m_maxHealth) {
		m_health = m_maxHealth;
	}
}

void Player::setPosition(sf::Vector2f position)
{
	m_position = position;
}

void Player::setVelocity(sf::Vector2f velocity)
{
	m_velocity = velocity;
}

sf::FloatRect Player::getRect()
{
	return m_sprite.getGlobalBounds();
}

bool Player::getShielded() {
	return m_shielded;
}

void Player::setShieled(bool shielded) {
	m_shielded = shielded;
}
