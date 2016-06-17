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
	/*Definicion Cursores
	A es Fondo ROJO con Caracter Nulo

	*/
	if (jugador==0) // Jugador A
	{
		switch(dir)
		{
			case IZQ:
			print(0,X_A,Y_A+1,C_BG_LIGHT_GREY);
			X_A--;
			X_A=X_A % 80;
			print(0,X_A,Y_A+1,C_BG_RED);
			break;

			case DER:
			print(0,X_A,Y_A+1,C_BG_LIGHT_GREY);
			X_A++;
			X_A=X_A % 80;
			print(0,X_A,Y_A+1,C_BG_RED);

			break;
			case ARB:
			print(0,X_A,Y_A+1,C_BG_LIGHT_GREY);
			Y_A++;
			Y_A=Y_A % 44;
			print(0,X_A,Y_A+1,C_BG_RED);

			break;
			case ABA:
			print(0,X_A,Y_A,C_BG_LIGHT_GREY);
			Y_A--;
			Y_A=Y_A % 44;
			print(0,X_A,Y_A,C_BG_RED);
			
			break;
		}

	}

	else // Jugador B
	{		switch(dir)
		{
			case IZQ:
			print(0,X_B,Y_B,C_BG_LIGHT_GREY);
			X_B--;
			X_B=X_B % 80;
			print(0,X_A,Y_A,C_BG_BLUE);
			break;

			case DER:
			print(0,X_A,Y_A,C_BG_LIGHT_GREY);
			X_B++;
			X_B=X_B % 80;
			print(0,X_A,Y_A,C_BG_BLUE);

			break;
			case ARB:
			print(0,X_A,Y_A+1,C_BG_LIGHT_GREY);
			Y_B++;
			Y_B=Y_B % 44;
			print(0,X_A,Y_A+1,C_BG_BLUE);

			break;
			case ABA:
			print(0,X_A,Y_A,C_BG_LIGHT_GREY);
			Y_B--;
			Y_B=Y_B % 44;
			print(0,X_A,Y_A,C_BG_BLUE);
			
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
