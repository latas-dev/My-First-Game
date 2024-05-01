#include <iostream>
#include <SFML/Graphics.hpp>

#define W_WIDTH		640
#define W_HEIGHT	480

#define S_SIZE		20
//constexpr auto RATIO = W_WIDTH / W_HEIGHT;

//#define S_WIDTH		W_WIDTH / 20
//#define S_HEIGHT	S_WIDTH / RATIO

enum Direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT
};

class Snake
{
public:
	sf::RectangleShape	m_shape;
	int					m_speed;
	//float				m_speedX;
	//float				m_speedY;

	Snake(const int xPosition, const int yPosition) 
		: m_shape(sf::Vector2f(20.0f, 20.0f))
		, m_speed(S_SIZE)
		//, m_speedX(S_WIDTH)
		//, m_speedY(S_HEIGHT)
	{
		m_shape.setPosition(xPosition, yPosition);
		m_shape.setSize(sf::Vector2f(S_SIZE, S_SIZE));
		//m_shape.setSize(sf::Vector2f(S_WIDTH, S_HEIGHT));
	}

	void moveSnake(Direction dir)
	{
		sf::Vector2f position = m_shape.getPosition();

		switch (dir)
		{
		case UP:
			m_shape.setPosition(position.x, position.y - m_speed);
			break;
		case RIGHT:
			m_shape.setPosition(position.x + m_speed, position.y);
			break;
		case DOWN:
			m_shape.setPosition(position.x, position.y + m_speed);
			break;
		case LEFT:
			m_shape.setPosition(position.x - m_speed, position.y);
			break;
		}
	}

	// TODO:
	// Create Reset Method
	// Create Growing Method
	// Create Losing Method
};

// TODO:
// Create Pill Struct

int main(void)
{
	sf::RenderWindow window(sf::VideoMode(W_WIDTH, W_HEIGHT), "Snake Game");

	Snake snake(100, 100);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					snake.moveSnake(LEFT);
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					snake.moveSnake(RIGHT);
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
					snake.moveSnake(UP);
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					snake.moveSnake(DOWN);
				break;
			default:
				break;
			}
		}
		window.clear();
		window.draw(snake.m_shape);
		window.display();
	}

	return 0;
}