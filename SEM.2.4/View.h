#include <SFML\Graphics.hpp>
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