#pragma once
#include <SFML/Audio.hpp>
#include "Player.hpp"
#include"Enamy.hpp"
#include"Item.hpp"
#include<stdio.h>
#include "ScoreList.h"

#define GAME_MENU        0
#define GAME_HIGHSCORE   1
#define GAME_PLAY        2
#define GAME_PAUSE       3
#define GAME_OVER        4


#define BUTTON_PLAY       0
#define BUTTON_HIGHSCORE  1
#define BUTTON_QUIT       2
#define BUTTON_RETRY      3

#define Max_menu 3

class Game {

private:

    ScoreList* score_list;
    RenderWindow* window;
    Player* player;
    vector<Enamy>Enamys;
    Texture EnemyTexture;
    Texture EnemyTexture2;
    Texture EnemyTexture3;
    Texture lifeTexture;
    Sprite lifeSprite[3];
    Texture bgTexture;
    Sprite bgSprite;
    Texture bggameOverTexture;
    Sprite bggameOverSprite;
    Texture bgstartTexture;
    Sprite bgstartSprite;
    Texture bgscoreTexture;
    Sprite bgscoreSprite;
    vector<Item>items;
    Sprite Itemsprite;
    Texture ItemTexture;
    Texture ItemTexture2;
    float spTime;
    float spTimeMax;
    float immuneTime;
    float immuneTimeMax;
    float spawnItemDelay;
    float spawnItemDelayMax;
    int kill;
    int score; //คะแนน
    bool isimmune;
    int itemType;
    int game_state;
    int menu_selection;
    Font font;
    Font font2; //เปลี่ยนfont
    Text menu[4];
    Text pauseText;
    Text GameoverText;
    Text ScoreText;
    Text ScoreText1;
    Text enterText;
    Text MynameText;
    Text nameGameText;
    Text enterName;
    Text enteryournameText;
    Text highscoreText;
    Text Scoreborad;
    Event event;
    Sound sound;
    SoundBuffer Shoot;
    Sound hurtsound;
    SoundBuffer hurt;
    Sound oversound;
    SoundBuffer gover;
    Sound itemsound;
    SoundBuffer itemsong;
    Sound clicksound;
    SoundBuffer clicksong;
    std::string enter_name;

    bool up_button_pressed;
    bool down_button_pressed;
    bool pause_button_pressed;

public:

    Game(ScoreList* score_list) 
    {   
        this->score_list = score_list;
        this->enter_name = "";
        this->window = new RenderWindow(VideoMode(w, h), "SHOOT TILL YOUR HEAD SPINS");
        this->window->setFramerateLimit(60);
        this->bgTexture.loadFromFile("Texture/4.jpg");
        this->bgSprite.setTexture(bgTexture);
        this->bgSprite.setScale(Vector2f(0.95f, 0.8f)); 
        this->player = new Player(this->window);
        this->spTimeMax = 120.f;
        this->spTime = 0;
        this->EnemyTexture.loadFromFile("Texture/Enemy/11.png");
        this->EnemyTexture2.loadFromFile("Texture/Enemy/12.png");
        this->EnemyTexture3.loadFromFile("Texture/Enemy/13.png");
        this->ItemTexture.loadFromFile("Texture/heart.png");
        this->ItemTexture2.loadFromFile("Texture/Bulletbox.png");
        this->font2.loadFromFile("Font/Witch2.ttf");
        this->font.loadFromFile("Font/Font11.ttf");
        this->lifeTexture.loadFromFile("Texture/heart.png");
        for (size_t i = 0; i < 3; i++)
        {
            lifeSprite[i].setTexture(lifeTexture);  
        }
        this->immuneTimeMax = 120.f;
        this->immuneTime = immuneTimeMax;
        this->isimmune = 0;
        this->kill = 0; 
        this->spawnItemDelayMax = 900.f;
        this->spawnItemDelay = 0;
        this->game_state = GAME_MENU;
        this->menu_selection = 0;
        this->score = 0;

        this->menu[0].setFont(font);
        this->menu[0].setCharacterSize(150);
        this->menu[0].setFillColor(Color::Red);
        this->menu[0].setString("Play");
        this->menu[0].setOrigin(menu[0].getGlobalBounds().width / 2, menu[0].getGlobalBounds().height / 2);
        this->menu[0].setPosition(Vector2f(w / 2, h / (Max_menu + 1) * 1.5));

        this->menu[1].setFont(font);
        this->menu[1].setCharacterSize(125);
        this->menu[1].setFillColor(Color::White);
        this->menu[1].setString("ScoreBoard");
        this->menu[1].setOrigin(menu[1].getGlobalBounds().width / 2, menu[1].getGlobalBounds().height / 2);
        this->menu[1].setPosition(Vector2f(w / 2, h / (Max_menu + 1) * 2));

        this->menu[2].setFont(font);
        this->menu[2].setCharacterSize(125);
        this->menu[2].setFillColor(Color::Red);
        this->menu[2].setString("Exit");
        this->menu[2].setOrigin(menu[2].getGlobalBounds().width / 2, menu[2].getGlobalBounds().height / 2);
        this->menu[2].setPosition(Vector2f(w / 2, h / (Max_menu + 1) * 2.5));
        
        this->highscoreText.setFont(font);
        this->highscoreText.setCharacterSize(125);
        this->highscoreText.setFillColor(Color::White);

        this->up_button_pressed = false;
        this->down_button_pressed = false;
        this->pause_button_pressed = false;
       //เสียง
        if (!Shoot.loadFromFile("Sound/shoot1.wav"))
        {
            cout << "error shoot" << endl;
        }
        sound.setBuffer(Shoot);
        sound.setVolume(40);

        if (!hurt.loadFromFile("Sound/Hurt.wav"))
        {
            cout << "error shoot" << endl;
        }
        hurtsound.setBuffer(hurt);
        hurtsound.setVolume(40);
        if (!gover.loadFromFile("Sound/GameOver2.wav"))
        {
            cout << "error shoot" << endl;
        }
        oversound.setBuffer(gover);
        oversound.setVolume(80);
        if (!itemsong.loadFromFile("Sound/item.wav"))
        {
            cout << "error shoot" << endl;
        }
        itemsound.setBuffer(itemsong);
        itemsound.setVolume(100);
        if (!clicksong.loadFromFile("Sound/click.wav"))
        {
            cout << "error shoot" << endl;
        }
        clicksound.setBuffer(clicksong);
        clicksound.setVolume(70);
    }

    ~Game() 
    {
        delete this->window;
        delete this->player;
    }

    bool isRunning() 
    {

        return this->window->isOpen();
    }

    void processEvent() 
    {

        while (this->window->pollEvent(this->event))
        {
            // Close window: exit
            if (this->event.type == Event::Closed)
                this->window->close();
            if (this->event.type == Event::TextEntered)
               cout << this->event.text.unicode << endl;
            if (this->event.type == Event::KeyPressed)
            {
                if (Keyboard::isKeyPressed(Keyboard::Escape))
                {
                    this->window->close();
                }
            }
        }
    }
   
    void gameMenuUpdate()
    {
        this->bgstartTexture.loadFromFile("Texture/bgg1.png");
        this->bgstartSprite.setTexture(bgstartTexture);
        this->bgstartSprite.setScale(Vector2f(1.f, 1.f));
        MynameText.setFont(font);
        MynameText.setCharacterSize(50);
        MynameText.setFillColor(Color::White);
        MynameText.setString("64010986 Onpreeya Kummala");
        MynameText.setPosition(Vector2f(20, 1010));
        nameGameText.setFont(font2);
        nameGameText.setCharacterSize(125);
        nameGameText.setFillColor(Color::Yellow);
        nameGameText.setString("SHOOT TILL YOUR HEAD SPINS");
        nameGameText.setPosition(Vector2f(240, 215));
        if (this->event.text.unicode == 13)
        {
            if (this->menu_selection == BUTTON_PLAY)
            {
                clicksound.play();
                this->game_state = GAME_PLAY;
                this->player->lifereset();
                this->player->setHpMax();                
                this->player->resetplayer();
                this->player->resetBullet();
                this->Enamys.clear();
                this->items.clear();
                this->spTimeMax = 120.f;
                this->spTime = 0;
                this->kill = 0;
                this->spawnItemDelayMax = 900.f;
                this->spawnItemDelay = 0; 

            }
            if (this->menu_selection == BUTTON_HIGHSCORE)
            {
                clicksound.play();
                this->game_state = GAME_HIGHSCORE;
            }
            if (this->menu_selection == BUTTON_QUIT) 
            {
                clicksound.play();
                this->window->close();
            }
            event.text.unicode = 0;
        }
        
   

        if (Keyboard::isKeyPressed(Keyboard::Up) && !this->up_button_pressed) // ผู้เล่นกดปุ่มลง 
        {
            this->up_button_pressed = true;
            this->menu_selection--;
            if (this->menu_selection == -1) this->menu_selection = 2;
        }
        else if(!Keyboard::isKeyPressed(Keyboard::Up)) this->up_button_pressed = false;
        if (Keyboard::isKeyPressed(Keyboard::Down) && !this->down_button_pressed) // ผุ้เล่นกดปุ่มขึ่น
        {
            this->down_button_pressed = true;
            this->menu_selection++;
            if (this->menu_selection == 3) this->menu_selection = 0;
        }
        else if(!Keyboard::isKeyPressed(Keyboard::Down)) this->down_button_pressed = false;


        if (this->menu_selection == BUTTON_PLAY)
        {
            menu[0].setStyle(Text::Underlined);
        } else menu[0].setStyle(Text::Regular);
        if (this->menu_selection == BUTTON_HIGHSCORE)
        {
            menu[1].setStyle(Text::Underlined);
        } else menu[1].setStyle(Text::Regular);
        if (this->menu_selection == BUTTON_QUIT)
        {
            menu[2].setStyle(Text::Underlined);
        } else menu[2].setStyle(Text::Regular);

    }
    void gameMenuDraw() 
    {
        this->window->draw(this->bgstartSprite);
        this->window->draw(menu[0]);
        this->window->draw(menu[1]);
        this->window->draw(menu[2]);
        this->window->draw(MynameText);
        this->window->draw(nameGameText);

    }

    void gamePlayUpdate()
    {
        // Pause
        if (Keyboard::isKeyPressed(Keyboard::P) && !this->pause_button_pressed)
        {
            this->pause_button_pressed = true;
            this->game_state = GAME_PAUSE;
        }
        else if(!Keyboard::isKeyPressed(Keyboard::P)) this->pause_button_pressed = false;

        //ความเร็วการเกิดEnemy

        if ( 30 <=kill < 50)
        {
            spTimeMax = 120 - (kill % 10) * 13;
        }
        else
        {
            spTimeMax = 120 - (kill % 15) * 8;
        }
            

        //สุ่มEnamy
        if (spTime>=spTimeMax)
        {
            int EnamyType =  rand() %3;
            if (EnamyType == 0)
            {
                Enamys.push_back(Enamy(&EnemyTexture,10,0.4));
            }
            if (EnamyType == 1)
            {
                Enamys.push_back(Enamy(&EnemyTexture2, 10,0.4));
            }
            if (EnamyType == 2)
            {
                Enamys.push_back(Enamy(&EnemyTexture3, 10,0.5));
            }
            spTime = 0;
        }
        else
        {
            spTime++;
        }
        //player

        this->player->updatePlayer();
        if (this->player->getHp() <= 0)
        {
            if (this->player->getlife() == 0)
            {
                
                this->game_state = GAME_OVER;
                oversound.play();
                return;
            }
            this->player->deletelife();
            this->player->setHpMax();
            this->isimmune = 1;
            this->immuneTime = 0;

        }
        if (isimmune ==1) //อมตะ
        {
            immuneTime++;
        }
        if (immuneTime >= immuneTimeMax)
        {
            isimmune = 0;
        }
        if(this->player->getlife() >= 0) {
            for (size_t i = 0; i < this->player->getlife(); i++)
            {
                lifeSprite[i].setPosition(100+(i*125),50); //ปรับหัวใจ
                lifeSprite[i].setScale(0.4f, 0.4f);
            }
        }
        for (size_t i = 0; i < Enamys.size(); i++)
        {
            Enamys[i].update(player->getPosition());
            if (Enamys[i].getGlobalBounds().intersects(this->player->getGlobalBounds()))
            {
                if (isimmune == 0)
                {
                  hurtsound.play();
                  this->player->getDamage(-10);
                  
                }
                Enamys.erase(Enamys.begin()+i);
                score -= 10;
                break;
            }
            if (Enamys[i].getHp() <= 0)
            {
                Enamys.erase(this->Enamys.begin() + i);
                kill++;
                score += 20;
                break;
            }
        }
      

        for (size_t i = 0; i < player->getBullet().size(); i++)
        {
            player->getBullet()[i].updateBullet();
            for (size_t j = 0; j <Enamys.size(); j++)
            {
                if (player->getBullet()[i].getGlobalBounds().intersects(Enamys[j].getGlobalBounds()))
                {
                    Enamys[j].updatehp(-5);
                    player->getBullet().erase(player->getBullet().begin() + i);
                    sound.play();
                    break;
                }
            }
        }
       
        //item
        if (spawnItemDelay >= spawnItemDelayMax)
        {
            int itemType = rand() % 2;
            if (itemType == 0)
            {
                items.push_back(Item(&ItemTexture, 0.3,ITEM_HEAL));
            }
            if (itemType == 1)
            {
                 items.push_back(Item(&ItemTexture2, 0.3,ITEM_BULLET));
            }
            spawnItemDelay = 0;
        }
        else
        {
            spawnItemDelay++;
        }

        for (int i = 0; i < items.size(); i++)
        {
            items[i].update();
            if (items[i].getGlobalBounds().intersects(this->player->getGlobalBounds()))
            {
                if (items[i].getType() == ITEM_HEAL)
                {
                    itemsound.play();
                    this->player->setHpMax();
                    items.erase(items.begin() + i);
                    break;
                }
                else if (items[i].getType() == ITEM_BULLET)
                {
                    itemsound.play();
                    this->player->setDualShoot(10);
                    items.erase(items.begin() + i);
                    break;
                }

            }
        }
        for (int i = 0; i < items.size(); i++)
        {
            items[i].update();
        }

        cout << score << endl;
        if (score <= 0)
        {
            score = 0;
        }

        ScoreText.setFont(font);
        ScoreText.setCharacterSize(50);
        ScoreText.setFillColor(Color::Black);
        ScoreText.setString("SCORE : "+to_string(score));
        ScoreText.setPosition(Vector2f(1400,20));
    }

    void clearScreen() 
    {
        this->window->clear();
    }

    void gameHighscoreUpdate() {

        this->bgscoreTexture.loadFromFile("Texture/Score1.png");
        this->bgscoreSprite.setTexture(bgscoreTexture);
        this->bgscoreSprite.setScale(Vector2f(1.f, 1.f));
        //ย้อนกลับไปเมนู
        if(event.text.unicode == 32) 
        { 
            this->game_state = GAME_MENU;
        }
    }
    void gameHighscoreDraw() {

        // วาด ชื่อ
        this->window->draw(this->bgscoreSprite);
        for(int i = 0; i < this->score_list->get().size(); i++)
        {
            highscoreText.setFont(font);
            highscoreText.setCharacterSize(150);
            this->highscoreText.setString(this->score_list->get().at(i).getName());
            this->highscoreText.setPosition(Vector2f(600, 285 + (i * 150)));
            this->window->draw(this->highscoreText);

            this->highscoreText.setString(std::to_string(this->score_list->get().at(i).getScore()));
            this->highscoreText.setPosition(Vector2f(1100, 285 + (i * 150)));
            this->window->draw(this->highscoreText);

            Scoreborad.setFont(font2);
            Scoreborad.setCharacterSize(200);
            Scoreborad.setFillColor(Color::Red);
            Scoreborad.setString("SCOREBORAD");
            Scoreborad.setPosition(Vector2f(500, 25));
            this->window->draw(this->Scoreborad); 
            
        }
    }

    void gamePlayDraw() 
    {
        this->window->draw(this->bgSprite);
        this->window->draw(ScoreText);
        this->player->draw();
        if(this->player->getlife() >= 0) {
            for (size_t i = 0; i < this->player->getlife(); i++)
            {
                this->window->draw(lifeSprite[i]);
            }
        }
        for (size_t i = 0; i < Enamys.size(); i++)
        {
            Enamys[i].draw(*this->window);
        }

        for (int i = 0; i < items.size(); i++)
        {
            items[i].draw(this->window);

        }

    }
    void gamePauseUpdate()
    {
        // Un Pause
        if (Keyboard::isKeyPressed(Keyboard::P) && !this->pause_button_pressed)
        {
            this->pause_button_pressed = true;
            this->game_state = GAME_PLAY;
        }
        else if(!Keyboard::isKeyPressed(Keyboard::P)) this->pause_button_pressed = false;


        pauseText.setFont(font);
        pauseText.setCharacterSize(150);
        pauseText.setFillColor(Color::Black);
        pauseText.setString("PAUSE");
        pauseText.setPosition(Vector2f(1400,900));
    }

    void gamePauseDraw()
    {
        this->window->draw(pauseText);
    }
    
    void gameOver()
    {
        // ลบตัวหนังสือ
        if(event.text.unicode == 8) { 

            if(this->enter_name.size() > 0) { 

                this->enter_name.erase(this->enter_name.end()-1);
            }
            event.text.unicode = 0;
        }

        // พิมพ์ตัวหนังสือ
        if((event.text.unicode >= 'A' && event.text.unicode <= 'Z') || (event.text.unicode >= 'a' && event.text.unicode <= 'z')) 
        {
            if(this->enter_name.size() < 10) 
            { // พิมพ์ได้มากสุด 10 ตัว
                this->enter_name.push_back((char)event.text.unicode);
            }
            event.text.unicode = 0;
        }

        if (event.text.unicode == 13)
        {
            this->game_state = GAME_MENU;
            clicksound.play();
            event.text.unicode = 0;

            this->score_list->addEntry(this->enter_name, this->score);
            this->enter_name = "";
        }

        this->bggameOverTexture.loadFromFile("Texture/gameoverbg.png");
        this->bggameOverSprite.setTexture(bggameOverTexture);
        this->bggameOverSprite.setScale(Vector2f(1.2f, 1.2f));
        GameoverText.setFont(font2);
        GameoverText.setCharacterSize(250);
        GameoverText.setFillColor(Color::Red);
        GameoverText.setString("GAME OVER");
        GameoverText.setPosition(Vector2f(420,200));
       
        ScoreText1.setFont(font);
        ScoreText1.setCharacterSize(75);
        ScoreText1.setFillColor(Color::White);
        ScoreText1.setString("SCORE : " + to_string(score));
        ScoreText1.setPosition(Vector2f(780, 500));

        enteryournameText.setFont(font);
        enteryournameText.setCharacterSize(50);
        enteryournameText.setFillColor(Color::Yellow);
        enteryournameText.setString("ENTER YOUR NAME");
        enteryournameText.setPosition(Vector2f(750, 600));

        enterName.setFont(font);
        enterName.setCharacterSize(50);
        enterName.setString(this->enter_name + "_");
        enterName.setPosition(Vector2f(850, 650));

        enterText.setFont(font);
        enterText.setCharacterSize(30);
        enterText.setFillColor(Color::Red);
        enterText.setString("ENTER IF YOU WANT TO PLAY AGAIN");
        enterText.setPosition(Vector2f(720, 730));
    }

    void gameOverdraw()
    {
        this->window->draw(this->bggameOverSprite);
        this->window->draw(GameoverText);
        this->window->draw(ScoreText1);
        this->window->draw(enteryournameText);      
        this->window->draw(enterName);
        this->window->draw(enterText);
    }

    void update()
    {

        if (this->game_state == GAME_MENU) this->gameMenuUpdate();
        if (this->game_state == GAME_HIGHSCORE) this->gameHighscoreUpdate();
        if (this->game_state == GAME_PAUSE)
        {
            this->gamePauseUpdate();
        }
        if (this->game_state == GAME_PLAY) this->gamePlayUpdate();
        if (this->game_state == GAME_OVER)
        {
            this->gameOver();
        }
    }
    void drawScreen()
    {

        if (this->game_state == GAME_MENU) this->gameMenuDraw();
        if (this->game_state == GAME_HIGHSCORE) this->gameHighscoreDraw();
        if (this->game_state == GAME_PLAY) this->gamePlayDraw();
        if (this->game_state == GAME_PAUSE)
        {
            this->gamePlayDraw();
            this->gamePauseDraw();
        }
        if (this->game_state == GAME_OVER)
        {
            this->gameOverdraw();
        }
    }

    void displayScreen() 
    {
        this->window->display();
    }

};
