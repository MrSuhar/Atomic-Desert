#include "header.hpp"
//#include "2d_item.cpp"
class Character
{
protected:
	sf::CircleShape character_shape;
	int pos_x, pos_y;
	float vx, vy;
	float max_spd;
	float acc; // default acceleration
	bool if_acc; // acceleration flag
	sf::Texture character_texture;

	//USED FOR COUNTING HP
	int hp=100; //BASIC HP AMOUNT

public:
	int hor_acc; // flags of horizontal and vertical acceleration
	int ver_acc; // can be -1, 0, 1

	//USED FOR CHAMGING HP FOR FIXED AMOUNT
	void change_hp(int a)
	{
		hp+=a;
		std::cout<<"Current hp is: "<<hp<<std::endl; //used for debug
	}	

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
	// CALCULATING AND SETTING PLAYER POSITIOn
	void move() 
	{
		if (pos_x + vx < 0 || RES_X < pos_x + vx) // halting if approaching window edge
			vx = 0;
		else
			pos_x += vx;

		if (pos_y + vy < 0 || RES_Y < pos_y + vy)
			vy = 0;
		else
			pos_y += vy;

		float slow = 0.05; // percent of max speed lost when not moving


		if (hor_acc == 0) // slowing character down if not moving
		{
			if (vx > 0)
				vx -= max_spd * slow;
			if (vx < 0)
				vx += max_spd * slow;
		}

		if (ver_acc == 0)
		{
			if (vy > 0)
				vy -= max_spd * slow;
			if (vy < 0)
				vy += max_spd * slow; 
		}			

		if_acc = false; // reseting player acceleration
		ver_acc = 0;
		hor_acc = 0;
		character_shape.setPosition(pos_x, pos_y);
	}

	void gain_speed()
	{		
		float acc_vect = sqrt(hor_acc * hor_acc + ver_acc * ver_acc) / sqrt(2); // this variable is multiplied with acc to remove higher diagonal acceleration, 0 if no acceleration

		if (acc_vect == 0)
		{
			if_acc = false;
			return;
		}

		float new_vx = vx + acc * acc_vect * hor_acc; // calculating new speed
		float new_vy = vy + acc * acc_vect * ver_acc;
		

		if (-max_spd < new_vx && new_vx < max_spd) // changing speed if possible
			vx = new_vx;
		if (-max_spd < new_vy && new_vy < max_spd)
			vy = new_vy;
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
		hor_acc = 0;
		ver_acc = 0;
	}

	Character()
	{}	
};