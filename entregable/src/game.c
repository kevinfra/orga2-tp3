/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"
#include "tss.h"
#include "gdt.h"
#include "sched.h"

int X_A;
int Y_A;
int X_B;
int Y_B;
int puntajeRojo;
int puntajeAzul;
int juegoEstaIniciado = 0;
int tareasEnJuego[2];

void iniciarGame(){
  X_A=20;
  Y_A=20;
  X_B=20;
  Y_B=50;
  puntajeAzul = 0;
  puntajeRojo = 0;
  print_int(puntajeRojo, 48, 51, (C_BG_RED | C_FG_WHITE));
  print_int(puntajeAzul, 48, 57, (C_BG_BLUE | C_FG_WHITE));
  print_int(0, 20, 20, (C_BG_RED | C_FG_RED));
  print_int(0, 20, 50, (C_BG_BLUE | C_FG_BLUE));
  print("Yo no manejo el rating, yo manejo un rolls-royce", 14, 0, (C_BG_BLACK | C_FG_WHITE));
  juegoEstaIniciado = 1;
  tareasEnJuego[0] = 0;
  tareasEnJuego[1] = 0;
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
int tareasLanzadas(unsigned int jugador){
  return tareasEnJuego[jugador];
}

void sumarTareaLanzada(unsigned int jugador){
  tareasEnJuego[jugador] += 1;
}

void game_lanzar(unsigned int jugador) {
  if(juegoEstaIniciado && tareasLanzadas(jugador) < 5){
    if(jugador == 1){ // azul
      inicializar_tss(0x12000, 25, 25);
      pintarTarea(X_B, Y_B, 1);
    }else if(jugador == 0){
      inicializar_tss(0x11000, 25, 25);
      pintarTarea(X_A, Y_A, 0);
    }
    sumarTareaLanzada(jugador);
  }
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


void volverDeExcepcion(){
    switch (colaActual) {
      case 0:
        if(proximoColaB == 0){
          colaJugadorB[4].presente = 0;
        }else{
          colaJugadorB[proximoColaB-1].presente = 0;
        }
      case 1:
        if(proximoColaNadie == 0){
          colaNadie[14].presente = 0;
        }else{
          colaNadie[proximoColaNadie-1].presente = 0;
        }
      case 2:
        if(proximoColaA == 0){
          colaJugadorA[4].presente = 0;
        }else{
          colaJugadorA[proximoColaA-1].presente = 0;
        }
    }
    gdt[tareaActual.indiceGdt].p = 0;
    print_int(0, tareaActual.posicion.x, tareaActual.posicion.y, (C_BG_LIGHT_GREY | C_FG_LIGHT_GREY));
    mmu_unmapear_pagina(0x08000000, tareaActual.cr3Actual);
    mmu_unmapear_pagina(0x08001000, tareaActual.cr3Actual);
  }
