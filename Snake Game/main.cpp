#include <iostream>
#include <SFML/Graphics.hpp>

#define W_WIDTH		640
#define W_HEIGHT	480

#define S_SIZE		W_WIDTH / 10
#define B_RADIUS	W_WIDTH / 20
//constexpr auto RATIO = W_WIDTH / W_HEIGHT;

//#define S_WIDTH		W_WIDTH / 20
//#define S_HEIGHT	S_WIDTH / RATIO

/* TODO LIST:
   + Finish detectCollision()
   + Add handleCollision() method on Ball
*/

enum Direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT
};

// Returns the side where the subject collided with the object
Direction detectCollision(const sf::Shape& sub, const sf::Shape& obj)
{
	// Subject
	sf::FloatRect subBounds = sub.getGlobalBounds();
	sf::FloatRect objBounds = obj.getGlobalBounds();

	// TODO: 
	// Detect collision Direction
	// Return collision Direction

}

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
		sf::Vector2f size = m_shape.getSize();
		// TODO:
		// ADD COLLISION

		switch (dir)
		{
		case UP:
			if (position.y <= 0) return;
			m_shape.setPosition(position.x, position.y - m_speed);
			break;
		case RIGHT:
			if (position.x + size.x >= W_WIDTH) return;
			m_shape.setPosition(position.x + m_speed, position.y);
			break;
		case DOWN:
			if (position.y + size.y >= W_HEIGHT) return;
			m_shape.setPosition(position.x, position.y + m_speed);
			break;
		case LEFT:
			if (position.x <= 0) return;
			m_shape.setPosition(position.x - m_speed, position.y);
			break;
		}
	}

	// TODO:
	// Create Reset Method
	// Create Growing Method
	// Create Losing Method
};

class Ball
{
public:
	sf::CircleShape m_circle;
	float				m_speedX;
	float				m_speedY;

	Ball()
		: m_circle(B_RADIUS)
		, m_speedX(0.1f)
		, m_speedY(0.1f)
	{
		m_circle.setFillColor(sf::Color::Red);
		m_circle.setPosition(W_WIDTH / 2, W_HEIGHT / 2);
	}

	void bounceBall()
	{
		sf::FloatRect bounds = m_circle.getGlobalBounds();
		sf::Vector2f position = m_circle.getPosition();

		if (bounds.left <= 0)
			m_speedX = std::abs(m_speedX);

		else if (bounds.left + bounds.width >= W_WIDTH)
			m_speedX = -std::abs(m_speedX);
			
		else if (bounds.top + bounds.height >= W_HEIGHT)
			m_speedY = -std::abs(m_speedY);
			
		else if (bounds.top <= 0) 
			m_speedY = std::abs(m_speedY);

		m_circle.setPosition(position.x + m_speedX, position.y + m_speedY);
	}

};

// TODO:
// Create Pill Struct

int main(void)
{
	sf::RenderWindow window(sf::VideoMode(W_WIDTH, W_HEIGHT), "Snake Game");

	Snake snake(100, 100);
	Ball ball;

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
		window.draw(ball.m_circle);
		ball.bounceBall();
		window.display();
	}

	return 0;
}