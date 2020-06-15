#include "header.hpp"


//CLASS USED FOR DISPLAYING SQUARE
class Square_2D
{
protected:
	sf::RectangleShape item_shape;
	int pos_x, pos_y;	
	sf::Texture item_texture;

public:	
	//TEXTURE MANIPULATION METHODS
	int load_texture(std::string filename)
	{
		if(!item_texture.loadFromFile(filename,sf::IntRect(0,0,item_shape.getSize().x,item_shape.getSize().y)))return -1;
		item_texture.setSmooth(true);
		//std::cout<<"Loaded from file: "<<filename; //DEBUGGING		
	}
	
	void set_texture() //must be used in screen loop 
	{
		item_shape.setTexture(&item_texture);
	}
	
	void plain_color()//for debugging
	{
		item_shape.setFillColor(sf::Color::Blue);
	}

	//CHARACTER POSITION CONTROL
	void set_position()
	{
		item_shape.setPosition(pos_x,pos_y);
	}
	void set_position(int x,int y)
	{
		item_shape.setPosition(x,y);
	}	

	//USED IN DRAWING
	sf::RectangleShape get_shape()
	{
		return item_shape;
	}

	//CONSTRUCTORS	
	Square_2D(int size_x,int size_y,std::string filename)
	{	
		item_shape.setSize(sf::Vector2f(size_x,size_y));	
		if(load_texture(filename)!=-1) set_texture();				
	}

	Square_2D(){}	
};