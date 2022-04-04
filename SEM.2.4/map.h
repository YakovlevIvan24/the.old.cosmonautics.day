#include <SFML\Graphics.hpp>
const int HEIGHT_MAP = 25;//размер карты высота
const int WIDTH_MAP = 40;//размер карты ширина 


sf::String TileMap[HEIGHT_MAP] = {
	"[--------------------------------------]",
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

void randomMapGenerate() {//рандомно расставляем камни

	int randomX = 0;//случайный элемент по горизонтали
	int randomY = 0;//случ эл-т по вертикали
	srand(time(0));//рандом	
	int countSphere = 10;//количество камней
	int countPoison = 20;
	int countHeal = 3;

	while (countSphere > 0) {
		randomX = 1 + rand() % (WIDTH_MAP - 1);//рандомное по иксу от 1 до ширина карты-1, чтобы не получать числа бордюра карты
		randomY = 1 + rand() % (HEIGHT_MAP - 1);//по игреку так же

		if (TileMap[randomY][randomX] == ' '&&
			randomX != 8 && randomX != 9 && randomX != 10 && randomX != 11 &&
			randomX != 7 && randomX != 6 && randomX != 5 &&
			randomY != 8 && randomY != 9 && randomY != 10 && randomY != 11 &&
			randomY != 7 && randomY != 6 && randomY != 5) {
			TileMap[randomY][randomX] = 's'; //то ставим туда камень.
			countSphere--;
		}
	}

	while (countPoison > 0) {
		randomX = 1 + rand() % (WIDTH_MAP - 1);//рандомное по иксу от 1 до ширина карты-1, чтобы не получать числа бордюра карты
		randomY = 1 + rand() % (HEIGHT_MAP - 1);//по игреку так же

		if (TileMap[randomY][randomX] == ' ' &&
			randomX != 8 && randomX != 9 && randomX != 10 && randomX != 11 &&
			randomX != 7 && randomX != 6 && randomX != 5 &&
			randomY != 8 && randomY != 9 && randomY != 10 && randomY != 11 &&
			randomY != 7 && randomY != 6 && randomY != 5) {
			TileMap[randomY][randomX] = 'p'; //то ставим туда камень.
			countPoison--;
		}
	}
	while (countHeal > 0){
		randomX = 1 + rand() % (WIDTH_MAP - 1);//рандомное по иксу от 1 до ширина карты-1, чтобы не получать числа бордюра карты
		randomY = 1 + rand() % (HEIGHT_MAP - 1);//по игреку так же

		if (TileMap[randomY][randomX] == ' ' &&
			randomX != 8 && randomX != 9 && randomX != 10 &&
			randomX != 7 && randomX != 6 &&
			randomY != 8 && randomY != 9 && randomY != 10 &&
			randomY != 7 && randomY != 6) {
			TileMap[randomY][randomX] = '+'; //то ставим туда камень.
			countHeal--;
		}
	}



}