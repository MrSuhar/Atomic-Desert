#include "2d_item.cpp"

class Armour : public Square_2D
{
private:
	int armour;
	int durability;
	int value;
public:	
	//FUNCTION USED FOR REDCING DAMAGE TO PLAYER
	void defend(int damage)//,Character *target_of_usage)
	{
		if(durability>0)
		{
			//target_of_usage->change_hp(damage-armour);
			durability--;
			if(durability==0)
			{
				load_texture("./Textures/Armours/rags.png");
				set_texture();
			}					
			return;
		}
		else if(durability==0)return;						
	}

	//FUNCTION USED FOR CHECKING WHETER ITEM WAS USED BY PLAYER
	bool used(int x,int y, Character *target_of_usage)
	{
		border=item_shape.getGlobalBounds();
		if(border.contains(x,y))
		{
			std::cout<<"Armour is: "<<armour<<std::endl;
			return true;
		}
		return false;
		//else {std::cout<<"Border doesn't contain"<<std::endl;}
	}

	int get_armour(){return armour;}
	int get_durability() {return durability;}
	int get_value() {return value;}

	//CONSTRUCTOR
	Armour(int arm,int dur,int val,std::string filename)
	{
		armour=arm;
		durability=dur;
		value=val;
		item_shape.setSize(sf::Vector2f(50,50));
		if(load_texture(filename)!=-1) set_texture();
		border=item_shape.getLocalBounds();					
	}

	Armour(){};
	~Armour(){};	
};

//USED FOR DISPLAING EQ AND KEEPING TRACK OF ITEMS
class Inventory
{
protected:
	sf::RectangleShape backpack_background;
	bool opened=false;
	//CURRENT EMPTY ITEM SPACE
	int item_x=0,item_y=0;
	sf::Texture background_texture; 
	
	//USED FOR STORING ITEMS 
	std::variant<Item_medicine,Armour> items[4][4];

public:
	//CONSTRUCTOR
	Inventory()
	{			
	backpack_background.setSize(sf::Vector2f(320,240));
	backpack_background.setPosition(RES_X/5,RES_Y/5);
	//backpack_background.setFillColor(sf::Color::Cyan);	
	background_texture.loadFromFile("./Textures/camouflage.png",(sf::IntRect(0,0,320,240)));
	backpack_background.setTexture(&background_texture);
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
					std::size_t a=items[i][j].index();
					switch (a)
					{
						case 0:
							screen->draw(std::get<0>(items[i][j]).get_shape());
							break;
						case 1:
							screen->draw(std::get<1>(items[i][j]).get_shape());
							break;
					}					
				}				
			} //work in progress
		}		
	}
	//OPENING INVENTORY AND CLOSING INVENTIORY
	void set_open(bool setter){opened=setter;}
	bool get_open(){return opened;}
		
	//ADDING ITEM TO EQUIPEMENT work in progress	
	void add_item(std::variant<Item_medicine,Armour> item)//Will need to change for UNION of all items
	{
		if(item_y<=3)
		{
			items[item_x][item_y]=item;
			std::size_t a=items[item_x][item_y].index();
					switch (a)
					{
						case 0:
							std::get<0>(items[item_x][item_y]).set_position(item_x*80+RES_X/5+15,item_y*60+RES_Y/5+5);
							break;
						case 1:
							std::get<1>(items[item_x][item_y]).set_position(item_x*80+RES_X/5+15,item_y*60+RES_Y/5+5);
							break;
					}			
			item_x++; 
			if(item_x>=4)
				{
					item_x=0;
					item_y++;
				}	
			//item.set_position(item_x*80+RES_X/5,item_y*60+RES_Y/5);
		}
	};

	/*
	void add_item(A item)//Will need to change for UNION of all items
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
	*/

	//CHECKING WHETHER ITEM WAS CLICKED ON
	void using_items(sf::Vector2i mouse_position,Character *player)
	{
		//std::cout<<"Checking what was clicked in eq"<<std::endl;
		//std::cout<<"Mouse x: "<<mouse_position.x<<" Mouse y: "<<mouse_position.y<<std::endl;
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{		
				std::size_t a=items[i][j].index();
					switch (a)
					{
						case 0:
							if(std::get<0>(items[i][j]).used((int) mouse_position.x,(int) mouse_position.y,player))
								{
									Item_medicine a;
									items[i][j]=a;
									return;
								}
							break;
						case 1:
							if(std::get<1>(items[i][j]).used((int) mouse_position.x,(int) mouse_position.y,player))
								{
									Item_medicine a;
									items[i][j]=a;
									return;
								}
							break;
					}							
			}
		}
	}
	

};