#include <SFML\Graphics.hpp>
const int HEIGHT_MAP = 25;//������ ����� ������
const int WIDTH_MAP = 40;//������ ����� ������ 


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

void randomMapGenerate() {//�������� ����������� �����

	int randomX = 0;//��������� ������� �� �����������
	int randomY = 0;//���� ��-� �� ���������
	srand(time(0));//������	
	int countSphere = 10;//���������� ������
	int countPoison = 20;
	int countHeal = 3;

	while (countSphere > 0) {
		randomX = 1 + rand() % (WIDTH_MAP - 1);//��������� �� ���� �� 1 �� ������ �����-1, ����� �� �������� ����� ������� �����
		randomY = 1 + rand() % (HEIGHT_MAP - 1);//�� ������ ��� ��

		if (TileMap[randomY][randomX] == ' '&&
			randomX != 8 && randomX != 9 && randomX != 10 && randomX != 11 &&
			randomX != 7 && randomX != 6 && randomX != 5 &&
			randomY != 8 && randomY != 9 && randomY != 10 && randomY != 11 &&
			randomY != 7 && randomY != 6 && randomY != 5) {
			TileMap[randomY][randomX] = 's'; //�� ������ ���� ������.
			countSphere--;
		}
	}

	while (countPoison > 0) {
		randomX = 1 + rand() % (WIDTH_MAP - 1);//��������� �� ���� �� 1 �� ������ �����-1, ����� �� �������� ����� ������� �����
		randomY = 1 + rand() % (HEIGHT_MAP - 1);//�� ������ ��� ��

		if (TileMap[randomY][randomX] == ' ' &&
			randomX != 8 && randomX != 9 && randomX != 10 && randomX != 11 &&
			randomX != 7 && randomX != 6 && randomX != 5 &&
			randomY != 8 && randomY != 9 && randomY != 10 && randomY != 11 &&
			randomY != 7 && randomY != 6 && randomY != 5) {
			TileMap[randomY][randomX] = 'p'; //�� ������ ���� ������.
			countPoison--;
		}
	}
	while (countHeal > 0){
		randomX = 1 + rand() % (WIDTH_MAP - 1);//��������� �� ���� �� 1 �� ������ �����-1, ����� �� �������� ����� ������� �����
		randomY = 1 + rand() % (HEIGHT_MAP - 1);//�� ������ ��� ��

		if (TileMap[randomY][randomX] == ' ' &&
			randomX != 8 && randomX != 9 && randomX != 10 &&
			randomX != 7 && randomX != 6 &&
			randomY != 8 && randomY != 9 && randomY != 10 &&
			randomY != 7 && randomY != 6) {
			TileMap[randomY][randomX] = '+'; //�� ������ ���� ������.
			countHeal--;
		}
	}



}