#include <SFML\Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

void menu(RenderWindow& window) {
    Texture menuTexture1, menuTexture2, menuTexture3, menuBackground, menuPudge;
    menuTexture1.loadFromFile("image/PlayCamp.png");
    menuTexture2.loadFromFile("image/Survival.png");
    menuTexture3.loadFromFile("image/ExitGame.png");
    menuBackground.loadFromFile("image/Fon2.jpg");
    menuPudge.loadFromFile("image/Pudge.jpg");
    Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), menuBg(menuBackground), menuPg(menuPudge);
    bool isMenu = 1;
    int menuNum = 0;
    menu1.setPosition(688, 200);
    menu2.setPosition(793, 500);
    menu3.setPosition(774, 800);

    //////////////////////////////лемч///////////////////
    while (isMenu)
    {
        menu1.setColor(Color::White);
        menu2.setColor(Color::White);
        menu3.setColor(Color::White);
        menuNum = 0;

        if (IntRect(688, 200, 544, 97).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Yellow); menuNum = 1; }
        if (IntRect(793, 500, 334, 97).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Yellow); menuNum = 2; }
        if (IntRect(774, 800, 372, 97).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Yellow); menuNum = 3; }

        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (menuNum == 1) isMenu = false; 
            if (menuNum == 2) { window.draw(menuPg);  window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
            if (menuNum == 3) { window.close(); isMenu = false; }

        }

        window.draw(menuBg);
        window.draw(menu1);
        window.draw(menu2);
        window.draw(menu3);

        window.display();
    }
}