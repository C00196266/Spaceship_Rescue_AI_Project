#pragma once

#include "stdafx.h"

class Tile {
public:
	Tile() {};
	Tile(sf::Vector2f pos);

	void loadImage();

	void render(sf::RenderWindow &window);

	//sf::Vector2f getPos();

protected:
	sf::Vector2f m_pos;

	sf::Image m_image;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	float m_width;
	float m_height;
};

//private:
//	Rect m_rectangle;
//	Colour m_colour;
//
//public:
//	Platform();
//	~Platform();
//	Platform(Point2D pos, float worldUnit);
//	Platform(Rect r);
//
//	void Render(Renderer & r);
//
//
//
//	void Update(unsigned int deltaTime);
//
//	void CheckBounds(int width, int height);
//
//	Rect getRect();
//
//	GameObjectType type;
//
//	void setColliding(bool colliding);