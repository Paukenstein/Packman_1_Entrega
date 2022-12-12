

#include <iostream>
#include <conio.h>

#define MAP_VERTICAL 29 
#define MAP_HORIZONTAL 120 
#define SALTO_LINEA std::cout<<std::endl
#define PERSONAJE '@';
#define AZUL "\x1b[34m";
#define BLANCO "\x1b[37m"
#define AMARILLO "\x1b[33m"

enum TILES { EMPTY = ' ', WALL = 219, POINT = 'o' }; 

TILES map[MAP_VERTICAL][MAP_HORIZONTAL]; 
bool run = true; 
enum INPUT { QUIT, UP, DOWN, LEFT, RIGHT, UNKNOWN }; 
INPUT currentInput = INPUT::UNKNOWN;

int personeje_x;
int personaje_y;
int puntuacion_actual = 0;
int puntuacion_total;
int total_points = 15;

/*PREPARACION DEL JUEGO*/
void Setup() {
	personaje_y = MAP_VERTICAL / 2; 
	personeje_x = MAP_HORIZONTAL / 2;


	for (size_t i = 0; i < MAP_VERTICAL; i++)
	{
		for (size_t j = 0; j < MAP_HORIZONTAL; j++)
		{
			if (i == 0 || j == 0 || i == MAP_VERTICAL - 1 || j == MAP_HORIZONTAL - 1) { 
				map[i][j] = TILES::WALL;
			}
			else {
				map[i][j] = TILES::EMPTY;
			}

		}
	}


	/*CREAMOS LOS "COCOS"*/
	map[14][15] = TILES::POINT;
	map[14][72] = TILES::POINT;
	map[14][90] = TILES::POINT;
	map[14][20] = TILES::POINT;
	map[14][30] = TILES::POINT;
	map[14][50] = TILES::POINT;
	map[14][70] = TILES::POINT;
	map[14][30] = TILES::POINT;
	map[14][40] = TILES::POINT;
	map[14][45] = TILES::POINT;
	map[14][55] = TILES::POINT;
	map[14][35] = TILES::POINT;
	map[14][75] = TILES::POINT;
	map[14][73] = TILES::POINT;
	map[14][25] = TILES::POINT;
	map[14][23] = TILES::POINT;


	/*CREAMOS LAS "PUERTAS"*/
	map[11][0] = TILES::EMPTY;
	map[12][0] = TILES::EMPTY;
	map[13][0] = TILES::EMPTY;
	map[14][0] = TILES::EMPTY;

	map[11][MAP_HORIZONTAL - 1] = TILES::EMPTY;
	map[12][MAP_HORIZONTAL - 1] = TILES::EMPTY;
	map[13][MAP_HORIZONTAL - 1] = TILES::EMPTY;
	map[14][MAP_HORIZONTAL - 1] = TILES::EMPTY;

	map[0][58] = TILES::EMPTY;
	map[0][59] = TILES::EMPTY;
	map[0][60] = TILES::EMPTY;
	map[0][61] = TILES::EMPTY;
	map[0][62] = TILES::EMPTY;

	map[MAP_VERTICAL - 1][58] = TILES::EMPTY;
	map[MAP_VERTICAL - 1][59] = TILES::EMPTY;
	map[MAP_VERTICAL - 1][60] = TILES::EMPTY;
	map[MAP_VERTICAL - 1][61] = TILES::EMPTY;
	map[MAP_VERTICAL - 1][62] = TILES::EMPTY;



}

/*RECOGIDA DE INPUTS DEL USUARIO*/
void Inputs() {
	char input = _getch();
	switch (input)
	{
	case'W':
	case'w':
		currentInput = INPUT::UP;
		break;
	case'a':
	case'A':
		currentInput = INPUT::LEFT;
		break;
	case's':
	case'S':

		currentInput = INPUT::DOWN;
		break;
	case'd':
	case'D':
		currentInput = INPUT::RIGHT;
		break;
	case'q':
	case'Q':
		currentInput = INPUT::QUIT;
		break;
	default:
		currentInput = INPUT::UNKNOWN;
		break;
	}

}

/*APLICAMOS LA LOGICA DEL JUEGO*/
void Logic() {
	int personaje_y_new = personaje_y; 
	int persomnaje_x_new = personeje_x;

	switch (currentInput)
	{
	case QUIT:
		run = false;
		break;
	case UP:
		personaje_y_new--;

		break;
	case DOWN:
		personaje_y_new++;
		break;
	case LEFT:
		persomnaje_x_new--;
		break;
	case RIGHT:
		persomnaje_x_new++;
		break;
	}

	/*TELETRANSPORTE*/
	if (persomnaje_x_new < 0)
	{
		persomnaje_x_new = MAP_HORIZONTAL - 1;
	}
	
	persomnaje_x_new = persomnaje_x_new % MAP_HORIZONTAL; 
	if (personaje_y_new < 0)
	{
		personaje_y_new = MAP_VERTICAL - 1;
	}
	personaje_y_new = personaje_y_new % MAP_VERTICAL;

	switch (map[personaje_y_new][persomnaje_x_new])
	{
	case TILES::WALL: 
		break;
	case TILES::POINT: 
		puntuacion_actual++; 
		map[personaje_y_new][persomnaje_x_new] = TILES::EMPTY;
		if (puntuacion_actual == total_points)
		{

			run = false;
		}
	default:
		personaje_y = personaje_y_new;
		personeje_x = persomnaje_x_new;
		puntuacion_total = puntuacion_actual;

		break;
	}
}

/*PARTE GRAFICA DEL CODIGO*/
void Draw() {
	system("CLS");
	system("Color 01"); //Cambiamos el color de la letra a azul

	/*Diobujamos el mapa, el personaje i los "cocos"*/
	for (size_t i = 0; i < MAP_VERTICAL; i++)
	{
		for (size_t j = 0; j < MAP_HORIZONTAL; j++)

			if (i == personaje_y && j == personeje_x) 
			{
				std::cout << BLANCO; std::cout << PERSONAJE std::cout << AZUL; //Cambiamos el color del personaje


			}
			else
			{
				if (map[i][j] == TILES::POINT)
				{
					std::cout << AMARILLO; std::cout << (char)map[i][j]; std::cout << AZUL //Cambiamos el color de los "cocos"

				}
				else {
					std::cout << (char)map[i][j]; 
				}
			}

	}
	SALTO_LINEA;

	/*Escribimos puntuacion */
	std::cout << "Puntuacio: ";
	std::cout << puntuacion_total;
	std::cout << '/';
	std::cout << total_points;
	if (puntuacion_actual == total_points)
	{
		std::cout << " WIN!!";
	}


}


/*FUNCION MAIN (llamamos a las otras funciones)*/
int main()
{
	Setup();
	Draw();
	while (run) {
		Inputs();
		Logic();
		Draw();
	}
}
