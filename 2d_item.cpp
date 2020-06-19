#include "header.hpp"
#include "characters.cpp"


//CLASS USED FOR DISPLAYING SQUARE
class Square_2D
{
protected:
	sf::RectangleShape item_shape;
	int pos_x, pos_y;	
	sf::Texture item_texture;
	sf::FloatRect border; //USED FOR CHECKING IF ITEM WAS CLICKED

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

//CAN BE USED FOR BOTH HEALING AND DAMAGE,
//INHERITED CLASSES CAN GIVE BUFFS AS WELL AS HP
class Item_medicine : public Square_2D
{
private:
	int hp_change;
public:	
	//FUNCTION USED FOR CHECKING WHETER ITEM WAS USED BY PLAYER
	bool used(int x,int y, Character *target_of_usage)
	{
		border=item_shape.getGlobalBounds();
		if(border.contains(x,y))
		{
			//std::cout<<"ADDED HP EQUALS: "<<hp_change<<std::endl; //used in debug
			target_of_usage->change_hp(hp_change);
			return true;
		}
		return false;
		//else {std::cout<<"Border doesn't contain"<<std::endl;}
	}

	//CONSTRUCTOR
	Item_medicine(int a,std::string filename)
	{
		hp_change=a;
		item_shape.setSize(sf::Vector2f(50,50));
		if(load_texture(filename)!=-1) set_texture();
		//border=item_shape.getLocalBounds();					
	}

	Item_medicine(){};
};

//USED FOR DISPLAING EQ AND KEEPING TRACK OF ITEMS
class Inventory
{
protected:
	sf::RectangleShape backpack_background;
	bool opened=false;
	//CURRENT EMPTY ITEM SPACE
	int item_x=0,item_y=0;
	
	//USED FOR DISPLAYING in previous version	
	//Square_2D items[4][4];	

	Item_medicine items[4][4]; //Will need to change for UNION of all items

public:
	//CONSTRUCTOR
	Inventory()
	{			
	backpack_background.setSize(sf::Vector2f(320,240));
	backpack_background.setPosition(RES_X/5,RES_Y/5);
	backpack_background.setFillColor(sf::Color::Cyan);
	}
	
	//DISPLAYING INVENTORY AND ITS CONTENTS
	void disp_eq(sf::RenderWindow *screen)
	{	
		if(opened)
		{
		screen->draw(backpack_background);
			for(int i=0;i<4;i++)//i<item_x;i++)
			{
				for(int j=0;j<4;j++)
				{
					screen->draw(items[i][j].get_shape());
				}				
			} //work in progress
		}		
	}
	//OPENING INVENTORY AND CLOSING INVENTIORY
	void set_open(bool setter){opened=setter;}
	bool get_open(){return opened;}
		
	//ADDING ITEM TO EQUIPEMENT work in progress	
	void add_item(Item_medicine item)//Will need to change for UNION of all items
	{
		if(item_y<=3)
		{
			items[item_x][item_y]=item;
			items[item_x][item_y].set_position(item_x*80+RES_X/5+15,item_y*60+RES_Y/5+5);
			item_x++; 
			if(item_x>=4)
				{
					item_x=0;
					item_y++;
				}	
			//item.set_position(item_x*80+RES_X/5,item_y*60+RES_Y/5);
		}
	};

	//CHECKING WHETHER ITEM WAS CLICKED ON
	void using_items(sf::Vector2i mouse_position,Character *player)
	{
		//std::cout<<"Checking what was clicked in eq"<<std::endl;
		//std::cout<<"Mouse x: "<<mouse_position.x<<" Mouse y: "<<mouse_position.y<<std::endl;
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{				
				if(items[i][j].used((int) mouse_position.x,(int) mouse_position.y,player))
					{
						Item_medicine a;
						items[i][j]=a;
						return;
					}
			}
		}
	}
	

};