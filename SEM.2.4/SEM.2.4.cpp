#include <SFML\Graphics.hpp>
#include "map.h"
#include "View.h"
#include <iostream>
#include <sstream>
#include "mission.h"


using namespace sf;
using namespace std;

class Player {
private:
    float x, y = 0;
public:
    float dx, dy;
    int  width, height;
    float speed;
    unsigned int direction;
    unsigned int player_score = 0;
    bool life = true;
    float health;
    float CurrFrame = 0;
    string File;    
    Image image;
    Texture texture;
    Sprite sprite;
public:
    Player(string File, float x, float y, int width, int height) {
        this->File = File;
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        life = true;
        health = 100;
        image.loadFromFile("image/" + File);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(width, height, width, height));
    }

    float GetPlayerCoordinateX() { return x; }

    float GetPlayerCoordinateY() { return y; }

    void Control(float time) 
    {
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            direction = 1; speed = 0.1;
            CurrFrame += 0.0025 * time;
            if (CurrFrame > 4) CurrFrame -= 4;
            sprite.setTextureRect(IntRect(width * int(CurrFrame), height, width, height));
            GetPlayerCoordinateForView(GetPlayerCoordinateX(), GetPlayerCoordinateY());
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            direction = 0; speed = 0.1;
            CurrFrame += 0.0025 * time;
            if (CurrFrame > 4) CurrFrame -= 4;
            sprite.setTextureRect(IntRect(width * int(CurrFrame), height * 2, width, height));
            GetPlayerCoordinateForView(GetPlayerCoordinateX(), GetPlayerCoordinateY());
        }
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            direction = 3; speed = 0.1;
            CurrFrame += 0.0025 * time;
            if (CurrFrame > 4) CurrFrame -= 4;
            sprite.setTextureRect(IntRect(width * int(CurrFrame), height * 3, width, height));
            GetPlayerCoordinateForView(GetPlayerCoordinateX(), GetPlayerCoordinateY());
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            direction = 2; speed = 0.1;
            CurrFrame += 0.0025 * time;
            if (CurrFrame > 4) CurrFrame -= 4;
            sprite.setTextureRect(IntRect(width * int(CurrFrame), 0, width, height));
            GetPlayerCoordinateForView(GetPlayerCoordinateX(), GetPlayerCoordinateY());
        }
    }

    void interactionWithMap()
    {
        for (int i = y / 32; i < (y + height) / 32; i++)
            for (int j = x / 32; j < (x + width) / 32; j++)
            {
                if (i >= 0 && i < 25 && j >= 0 && j < 40) {
                    if (TileMap[i][j] == '-')
                    {
                        if (dy > 0) { y = i * 32 - height; }
                        if (dy < 0) { y = i * 32 + 32; }
                    }
                    if (TileMap[i][j] == '|')
                    {
                        if (dx > 0) { x = j * 32 - width; }
                        if (dx < 0) { x = j * 32 + 32; }
                    }
                    if (TileMap[i][j] == 'p') { health = health - 0.01; sprite.setColor(Color::Green); }
                    if (TileMap[i][j] == '+') {
                        health = health + 40;
                        if (health >= 100)
                            health = 100;
                        sprite.setColor(Color::White);
                        TileMap[i][j] = ' ';
                    }
                }
            }
    }

    void update(float time) {
        Control(time);
        switch (direction) {
        case 0: dx = -speed; dy = 0; break;
        case 1: dx = speed; dy = 0; break;
        case 2: dx = 0; dy = speed; break;
        case 3: dx = 0; dy = -speed; break;
        }
        x = x + dx * time;
        y = y + dy * time;

        speed = 0;
        
        interactionWithMap();
        if (health <= 0) { life = false; }  
        if (sprite.getColor() == Color::Green)
            health = health - 0.002;
 
    }
};


int main()
{
    randomMapGenerate();

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Game!", Style::Fullscreen);

    view.reset(FloatRect(0, 0, 640, 480));
    //ШРИФТЫ
    Font font;
    font.loadFromFile("Pixelfont.ttf");
    Text mission("", font, 20);
    mission.setFillColor(Color::Black);
    Text text("", font, 30);
    text.setFillColor(Color::White);
    //Спрайты и текстуры
    //Карта
    Image map_image;
    map_image.loadFromFile("image/NewMap.png");
    Texture map;
    map.loadFromImage(map_image);
    Sprite s_map;
    s_map.setTexture(map);
    //Миссия
    Image quest_image;
    quest_image.loadFromFile("image/mission.jpg");
    quest_image.createMaskFromColor(Color(0, 0, 0));
    Texture quest_texture;
    quest_texture.loadFromImage(quest_image);
    Sprite s_quest;
    s_quest.setTexture(quest_texture);
    s_quest.setTextureRect(IntRect(0, 0, 340, 510));
    s_quest.setScale(0.6f, 0.6f);

    Player Player1("soldat1.png", 256, 256, 40, 60);

    float CurrFrame = 0;
    Clock clock;
    Clock game_timeClock;
    int game_time = 0;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed)
                if ((event.key.code == Keyboard::Escape)) { window.close(); }
        }

        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;

        if (Player1.life) {
            game_time = game_timeClock.getElapsedTime().asSeconds();
            Player1.Control(time);
        }

        Player1.update(time);
        changeview();
        window.setView(view);
        window.clear();

        // СОЗДАНИЕ КАРТЫ
        for (int i = 0; i < HEIGHT_MAP; i++)
            for (int j = 0; j < WIDTH_MAP; j++)
            {
                if (TileMap[i][j] == ' ') s_map.setTextureRect(IntRect(0, 0, 32, 32));
                if (TileMap[i][j] == '_') s_map.setTextureRect(IntRect(32 * 1, 0, 32, 32));
                if (TileMap[i][j] == '-') s_map.setTextureRect(IntRect(32 * 2, 0, 32, 32));
                if (TileMap[i][j] == '|') s_map.setTextureRect(IntRect(32 * 3, 0, 32, 32));
                if (TileMap[i][j] == '[') s_map.setTextureRect(IntRect(32 * 4, 0, 32, 32));
                if (TileMap[i][j] == ']') s_map.setTextureRect(IntRect(32 * 5, 0, 32, 32));
                if (TileMap[i][j] == '<') s_map.setTextureRect(IntRect(32 * 6, 0, 32, 32));
                if (TileMap[i][j] == '>') s_map.setTextureRect(IntRect(32 * 7, 0, 32, 32));
                if (TileMap[i][j] == 'p') s_map.setTextureRect(IntRect(32 * 1, 32 * 1, 32, 32));
                if (TileMap[i][j] == 's') s_map.setTextureRect(IntRect(32 * 2, 32 * 1, 32, 32));
                if (TileMap[i][j] == '+') s_map.setTextureRect(IntRect(32 * 4, 32 * 1, 32, 32));
                s_map.setPosition(j * 32, i * 32);
                window.draw(s_map);
            }

        //ВЫВОД ТЕКСТА		
        ostringstream gameTimeString;
        gameTimeString << game_time;
        ostringstream playerHealthString;
        playerHealthString << (int)Player1.health;
        if (Player1.life == true) {
            text.setString("Health: " + playerHealthString.str() + "\nGame time: " + gameTimeString.str());
            text.setPosition(view.getCenter().x + 120, view.getCenter().y - 225);
            window.draw(Player1.sprite);
            window.draw(text);
        }
        if (Keyboard::isKeyPressed(Keyboard::Tab)) {
            std::ostringstream task;
            task << getTextMission();
            mission.setString(task.str());
            mission.setPosition(view.getCenter().x - 95, view.getCenter().y - 130);
            s_quest.setPosition(view.getCenter().x - 100, view.getCenter().y - 130);
            window.draw(s_quest);
            window.draw(mission);
        }
        if (Player1.life == false) {
            std::ostringstream death;
            death << getTextDeath();
            mission.setString(death.str() + "\n\n\n\n\tGame time: " + gameTimeString.str()
                + "\n\n\n\n\n\n\n(To exit the game, \nclick \"Escape\")");
            mission.setPosition(view.getCenter().x - 95, view.getCenter().y - 130);
            s_quest.setPosition(view.getCenter().x - 100, view.getCenter().y - 130);
            window.draw(s_quest);
            window.draw(mission);
        }
        window.display();
    }

    return 0;
    
}