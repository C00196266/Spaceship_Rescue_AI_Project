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
	maxSpeed = 4;



	//initialization logic for player
	keyUp = true;
	m_pos = sf::Vector2f(0, 0);
	m_view = sf::View(m_pos, sf::Vector2f(360, 240));
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
	m_pos = sf::Vector2f(240, 300);

	m_sprite.setRotation(180);

	m_sprite.setAnimation(m_animation);
	m_sprite.setScale(0.3, 0.3); //was 0.2

	m_view.zoom(2.0f);
	m_view.setCenter(m_sprite.getPosition());
}



//Draw method used to draw the animated sprite and also to set the view of the render window to center on the player object.
void Player::Draw(sf::RenderWindow &window)
{

	window.draw(m_sprite);
	window.setView(m_view);
}

sf::Vector2f Player::GetPosition()
{
	return m_pos;
}

void Player::update(float time)
{

	//m_view.setCenter(m_sprite.getPosition());

	m_sprite.update(sf::seconds(0.05));

	m_sprite.setPosition(m_pos);



	m_velocity.x = sin((3.14 / 180)*angle) * speed;// * t.asSeconds();


	m_velocity.y = cos((3.14 / 180)*angle)* speed; //* t.asSeconds();



	m_position = m_position + m_velocity;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		if (speed < maxSpeed)
		{
			speed += 0.1;
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

	if (angle > 360)
	{
		angle -= 360;
	}
	if (angle < -360)
	{
		angle += 360;
	}

	/*cout << "angle: " << angle << endl;
	cout << "angleSPR: " << m_sprite.getRotation() << endl;


	cout << "x: " << std::to_string(m_velocity.y) << " y: " << std::to_string(m_velocity.y) << endl;

	cout << "speed: " << speed << endl;*/

	//m_position += m_velocity;

	m_sprite.setPosition(m_position); //set position of sprite
	
	//if (m_position.x > 0 && m_position.x < 1000) {
		m_view.setCenter(m_position);
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
