#pragma once

#include<vector>
using namespace sf;
using namespace std;
#define ITEM_HEAL 0
#define ITEM_BULLET 1

class Item
{
private:
	Sprite Itemsprite;
	Texture ItemTexture;
	int Random;
	int type;

public:

	Item(Texture* texture, float size, int type) 
	{
		this->Itemsprite.setTexture(*texture);
		this->Itemsprite.setScale(Vector2f(size, size));
		this->Itemsprite.setPosition(rand() % 1000, (rand() % 500 - 400) + 400);
		this->type = type;
		
	}



	void update()
	{
		
	}
	
	
	void draw(RenderWindow* window)
	{
		window->draw(this->Itemsprite);
	}

	void setType(int type) {

		this->type = type;
	}
	int getType() {

		return this->type;
	}

	inline const FloatRect getGlobalBounds()const
	{
		return this->Itemsprite.getGlobalBounds();
	}

	inline Vector2f getPosition()
	{
		return this->Itemsprite.getPosition();
	}

	

};