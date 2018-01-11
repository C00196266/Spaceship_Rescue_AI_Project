#include "Player.h"
#include <iostream>
using namespace std;

Player::Player()
{

}


Player::~Player()
{

}

void Player::Init()
{

	m_isAlive = true; //for test only
	speed = 0;
	maxVelo = sf::Vector2f(0, -2);
	minVelo = sf::Vector2f(0, 0);
	angle = 0;
	minSpeed = 0;
	maxSpeed = 6;





	//initialization logic for player
	keyUp = true;

	m_position = sf::Vector2f(0, 0);

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

	sf::Int32 msec = 50;

	m_sprite.setFrameTime(sf::milliseconds(msec)); //convert to time

	m_sprite.setOrigin(24, 23.5f);
	m_position = sf::Vector2f(240, 300);

	m_sprite.setRotation(180);
	m_sprite.setAnimation(m_animation);
	m_sprite.setScale(0.6, 0.6); //was 0.2

	m_view.zoom(10.0f);
	m_view.setCenter(m_sprite.getPosition());


}



//Draw method used to draw the animated sprite and also to set the view of the render window to center on the player object.
void Player::Draw(sf::RenderWindow &window)
{

	window.draw(m_sprite);// , sf::BlendAdd);

	//int count = 0;
	//for (bulletIterator = bulletVector.begin(); bulletIterator != bulletVector.end(); bulletIterator++)
	//{
	//	(bulletIterator*)->

	//	if (bulletIterator->getAlive())
	//	{

	//		bulletIterator->Draw(window);
	//	//	count++;
	//	}
	//}

	for (bulletIterator = bulletVector.begin(); bulletIterator != bulletVector.end(); ++bulletIterator) 
	{
		if ((*bulletIterator)->getAlive())
		{
			(*bulletIterator)->Draw(window);
		}
	}

	window.setView(m_view);




}




void Player::update(float time)
{
//	m_radar.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));

	//m_view.setCenter(m_sprite.getPosition());

	m_sprite.update(sf::seconds(0.05));

	m_sprite.setPosition(m_position);



	m_velocity.x = sin((3.14 / 180)*angle) * speed;// * t.asSeconds();


	m_velocity.y = cos((3.14 / 180)*angle)* speed; //* t.asSeconds();



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

		float mag = m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y;

		mag = sqrt(mag); //length of vector

		bulletVector.push_back(new Projectile(m_position, m_sprite.getRotation(), mag, m_velocity));

		std::cout << "bang" << endl;
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

	m_view.setCenter(m_position);
	

	int count = 0;

	for (bulletIterator = bulletVector.begin(); bulletIterator != bulletVector.end(); ++bulletIterator)
	{
		if ((*bulletIterator)->getAlive())
		{
			(*bulletIterator)->update(0, sf::Vector2f(0, 0), time);
			cout << "bull update" << endl;
		}
	}

	//int count = 0;
	//for (bulletIterator = bulletVector.begin(); bulletIterator != bulletVector.end(); bulletIterator++)
	//{
	//	if (bulletIterator->getAlive())
	//	{

	//		bulletIterator->update(count, m_position, time);
	//		count++;
	//	}
	//}
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
	m_health -= healthChange;
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
