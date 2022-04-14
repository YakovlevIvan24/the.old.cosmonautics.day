#include <SFML/Graphics.hpp>
#include "cmath"
#include <array>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <tuple>
#include <sstream>

using namespace std;
using namespace sf;




View view;

void GetPlayerCoordinateForView(float x, float y) { //функция для считывания координат игрока
    float tempX = x; float tempY = y;//считываем коорд игрока и проверяем их, чтобы убрать края

    if (x < 320) tempX = 320;//убираем из вида левую сторону
    if (y < 240) tempY = 240;//верхнюю сторону
    if (y > 554) tempY = 554;//нижнюю сторону
    if (x > 959) tempX = 959;

    view.setCenter(tempX, tempY); //следим за игроком, передавая его координаты.

}

void changeview() {
    if (Keyboard::isKeyPressed(Keyboard::U)) {
        view.zoom(1.001f); //масштабируем, уменьшение
        //view.zoom(1.0006f); //тоже самое помедленнее соответственно
    }
    if (Keyboard::isKeyPressed(Keyboard::Y)) {
        view.zoom(0.999f);
    }
    if (Keyboard::isKeyPressed(Keyboard::I)) {
        view.setSize(640, 480);//устанавливает размер камеры (наш исходный)
    }
    if (Keyboard::isKeyPressed(Keyboard::P)) {
        view.setSize(540, 380);//например другой размер
    }

}



std::string getTextMission() {
    std::string TextMission = " Hello, fighter! \n You have a \ndifficult task! \n Try to hold out \nuntil support \narrives!";
    return TextMission;
}
std::string getTextDeath() {
    std::string TextDeath = " Alas... You failed the \nmission! Try again! ";
    return TextDeath;
}
// Много ненужного, я пытался написать алгоритм поиска пути
struct Tail{
public:
    IntRect rect;
    int cost;
    int num;
    int x;
    int y;
    Tail* previous = nullptr;
    bool operator==(const Tail& a)const{
        return this->cost == a.cost && this->num == a.num;
    }
};
bool operator<(const Tail& a,const Tail& b){
    return a.cost < b.cost;
}
const int HEIGHT_MAP = 25;//ðàçìåð êàðòû âûñîòà
const int WIDTH_MAP = 40;//ðàçìåð êàðòû øèðèíà


sf::String TileMap[HEIGHT_MAP] = {
        "[--------------------------------------]",
        "|_     _     _     __     _     _     _|",
        "|_     _     _     __     _     _     _|",
        "|_     _     _     __     _     _     _|",
        "|_     _     _     __     _     _     _|",
        "|_     _     _     __     _     _     _|",
        "|_     !     !     __     _     _     _|",
        "|_     _     !     __     _     _     _|",
        "|_     _     !     __     _     _     _|",
        "|_     _     !     __     _     _     _|",
        "|_     _     !     __     _     _     _|",
        "|_     _     !     __     _     _     _|",
        "|__   ___   ___   ____   ___   ___   __|",
        "|_     _     _     __     _     _     _|",
        "|_     _     _     __     _     _     _|",
        "|_     _     _     __     _     _     _|",
        "|_     _     _     __     _     _     _|",
        "|_     _     _     __     _     _     _|",
        "|_     _     _     __     _     _     _|",
        "|_     _     _     __     _     _     _|",
        "|_     _     _     __     _     _     _|",
        "|_     _     _     __     _     _     _|",
        "|_     _     _     __     _     _     _|",
        "|_     _     _     __     _     _     _|",
        "<-------------------------------------->",
};

Tail tileMap[HEIGHT_MAP][WIDTH_MAP];


void randomMapGenerate() {//ðàíäîìíî ðàññòàâëÿåì êàìíè

    int randomX = 0;//ñëó÷àéíûé ýëåìåíò ïî ãîðèçîíòàëè
    int randomY = 0;//ñëó÷ ýë-ò ïî âåðòèêàëè
    srand(time(0));//ðàíäîì
    int countSphere = 10;//êîëè÷åñòâî êàìíåé
    int countPoison = 20;
    int countHeal = 3;

    while (countSphere > 0) {
        randomX = 1 + rand() % (WIDTH_MAP - 1);//ðàíäîìíîå ïî èêñó îò 1 äî øèðèíà êàðòû-1, ÷òîáû íå ïîëó÷àòü ÷èñëà áîðäþðà êàðòû
        randomY = 1 + rand() % (HEIGHT_MAP - 1);//ïî èãðåêó òàê æå

        if (TileMap[randomY][randomX] == ' '&&
            randomX != 8 && randomX != 9 && randomX != 10 && randomX != 11 &&
            randomX != 7 && randomX != 6 && randomX != 5 &&
            randomY != 8 && randomY != 9 && randomY != 10 && randomY != 11 &&
            randomY != 7 && randomY != 6 && randomY != 5) {
            TileMap[randomY][randomX] = 's'; //òî ñòàâèì òóäà êàìåíü.
            countSphere--;
        }
    }

    while (countPoison > 0) {
        randomX = 1 + rand() % (WIDTH_MAP - 1);//ðàíäîìíîå ïî èêñó îò 1 äî øèðèíà êàðòû-1, ÷òîáû íå ïîëó÷àòü ÷èñëà áîðäþðà êàðòû
        randomY = 1 + rand() % (HEIGHT_MAP - 1);//ïî èãðåêó òàê æå

        if (TileMap[randomY][randomX] == ' ' &&
            randomX != 8 && randomX != 9 && randomX != 10 && randomX != 11 &&
            randomX != 7 && randomX != 6 && randomX != 5 &&
            randomY != 8 && randomY != 9 && randomY != 10 && randomY != 11 &&
            randomY != 7 && randomY != 6 && randomY != 5) {
            TileMap[randomY][randomX] = 'p'; //òî ñòàâèì òóäà êàìåíü.
            countPoison--;
        }
    }
    while (countHeal > 0){
        randomX = 1 + rand() % (WIDTH_MAP - 1);//ðàíäîìíîå ïî èêñó îò 1 äî øèðèíà êàðòû-1, ÷òîáû íå ïîëó÷àòü ÷èñëà áîðäþðà êàðòû
        randomY = 1 + rand() % (HEIGHT_MAP - 1);//ïî èãðåêó òàê æå

        if (TileMap[randomY][randomX] == ' ' &&
            randomX != 8 && randomX != 9 && randomX != 10 &&
            randomX != 7 && randomX != 6 &&
            randomY != 8 && randomY != 9 && randomY != 10 &&
            randomY != 7 && randomY != 6) {
            TileMap[randomY][randomX] = '+'; //òî ñòàâèì òóäà êàìåíü.
            countHeal--;
        }
    }



}



class Creature{
public:
    float x, y = 0;
    float dx, dy;
    int  width, height;
    float speed;
    unsigned int direction;
    bool life = true;
    double health;
    double CurrFrame = 0;
    string File;
    Image image;
    Texture texture;
    Sprite sprite;

    Creature(const string& File, float x, float y, int width, int height) {
        this->File = File;
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        life = true;
        image.loadFromFile(File);//aboba
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, width, height));
    }

     float GetСreatureCoordinateX()const { return x; }

     float GetСreatureCoordinateY() const { return y; }


    virtual void interactionWithMap()
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
    };


    virtual void update(float time) {
        switch (direction) {
            case 0: dx = speed; dy = 0; break;
            case 1: dx = -speed; dy = 0; break;
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
        this->sprite.setPosition(x,y);//aboba
    }
};




class Player: public Creature {

public:
    unsigned int player_score = 0;

    Player(const string& File, float x, float y, int width, int height) : Creature(File, x, y, width, height) {
        this->health = 100;
    };


    void Control(float time) {
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            direction = 1;
            speed = 0.1;
            CurrFrame += 0.0025 * time;
            if (CurrFrame > 4) CurrFrame -= 4;
            sprite.setTextureRect(IntRect(width * int(CurrFrame), height, width, height));
            GetPlayerCoordinateForView(GetСreatureCoordinateX(), GetСreatureCoordinateY());
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            direction = 0;
            speed = 0.1;
            CurrFrame += 0.0025 * time;
            if (CurrFrame > 4) CurrFrame -= 4;
            sprite.setTextureRect(IntRect(width * int(CurrFrame), height * 2, width, height));
            GetPlayerCoordinateForView(GetСreatureCoordinateX(), GetСreatureCoordinateY());
        }
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            direction = 3;
            speed = 0.1;
            CurrFrame += 0.0025 * time;
            if (CurrFrame > 4) CurrFrame -= 4;
            sprite.setTextureRect(IntRect(width * int(CurrFrame), height * 3, width, height));
            GetPlayerCoordinateForView(GetСreatureCoordinateX(), GetСreatureCoordinateY());
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            direction = 2;
            speed = 0.1;
            CurrFrame += 0.0025 * time;
            if (CurrFrame > 4) CurrFrame -= 4;
            sprite.setTextureRect(IntRect(width * int(CurrFrame), 0, width, height));
            GetPlayerCoordinateForView(GetСreatureCoordinateX(), GetСreatureCoordinateY());
        }
    }

};

class Enemy: public Creature{
public:
    Enemy(const string& File, float x, float y, int width, int height) : Creature(File, x, y, width, height) {
        this->health = 100;
    };

};



int main()
{       //Карта
    Image map_image;
    map_image.loadFromFile("C://Users//123//Desktop//TAILsets/NewMap.png");
    Texture Map;
    Map.loadFromImage(map_image);
    Sprite s_map;
    s_map.setTexture(Map);

    Tail tail1 = {IntRect(0, 0, 32, 32),1};       // Много костылей, я пытался тестить алгоритм
    Tail tail2 = {IntRect(32 * 1, 0, 32, 32),2};
    Tail tail3 = {IntRect(32 * 2, 0, 32, 32),2};
    Tail tail4 = {IntRect(32 * 3, 0, 32, 32),100};
    Tail tail5 = {IntRect(32 * 4, 0, 32, 32),100};
    Tail tail6 = {IntRect(32 * 5, 0, 32, 32),100};
    Tail tail7 = {IntRect(32 * 6, 0, 32, 32),100};
    Tail tail8 = {IntRect(32 * 7, 0, 32, 32),100};
    Tail tail9 = {IntRect(32 * 1, 32 * 1, 32, 32),100};
    Tail tail10 = {IntRect(32 * 2, 32 * 1, 32, 32),100};
    Tail tail11 = {IntRect(32 * 4, 32 * 1, 32, 32),100};
    Tail tail12 = {IntRect(32 * 3, 32 * 1, 32, 32),100};
    map<char,Tail> tailKeys = {{' ',tail1},
                               {'_',tail2},
                               {'-',tail3},
                               {'|',tail4},
                               {'[',tail5},
                               {']',tail6},
                               {'<',tail7},
                               {'>',tail8},
                               {'p',tail9},
                               {'s',tail10},
                               {'+',tail11},
                               {'!',tail12}};

    for (int i = 0; i < HEIGHT_MAP; i++)
        for (int j = 0; j < WIDTH_MAP; j++)
        {
            if(tailKeys.find(TileMap[i][j])!= tailKeys.end()){
                tileMap[i][j].num = 40*i+j;
                tileMap[i][j].cost = tailKeys.find(TileMap[i][j])->second.cost;
                tileMap[i][j].x = i*32;
                tileMap[i][j].y = j*32;
            }
        }

    randomMapGenerate();

    sf::RenderWindow window(sf::VideoMode(1200, 800), "Game!");

    view.reset(FloatRect(0, 0, 640, 480));
    //ШРИФТЫ
    Font font;
    font.loadFromFile("C://Users//123//Downloads/Pixelfont.ttf");
    Text mission("", font, 20);
    mission.setFillColor(Color::Black);
    Text text("", font, 30);
    text.setFillColor(Color::White);
    //Спрайты и текстуры

    //Миссия
    Image quest_image;
    quest_image.loadFromFile("C://Users//123//Desktop//TAILsets/mission.png");
    quest_image.createMaskFromColor(Color(0, 0, 0));
    Texture quest_texture;
    quest_texture.loadFromImage(quest_image);
    Sprite s_quest;
    s_quest.setTexture(quest_texture);
    s_quest.setTextureRect(IntRect(0, 0, 340, 510));
    s_quest.setScale(0.6f, 0.6f);

    Player Player1("C://Users//123//Desktop//TAILsets/soldat1.png", 256, 256, 40, 60);
    Enemy Enemy1("C://Users//123//Desktop//TAILsets/enemy.png", 256, 256, 386, 350);
    Enemy1.sprite.scale(0.2f,0.2f);
    Enemy1.sprite.setPosition(500,200);
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
                if (event.key.code == Keyboard::Escape) { window.close(); }
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
        for (int i = 0; i < HEIGHT_MAP; i++) {
            for (int j = 0; j < WIDTH_MAP; j++) {
                if (tailKeys.find(TileMap[i][j]) != tailKeys.end()) {
                    s_map.setTextureRect(tailKeys[TileMap[i][j]].rect);
                }
                s_map.setPosition(j * 32, i * 32);
                window.draw(s_map);
            }
        }

        //ВЫВОД ТЕКСТА
        ostringstream gameTimeString;
        gameTimeString << game_time;
        ostringstream playerHealthString;
        playerHealthString << (int)Player1.health;
        if (Player1.life) {
            text.setString("Health: " + playerHealthString.str() + "\nGame time: " + gameTimeString.str());
            text.setPosition(view.getCenter().x + 120, view.getCenter().y - 225);
            window.draw(Player1.sprite);
            window.draw(Enemy1.sprite);
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
        if (!Player1.life) {
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