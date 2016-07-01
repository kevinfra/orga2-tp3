/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"
#include "i386.h"
#include "screen.h"
#include "colors.h"
#include "defines.h"

int X_A;
int Y_A;
int X_B;
int Y_B;
int puntajeRojo;
int puntajeAzul;
int juegoEstaIniciado = 0;

void iniciarGame(){
  X_A=0;
  Y_A=0;
  X_B=0;
  Y_B=79;
  puntajeAzul = 0;
  puntajeRojo = 0;
  print_int(puntajeRojo, 48, 51, (C_BG_RED | C_FG_WHITE));
  print_int(puntajeAzul, 48, 57, (C_BG_BLUE | C_FG_WHITE));
  //print_int(0, 20, 20, (C_BG_RED | C_FG_RED));
  //print_int(0, 20, 50, (C_BG_BLUE | C_FG_BLUE));
  print("Yo no manejo el rating, yo manejo un rolls-royce", 4, 0, (C_BG_BLACK | C_FG_WHITE));
  juegoEstaIniciado = 1;
  pintarTarea(X_A+1,Y_A,0); // Pinta Rojo
  pintarTarea(X_B+1,Y_B,1); // Pinta Azul
}

int juegoIniciado(){
  return juegoEstaIniciado;
}

void pintarTarea(int x, int y, int jugador){ //0 = A, 1=B 2=H
  switch (jugador) {
    case 0:
      print_int(0, x, y, (C_BG_RED | C_FG_RED));
      break;
    case 1:
      print_int(0, x, y, (C_BG_BLUE | C_FG_BLUE));
      break;
    case 2:
      print_int(0, x, y, (C_BG_GREEN | C_FG_GREEN));
      break;
   }
}

void pintarGris(int x, int y)
{
	print_int(0,x,y,C_FG_LIGHT_GREY | C_BG_LIGHT_GREY);
}


unsigned short dameTarea(){
  return (rtr() << 3);
}


void game_mover_cursor(int jugador, direccion dir) {

	if (jugador==0) // Jugador A
	{
		switch(dir)
		{
			case IZQ:
			pintarGris(X_A+1,Y_A);
			Y_A--;
			if(Y_A==-1)
				{
					Y_A++;
				}
			pintarTarea(X_A+1,Y_A,0);
			break;

			case DER:
			pintarGris(X_A+1,Y_A);
			Y_A++;
			if(Y_A==80)
				{
					Y_A--;
				}
			pintarTarea(X_A+1,Y_A,0);

			break;

			case ARB:
			pintarGris(X_A+1,Y_A);
			X_A--;
			if(X_A==-1){X_A++;}
			pintarTarea(X_A+1,Y_A,0);

			break;
			case ABA:
			pintarGris(X_A+1,Y_A);
			X_A++;
			if(X_A==44){X_A--;}
			pintarTarea(X_A+1,Y_A,0);

			break;
		}

	}

	else // Jugador B
	{		switch(dir)
		{
			case IZQ:
			pintarGris(X_B+1,Y_B);
			Y_B--;
			if(Y_B==-1)
				{
					Y_B++;
				}
			pintarTarea(X_B+1,Y_B,1);
			break;

			case DER:
			pintarGris(X_B+1,Y_B);
			Y_B++;
			if(Y_B==80)
				{
					Y_B--;
				}
			pintarTarea(X_B+1,Y_B,1);

			break;

			case ARB:
			pintarGris(X_B+1,Y_B);
			X_B--;
			if(X_B==-1){X_B++;}
			pintarTarea(X_B+1,Y_B,1);

			break;
			case ABA:
			pintarGris(X_B+1,Y_B);
			X_B++;
			if(X_B==44){X_B--;}
			pintarTarea(X_B+1,Y_B,1);

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
