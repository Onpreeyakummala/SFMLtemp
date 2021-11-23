#pragma once

using namespace std;

class Enamy
{

private:
    Sprite sprite;
    Texture* texture;
    Vector2f PlayerPos;
    int hp;
    int Random;
    int RandomHp;

public:
    Enamy(Texture* texture,int hp,float size)
    {
        this->texture = texture;
        this->Random = rand() % 4;
        this->RandomHp = rand() % 3 +1;
        this->hp = RandomHp*5; //5,10,15
        this->sprite.setTexture(*this->texture);
        this->sprite.setScale(Vector2f(size,size));
        this->PlayerPos = PlayerPos;
        if (Random == 0)
        {
            this->sprite.setPosition(0.f, rand() % 1080);
        }
        if (Random == 1)
        {
            this->sprite.setPosition(1920.f, rand() % 1080);
        }
        if (Random == 2)
        {
            this->sprite.setPosition(rand() % 1920, 0.f);
        }
        if (Random == 3)
        {
            this->sprite.setPosition(rand() % 1920, 1080.f);
        }
    }

    ~Enamy()
    {

    }

    void update(Vector2f PlayerPos)
    {
        Vector2f EnamyPos = Vector2f(sprite.getPosition().x, sprite.getPosition().y);
        Vector2f aimDir = PlayerPos - EnamyPos;
        Vector2f aimDirNorm = aimDir / sqrt((aimDir.x * aimDir.x + aimDir.y * aimDir.y));
        this->sprite.move(5.f * aimDirNorm);
        
    }

    void initVariable()
    {

    }

    void draw(RenderWindow& window)
    {
        window.draw(this->sprite);

    }

    void updatehp(int damage)
    {
        this->hp = hp+damage;

    }

    int getHp()
    {
        return this->hp;
    }
   
    inline const FloatRect getGlobalBounds()const
    {
        return this->sprite.getGlobalBounds();
    }

};
