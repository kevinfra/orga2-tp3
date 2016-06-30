/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"
#include "i386.h"
#include "screen.h"
#include "colors.h"

int X_A;
int Y_A;
int X_B;
int Y_B;
int puntajeRojo;
int puntajeAzul;

void iniciarPuntaje(){
  X_A=1;
  Y_A=0;
  X_B=1;
  Y_B=79;	
  puntajeAzul = 0;
  puntajeRojo = 0;
  print_int(puntajeRojo, 48, 51, (C_BG_RED & C_FG_WHITE));
  print_int(puntajeAzul, 48, 57, (C_BG_BLUE & C_FG_WHITE));

}

unsigned short dameTarea(){
  return (rtr() << 3);
}


void game_mover_cursor(int jugador, direccion dir) {
	/*Definicion Cursores
	A es Fondo ROJO con Caracter *
	B es Fondo AZUL con Caracter *

	*/
	if (jugador==0) // Jugador A
	{
		switch(dir)
		{
			case IZQ:
			print(0,X_A,Y_A+1,C_BG_LIGHT_GREY);
			X_A--;
			if(X_A==-1){X_A++;}
			print(0,X_A,Y_A+1,C_BG_RED);
			break;

			case DER:
			print(0,X_A,Y_A,C_BG_LIGHT_GREY);
			X_A++;
			if(X_A==80){X_A--;}
			print(0,X_A,Y_A,C_BG_RED);

			break;
			case ARB:
			print(0,X_A,Y_A,C_BG_LIGHT_GREY);
			Y_A--;
			if(Y_A==-1){Y_A++;};
			print(0,X_A,Y_A,C_BG_RED);

			break;
			case ABA:
			print(0,X_A,Y_A,C_BG_LIGHT_GREY);
			Y_A++;
			if(Y_A==45){Y_A--;};
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
			if(X_B==-1){X_B++;}
			print(0,X_A,Y_A,C_BG_BLUE);
			break;

			case DER:
			print(0,X_A,Y_A,C_BG_LIGHT_GREY);
			X_B++;
			if(X_B==80){X_B--;}
			print(0,X_A,Y_A,C_BG_BLUE);

			break;
			case ARB:
			print(0,X_A,Y_A,C_BG_LIGHT_GREY);
			Y_B++;
			if(Y_B==-1){Y_B++;};
			print(0,X_A,Y_A+1,C_BG_BLUE);

			break;
			case ABA:
			print(0,X_A,Y_A,C_BG_LIGHT_GREY);
			Y_B++;
			if(Y_B==45){Y_B--;};
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
  unsigned int tareaAMapear = (unsigned int) dameTarea();
  unsigned int cr3 = rcr3();
  unsigned int dirAMapear = (x + y*80)*4096 + 400000;
  mmu_mapear_pagina(tareaAMapear, cr3, dirAMapear);

}


void pintarPuntajeRojo(){
  puntajeRojo++;
  print_int(puntajeRojo, 48, 51, (C_BG_RED & C_FG_WHITE));
}

void pintarPuntajeAzul(){
  puntajeAzul++;
  print_int(puntajeAzul, 48, 57, (C_BG_BLUE & C_FG_WHITE));
}
