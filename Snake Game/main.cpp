#include <iostream>
#include <SFML/Graphics.hpp>

#define W_WIDTH		640
#define W_HEIGHT	480

// Player and Ball
#define P_HEIGHT	W_HEIGHT / 30
#define P_WIDTH		P_HEIGHT * 5
#define B_RADIUS	W_WIDTH / 60

/* TODO LIST:
   + Finish detectCollision()
   + Add handleCollision() method on Ball
*/

enum class Direction
{
	None,
	Up,
	Right,
	Down,
	Left
};

// Returns the side where the subject collided with the object
Direction detectCollision(const sf::Shape& sub, const sf::Shape& obj)
{
	// Subject
	sf::FloatRect subBounds = sub.getGlobalBounds();
	sf::FloatRect objBounds = obj.getGlobalBounds();


	if (subBounds.intersects(objBounds))
	{
		float dx = subBounds.left + subBounds.width / 2 - (objBounds.left + objBounds.width / 2);
		float dy = subBounds.top + subBounds.height / 2 - (objBounds.top + objBounds.height / 2);

		float overlapX = subBounds.width / 2 + objBounds.width / 2 - std::abs(dx);
		float overlapY = subBounds.height / 2 + objBounds.height / 2 - std::abs(dy);

		// y axis collision
		if (overlapX >= overlapY)
		{
			if (dy > 0)
				return Direction::Up;
			else
				return Direction::Down;
		}
		else
		{
			if (dx > 0)
				return Direction::Left;
			else
				return Direction::Right;
		}
	}

	return Direction::None;
}

class Player
{
public:
	sf::RectangleShape	m_shape;
	int					m_speed;

	Player(const int xPosition, const int yPosition) 
		: m_shape(sf::Vector2f(20.0f, 20.0f))
		, m_speed(P_HEIGHT)
	{
		m_shape.setPosition(xPosition, yPosition);
		m_shape.setSize(sf::Vector2f(P_WIDTH, P_HEIGHT));
	}

	void moveSnake(Direction dir)
	{
		sf::Vector2f position = m_shape.getPosition();
		sf::Vector2f size = m_shape.getSize();

		switch (dir)
		{
		case Direction::Up:
			if (position.y <= 0) return;
			m_shape.setPosition(position.x, position.y - m_speed);
			break;
		case Direction::Right:
			if (position.x + size.x >= W_WIDTH) return;
			m_shape.setPosition(position.x + m_speed, position.y);
			break;
		case Direction::Down:
			if (position.y + size.y >= W_HEIGHT) return;
			m_shape.setPosition(position.x, position.y + m_speed);
			break;
		case Direction::Left:
			if (position.x <= 0) return;
			m_shape.setPosition(position.x - m_speed, position.y);
			break;
		}
	}
};

class Ball
{
public:
	sf::CircleShape m_circle;
	float				m_speedX;
	float				m_speedY;

	Ball()
		: m_circle(B_RADIUS)
		, m_speedX(0.08f)
		, m_speedY(0.08f)
	{
		m_circle.setFillColor(sf::Color::Red);
		m_circle.setPosition(W_WIDTH / 2, W_HEIGHT / 2);
	}

	void bounceBall(Direction dir)
	{
		sf::FloatRect bounds = m_circle.getGlobalBounds();
		sf::Vector2f position = m_circle.getPosition();

		if (bounds.left <= 0 || dir == Direction::Left)
			m_speedX = std::abs(m_speedX);

		else if (bounds.left + bounds.width >= W_WIDTH || dir == Direction::Right)
			m_speedX = -std::abs(m_speedX);
			
		else if (bounds.top + bounds.height >= W_HEIGHT || dir == Direction::Down)
			m_speedY = -std::abs(m_speedY);
			
		else if (bounds.top <= 0 || dir == Direction::Up) 
			m_speedY = std::abs(m_speedY);

		m_circle.setPosition(position.x + m_speedX, position.y + m_speedY);
	}

};

int main(void)
{
	sf::RenderWindow window(sf::VideoMode(W_WIDTH, W_HEIGHT), "Player Game");

	Player snake(300, 420);
	Ball ball;

	std::vector<sf::RectangleShape> blocks;
	
	for (size_t i = 0; i < 4 ; ++i)
	{
		sf::RectangleShape block(sf::Vector2f(P_WIDTH, P_HEIGHT));
		block.setPosition((P_WIDTH + 30)*i + 130, 80);
		block.setFillColor(sf::Color::Green);
		blocks.push_back(block);
	}

	Direction collisionDir;

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
					snake.moveSnake(Direction::Left);
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					snake.moveSnake(Direction::Right);
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
					snake.moveSnake(Direction::Up);
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					snake.moveSnake(Direction::Down);
				break;
			default:
				break;
			}
		}
		window.clear();
		for (sf::RectangleShape &block : blocks)
		{
			window.draw(block);
		}
		window.draw(snake.m_shape);
		window.draw(ball.m_circle);
		collisionDir = detectCollision(ball.m_circle, snake.m_shape);
		
		Direction blockCollisionDir = Direction::None;
		int collisionIndex = -1; // need to initialize the variable
		for (size_t i = 0; i < blocks.size(); ++i)
		{
			blockCollisionDir = detectCollision(ball.m_circle, blocks[i]);
			if (blockCollisionDir != Direction::None) {
				collisionIndex = i;
				collisionDir = blockCollisionDir;
				break; // Break loop if any block collision detected
			}
		}

		ball.bounceBall(collisionDir);

		// Removes any block the ball collides with
		if (collisionIndex != -1)
			blocks.erase(blocks.begin() + collisionIndex);

		window.display();
	}

	return 0;
}