#include "header.hpp"

class Character
{
protected:
	sf::CircleShape character_shape;
	int pos_x,pos_y;
	sf::Texture character_texture;

public:

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
	}	
};