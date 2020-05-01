#include <SFML/Graphics.hpp>
#include <string>
#include <map>

#include "../point.h"

class Graphics
{
public:
    Graphics(unsigned width, unsigned height, std::string window_name) :
	window(sf::VideoMode(width, height), window_name),
	index{0};
	{
	    window.display();
	}

    void add_circle(std::pair<int,int> pos,
		     double radius,
		     sf::Color color = sf::Color::Green)
	{
	    sf::CircleShape* circle = new sf::CircleShape(radius);
	    circle->setFillColor(color);
	    shapes[index] = dynamic_cast<sf::Shape*>(circle);
	    index++;
	}

    sf::RenderWindow& get_window()
	{
	    return window;
	}

    void draw()
	{
	    while (window.isOpen())
	    {
		sf::Event event;
		while (window.pollEvent(event))
		{
		    // "close requested" event: we close the window
		    if (event.type == sf::Event::Closed)
			window.close();
		}

		window.clear();

		for (auto it = shapes.begin(); it != shapes.end(); it++)
		{
		    window.draw(*it->second);
		}
	    }
	}

private:
    sf::RenderWindow window;

    std::map<unsigned, sf::Shape*> shapes;
    unsigned index;
};


int main()
{
    Graphics g(1000, 1000, "test");

    g.draw_circle({0,0}, 100);

    while (true)
    {
	continue;
    }

    return 0;
}
