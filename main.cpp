#include "header.hpp"
#include "characters.cpp"
#define VERSION "Atomic Desert ver_0.01 First Hero Appears!"


int main()
{
	//SETTING CREATION
	sf::ContextSettings settings;
	settings.antialiasingLevel=2;
	//WINDOW CREATION
	sf::RenderWindow screen;
	screen.create(sf::VideoMode(1600,1200),VERSION,sf::Style::Default,settings);

	sf::Event event;

	while(screen.isOpen())
	{
		sf::Event event;
		
		//CREATING CHARACTER OBJECT
		Character Player_1(100,100,"./Textures/Player.png");
		Player_1.set_texture();
		Player_1.set_position();
		
		//MAIN LOOP
		while(screen.pollEvent(event))
		{
			if(event.type==sf::Event::Closed) screen.close();
			//KEYBOARD HANDLING WORK IN PROGRESS
			if(event.type==sf::Event::KeyPressed)
			{
				switch(event.key.code)
				{
					case sf::Keyboard::Escape:
					screen.close();
					break;
					case sf::Keyboard::W:
					break;
				}
			}
		}

		screen.clear(sf::Color::Yellow);
		screen.draw(Player_1.get_shape());
		screen.display();
	}

	//DLA WINDOWSA
	// system("pause");
	return 0;
}