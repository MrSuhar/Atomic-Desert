#include "header.hpp"

class Character
{
protected:
	sf::CircleShape character_shape;
	int pos_x, pos_y;
	float vx, vy;
	float max_spd;
	sf::Texture character_texture;

public:
	float acc; // default acceleration

	//TEXTURE MANIPULATION METHODS
	int load_texture(std::string filename)
	{
		if(!character_texture.loadFromFile(filename,sf::IntRect(0,0,20,20)))return -1;
		character_texture.setSmooth(true);
		//std::cout<<"Loaded from file: "<<filename; //DEBUGGING		
	}
	
	void set_texture() //must be used in screen loop 
	{
		character_shape.setTexture(&character_texture);
	}
	
	void plain_color()//for debugging
	{
		character_shape.setFillColor(sf::Color::Blue);
	}

	//CHARACTER POSITION CONTROL
	void set_position()
	{
		character_shape.setPosition(pos_x,pos_y);
	}
	void set_position(int x,int y)
	{
		character_shape.setPosition(x,y);
	}
	void move() // moving player according to his speed
	{
		if (pos_x + vx < 0 || RES_X < pos_x + vx) // halting if approaching window edge
			vx = 0;
		else
			pos_x += vx;

		if (pos_y + vy < 0 || RES_Y < pos_y + vy)
			vy = 0;
		else
			pos_y += vy;

		character_shape.setPosition(pos_x, pos_y);
	}

	void gain_speed(float ax, float ay)
	{
		if (-max_spd < vx + ax && vx + ax < max_spd) // must not be faster than max_spd
			vx += ax;

		if (-max_spd < vy + ay && vy + ay < max_spd)
			vy += ay;
	}

	//USED IN DRAWING
	sf::CircleShape get_shape()
	{
		return character_shape;
	}

	//CONSTRUCTORS
	
	Character(int x,int y,std::string filename)
	{	
		character_shape.setRadius(20.);	
		if(load_texture(filename)!=-1) set_texture();
		pos_x=x;
		pos_y=y;
		vx = 0;
		vy = 0;
		acc = 1;
		max_spd = 5;
	}	
};