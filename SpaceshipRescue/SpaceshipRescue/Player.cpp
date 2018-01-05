#include "Player.h"
#include <iostream>
using namespace std;

Player::Player()
{

}

void Player::Init()
{
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

	m_sprite.setAnimation(m_animation);
	m_sprite.setScale(0.2, 0.2);


	m_view.setCenter(m_sprite.getPosition());
}


void Player::Update()
{
	m_view.setCenter(m_sprite.getPosition());

	m_sprite.update(sf::seconds(0.05));

	m_sprite.setPosition(m_pos);



	cout << m_pos.y << endl;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		m_pos.x += 1; 
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		m_pos.y -= 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		m_pos.y += 1; 
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		m_pos.x -= 1;
	}

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

