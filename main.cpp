#include "header.hpp"
//#include "characters.cpp"
#include "armour.cpp"

#define VERSION "Atomic Desert ver_0.04 ARMOUR"


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

	//CREATING BACKGROUND
	Square_2D background(RES_X,RES_Y,"./Textures/desert.png");

	//CREATING CHARACTER OBJECT
	Character Player_1(100, 100, "./Textures/Player.png");	
	Player_1.set_texture();
	Player_1.set_position();

	
	//CREATING ITEM OBJECT, inherited from Square_2D Class
	Item_medicine pain_killer(10,"./Textures/painkiller.jpg");
	Item_medicine small_poison(-10,"./Textures/poison.png");
	//CREATING ARMOUR ITEM
	Armour leather_jacket(10,1,100,"./Textures/Armours/leather_jacket.png");
	
	//CREATING INVENTORY OBJECT as for now it only displays objects "2D_square"
	Inventory Player_EQ;
	//FILLINg PLAYER'S INVENTORY WITH random stuff
	Player_EQ.add_item(pain_killer); //filling inventory with random stuff
	Player_EQ.add_item(small_poison);
	Player_EQ.add_item(leather_jacket);	
	Player_EQ.add_item(leather_jacket);
	Player_EQ.add_item(small_poison);	

	//HP BAR
		sf::Font font_omen;
		font_omen.loadFromFile("./Textures/Fonts/BloodOmen.ttf");		
		sf::Text hp_gauge("TEST",font_omen,30);
		hp_gauge.setFillColor(sf::Color::Red);
		hp_gauge.setPosition(0,RES_Y-70);

	//MUSIC
	sf::Music main_theme;
	if(!main_theme.openFromFile("./Sounds/desert_wind.ogg")) 
		{
			std::cout<<"Failed to load music"<<std::endl;
			return -14;
		};

	main_theme.play();
	main_theme.setLoop(true);


	// CREATING COLLISION OBJECTS
	Box test_box1(500, 500, 200, 100);
	Box test_box2(800, 100, 50, 50);
	std::vector<Box> box_list = { test_box1, test_box2 };
	

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
					case sf::Keyboard::I: //opening and closing EQ
						if(Player_EQ.get_open())
						{
							Player_EQ.set_open(false);
						}
						else Player_EQ.set_open(true);
					break;

				}
			}
			//HANDING MOUSE CLICKS
			if(event.type==sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{					
					//USING ITEMS IN EQ IF IT IS OPENED
					if(Player_EQ.get_open())
					{						
						Player_EQ.using_items(sf::Mouse::getPosition(),&Player_1);//Second argument decides who the item is used on
					}
				}
			}
		}

		//HANDLING MOVEMENT		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			Player_1.ver_acc = -1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			Player_1.ver_acc = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			Player_1.hor_acc = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			Player_1.hor_acc = -1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			Player_1.sprint = true;
		}

		
		Player_1.gain_speed();
		Player_1.move(box_list);

		//SETTING CURRENT HP
		hp_gauge.setString(std::to_string(Player_1.get_hp()));

		
		screen.clear(sf::Color::Black);
		screen.draw(background.get_shape());

		for (Box box : box_list)
			screen.draw(box.shape);
		screen.draw(Player_1.get_shape());
		Player_EQ.disp_eq(&screen);

		//HP_GAUGE
		screen.draw(hp_gauge);				

		//screen.draw()
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