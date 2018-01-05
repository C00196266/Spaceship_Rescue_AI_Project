#include "SFML\Graphics.hpp"
#include "AnimatedSprite.hpp"

//Class definition for the Player game object
class Player {
private:
	sf::View m_view;
	sf::Vector2f m_pos;
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

public:
	Player();
	void Init();
	void Update();
	void Draw(sf::RenderWindow &window);
	sf::Vector2f GetPosition();
};
