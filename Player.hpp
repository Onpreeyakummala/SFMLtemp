#pragma once
#include "Bullet.hpp"
#include<vector>


using namespace std;

class Player 
{

private:

    RenderWindow* window;
    Sprite sprite;
    Texture texture;
    vector<Bullet>bullets;
    Texture bulletTexture;
    RectangleShape PlayerhpBar;
    RectangleShape PlayerhpBarBack; 
    int shootTime;
    int shootTimeMax;
    int hpPlayer;
    int hpPlayerMax; 
    int life;
    float dualShoot;

public:

    Player(RenderWindow* window)
    {
        this->window = window;
        this->texture.loadFromFile("Texture/Player/2.png");
        this->sprite.setTexture(this->texture);
        this->sprite.setPosition(960.f, 540.f);
        this->sprite.setOrigin(this->texture.getSize().x/2.f, this->texture.getSize().y / 2.f);
        this->sprite.setScale(Vector2f(0.5f,0.5f));
        this->hpPlayerMax = 10; // à´ÔÁ 100
        this->hpPlayer = hpPlayerMax;
        this->bulletTexture.loadFromFile("Texture/bullet2.png");
        this->shootTime = 0;
        this->shootTimeMax = 30;
        this->life = 3; // à´ÔÁ 3
        this->dualShoot = 0;
    }

    ~Player() 
    {

    }
 
    void updatePlayer() 
    {
      
        if (Keyboard::isKeyPressed(Keyboard::Key::D))
        {
            this->sprite.move(3.f, 0.f);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::A))
        {
            this->sprite.move(-3.f, 0.f);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::W))
        {
            this->sprite.move(0.f, -3.f);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::S))
        {
            this->sprite.move(0.f, 3.f);
        }
     

        if (Mouse::isButtonPressed(Mouse::Left)&&shootTime < 0)
        {
            Vector2f PlayerPos = Vector2f(sprite.getPosition().x, sprite.getPosition().y);
            Vector2f MousePos = Vector2f(Mouse::getPosition(*window));
            Vector2f aimDir = MousePos - PlayerPos;
            Vector2f aimDirNorm = aimDir / sqrt((aimDir.x * aimDir.x + aimDir.y * aimDir.y));
            if (dualShoot > 0)
            {
                Bullet bullet(&bulletTexture, aimDirNorm, this->sprite.getPosition() - Vector2f(45, 0));
                Bullet bullet2(&bulletTexture, aimDirNorm, this->sprite.getPosition() + Vector2f(45, 0));
                this->bullets.push_back(bullet);
                this->bullets.push_back(bullet2);
                this->shootTime = this->shootTimeMax;
                bullets.push_back(Bullet(&bulletTexture, aimDirNorm,this->sprite.getPosition())); //ÂÔ§ä´é3
                this->dualShoot--;
            }
            else
            {
                //¤ÇÒÁàÃçÇbullet
                Bullet bullet(&bulletTexture, aimDirNorm, this->sprite.getPosition() - Vector2f(45, 0));
                this->bullets.push_back(bullet);
                this->shootTime = this->shootTimeMax;
               
            }
        }
        else 
            this->shootTime--;
      
        

        //¢Íº¨Í

        if (sprite.getPosition().x < 0)
        {
            sprite.setPosition(Vector2f(0, sprite.getPosition().y));
        }
        if (sprite.getPosition().x > w - sprite.getGlobalBounds().width)
        {
            sprite.setPosition(Vector2f(w - sprite.getGlobalBounds().width, sprite.getPosition().y));
        }
        if (sprite.getPosition().y < 0)
        {
            sprite.setPosition(Vector2f(sprite.getPosition().x, 0));
        }
        if (sprite.getPosition().y > h - sprite.getGlobalBounds().height)
        {
            sprite.setPosition(Vector2f(sprite.getPosition().x, h - sprite.getGlobalBounds().height));
        }

        updatehp();

    }

  
    void draw() 
    {
        this->window->draw(sprite);
        for (size_t i = 0; i < bullets.size(); i++)
        {
            bullets[i].draw(*window);
        }
        this->window->draw(this->PlayerhpBarBack);
        this->window->draw(this->PlayerhpBar);
    }
   
    void updatehp()
    {


        this->PlayerhpBarBack.setSize(Vector2f(120.f, 15.f));
        this->PlayerhpBarBack.setFillColor(Color::Black);
        this->PlayerhpBarBack.setPosition(Vector2f(this->sprite.getPosition().x-60.f, this->sprite.getPosition().y - 85.f));

        this->PlayerhpBar.setSize(Vector2f((getHp()*120)/100.f, 15.f));
        this->PlayerhpBar.setFillColor(Color::Green);
        this->PlayerhpBar.setPosition(this->PlayerhpBarBack.getPosition());

    }
   
    void resetBullet()
    {
        dualShoot = 0;
    }
   
    void resetplayer()
    {
        this->sprite.setPosition(960.f, 540.f);
    }
    void getDamage(int dm)
    {
        this->hpPlayer += dm;
    }
    void lifereset()
    {
        this->life = 3;
    }

    void deletelife()
    {
        this->life -= 1;
    }

    void setHpMax()
    {
        this->hpPlayer = this->hpPlayerMax;
    }

    int getlife()
    {
        return this->life;
    }

    int getHp()
    {
        return this->hpPlayer;
    }

    int getHpMax()
    {
        return this->hpPlayerMax;
    }
   

    inline void setDualShoot(float time) 
    { 
        dualShoot = time; 
    }

    inline Vector2f getPosition()
    {
        return this->sprite.getPosition();
    }

    inline vector<Bullet>& getBullet()
    {
        return this->bullets;
    }

    inline const FloatRect getGlobalBounds()const
    {
        return this->sprite.getGlobalBounds();
    }
    

};
