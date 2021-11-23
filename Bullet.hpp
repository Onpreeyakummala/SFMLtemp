#pragma once

class Bullet
{

private:

    Sprite sprite;
    Texture* texture;
    Vector2f direction;


public:
    Bullet(Texture* texture,Vector2f direction,Vector2f position)
    {
        this->texture = texture;
        this->sprite.setTexture(*this->texture);
        this->direction = direction;
        this->sprite.setPosition(position);
        this->sprite.setScale(0.2f, 0.2f);

    }

    ~Bullet()
    {

    }

    void updateBullet()
    {
        this->sprite.move(20.f * this->direction);
        

    }


    void draw(RenderWindow& window)
    {
        window.draw(this->sprite);


    }

    inline const FloatRect getGlobalBounds()const 
    { 
        return this->sprite.getGlobalBounds(); 
    }

};
