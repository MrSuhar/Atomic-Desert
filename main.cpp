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
	screen.create(sf::VideoMode(RES_X, RES_Y),VERSION,sf::Style::Default,settings);
	//CLOCK CREATION
	sf::Clock Clock;
	int frame_time = 16; // ms

	sf::Event event;

	//CREATING CHARACTER OBJECT
	Character Player_1(100, 100, "./Textures/Player.png");
	Player_1.set_texture();
	Player_1.set_position();

	//MAIN LOOP
	while(screen.isOpen())
	{
		Clock.restart();
		sf::Event event;	
		
		
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
				}
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			Player_1.gain_speed(0, -Player_1.acc);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			Player_1.gain_speed(0, Player_1.acc);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			Player_1.gain_speed(Player_1.acc, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			Player_1.gain_speed(-Player_1.acc, 0);
		}


		Player_1.move();

		screen.clear(sf::Color::Yellow);
		screen.draw(Player_1.get_shape());
		screen.display();

		//CONTROLING FPS
		sf::Time time = Clock.getElapsedTime();
		sf::Int32 passed = time.asMilliseconds();
		while (frame_time > passed)
		{ 
			time = Clock.getElapsedTime(); // looping while waiting for next frame
			passed = time.asMilliseconds();
		}
	}

	//DLA WINDOWSA
	// system("pause");
	return 0;
}