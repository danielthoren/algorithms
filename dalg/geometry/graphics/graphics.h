#include <SFML/Graphics.hpp>

#include "../point.h"

namespace dg
{

    class Graphics
    {
    public:
	Graphics(unsigned width, unsigned height, std::string window_name) :
	    window(sf::VideoMode(width, height), window_name),
	    index{0};
	    {
		window.display();
	    }

	sf::RenderWindow& get_window()
	    {
		return window;
	    }

	void draw(sf::Shape const& shape)
	    {
		window.draw(shape);
	    }

    private:
	sf::RenderWindow window;

	std::map<unsigned, sf::Shape*> shapes;
	unsigned index;
    };

}

