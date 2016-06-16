/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"
#include "i386.h"

unsigned int X_A;
unsigned int Y_A;
unsigned int X_B;
unsigned int Y_B;

unsigned short dameTarea(){
  return (rtr() >> 3);
}


void game_mover_cursor(int jugador, direccion dir) {

	if (jugador==0) // Jugador A
	{
		switch(dir)
		{
			case IZQ:
			//print(,X_A,Y_A,);
			X_A--;
			X_A=X_A % 80;
			// print(,X_A,Y_A,);
			break;

			case DER:
			//print(,X_A,Y_A,);
			X_A++;
			X_A=X_A % 80;
			// print(,X_A,Y_A,);

			break;
			case ARB:
			//print(,X_A,Y_A,);
			Y_A++;
			Y_A=Y_A % 44;
			// print(,X_A,Y_A,);

			break;
			case ABA:
			//print(,X_A,Y_A,);
			Y_A--;
			Y_A=Y_A % 44;
			// print(,X_A,Y_A,);
			
			break;
		}

	}

	else // Jugador B
	{
			switch(dir)
		{
			case IZQ:


			break;

			case DER:

			break;
			case ARB:

			break;
			case ABA:

			break;
		}
	}

}

void game_lanzar(unsigned int jugador) {
}

void game_soy(unsigned int yoSoy) {

}

void game_donde(unsigned int* pos) {
}

void game_mapear(int x, int y) {
}
