/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"
#include "tss.h"
#include "gdt.h"
#include "sched.h"

int debugActivado;
int X_A;
int Y_A;
int X_B;
int Y_B;
int puntajeRojo;
int puntajeAzul;
int juegoEstaIniciado = 0;
int tareasEnJuego[2];
int vidasAzul;
int vidasRojas;
char pila[4320];
short second[2160];

char dameflag()
{
	return (unsigned int) debugActivado;
}

unsigned int damepila()
{
	return (unsigned int) &pila;
}

void atenderdebug()
{
	char * video = (char*) 0xB800;
	if (debugActivado==0) // A Activar...
	{
		int pos = 0 ;

		//video +=1280;
		//pila[0] = *video;
		int i = 8;
		for (i = 8; i < 43; ++i)
		{
			int j = 25;
			for (j = 25; j < 55; ++j)
			{
				pila[pos]=*(video+(160*i)+(2*j));
				pos ++;
				pila[pos]=*((video+1)+(160*i)+(2*j));
				pos++;
			}
			debugActivado=1;
		}
		//A modificar la pantalla
		//*(base+offset)
		print("WALLYYYYYYYYYYYYYYY",26,8,C_FG_RED);
		print("WALLYYYYYYYYYYYYYYY",26,9,C_FG_RED);
		print("WALLYYYYYYYYYYYYYYY",26,10,C_FG_RED);
		print("WALLYYYYYYYYYYYYYYY",26,11,C_FG_RED);
		print("WALLYYYYYYYYYYYYYYY",26,12,C_FG_RED);
		print("WALLYYYYYYYYYYYYYYY",26,13,C_FG_RED);
		print("WALLYYYYYYYYYYYYYYY",26,14,C_FG_RED);

	}


	else // Hay que desactivar
	{
		int pos = 0 ;

		//video +=1280;
		//pila[0] = *video;
		int i = 8;
		for (i = 8; i < 43; ++i)
		{
			int j = 25;
			for (j = 25; j < 55; ++j)
			{
				*(video+(160*i)+(2*j))=pila[pos];
				//pila[pos]=*(video+(160*i)+(2*j));
				pos ++;
				*(video+(160*i)+(2*j)+1)=pila[pos];
				//pila[pos]=*((video+1)+(160*i)+(2*j));
				pos++;
			}

		}

		debugActivado = 0 ;
	}

}

void iniciarGame(){
  X_A=20;
  Y_A=20;
  X_B=20;
  Y_B=50;
  debugActivado=0; // 0 Desactivado , 1 Activado
  puntajeAzul = 0;
  puntajeRojo = 0;
  print("Yo no manejo el rating, yo manejo un rolls-royce", 14, 0, (C_BG_BLACK | C_FG_WHITE));
  juegoEstaIniciado = 1;
  tareasEnJuego[0] = 0;
  tareasEnJuego[1] = 0;
  pintarTarea(X_A,Y_A,0); // Pinta Rojo
  pintarTarea(X_B,Y_B,1); // Pinta Azul
  vidasAzul = 15;
  vidasRojas = 15;
  print_int(vidasRojas, 48, 44, (C_BG_BLACK | C_FG_WHITE));
  print_int(vidasAzul, 48, 63, (C_BG_BLACK | C_FG_WHITE));
  print_int(0, 47, 51, (C_BG_RED | C_FG_WHITE));
  print_int(0, 47, 57, (C_BG_BLUE | C_FG_WHITE));
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
			pintarGris(X_A,Y_A);
			Y_A--;
			if(Y_A==-1)
				{
					Y_A++;
				}
			pintarTarea(X_A,Y_A,0);
			break;

			case DER:
			pintarGris(X_A,Y_A);
			Y_A++;
			if(Y_A==80)
				{
					Y_A--;
				}
			pintarTarea(X_A,Y_A,0);

			break;

			case ARB:
			pintarGris(X_A,Y_A);
			X_A--;
			if(X_A==-1){X_A++;}
			pintarTarea(X_A,Y_A,0);

			break;
			case ABA:
			pintarGris(X_A,Y_A);
			X_A++;
			if(X_A==45){X_A--;}
			pintarTarea(X_A,Y_A,0);

			break;
		}

	}

	else // Jugador B
	{		switch(dir)
		{
			case IZQ:
			pintarGris(X_B,Y_B);
			Y_B--;
			if(Y_B==-1)
				{
					Y_B++;
				}
			pintarTarea(X_B,Y_B,1);
			break;

			case DER:
			pintarGris(X_B,Y_B);
			Y_B++;
			if(Y_B==80)
				{
					Y_B--;
				}
			pintarTarea(X_B,Y_B,1);

			break;

			case ARB:
			pintarGris(X_B,Y_B);
			X_B--;
			if(X_B==-1){X_B++;}
			pintarTarea(X_B,Y_B,1);

			break;
			case ABA:
			pintarGris(X_B,Y_B);
			X_B++;
			if(X_B==44){X_B--;}
			pintarTarea(X_B,Y_B,1);

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
    if(jugador == 1 && vidasAzul > 0){ // azul
      inicializar_tss(0x12000, X_B, Y_B);
      pintarTarea(X_B, Y_B, 1);
      vidasAzul--;
      print_int(vidasAzul, 48, 63, (C_BG_BLACK | C_FG_WHITE));
    }else if(jugador == 0 && vidasRojas > 0){
      inicializar_tss(0x11000, X_A, Y_A);
      pintarTarea(X_A, Y_A, 0);
      vidasRojas--;
      print_int(vidasRojas, 48, 44, (C_BG_BLACK | C_FG_WHITE));
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
  //breakpoint();
  unsigned int cr3 = rcr3();
  unsigned int dirAMapear = (x + y*80)*4096 + 400000;
  mmu_mapear_pagina(tareaAMapear, cr3, dirAMapear);

}


void pintarPuntajeRojo(){
  puntajeRojo++;
  print_int(puntajeRojo, 47, 51, (C_BG_RED | C_FG_WHITE));
}

void pintarPuntajeAzul(){
  puntajeAzul++;
  print_int(puntajeAzul, 47, 57, (C_BG_BLUE | C_FG_WHITE));
}


void volverDeExcepcion(){
  //breakpoint();
    short colaDeTareaMuerta = (colaActual - 1) % 3;
    int indiceTareaABorrar;
    switch (colaActual) {
      case 0:
        indiceTareaABorrar = (siguienteIndiceDeTareaEnCola[colaDeTareaMuerta]);
        jugadores[colaJugadorB][indiceTareaABorrar].presente = 0;
        tareasEnJuego[1] -= 1;
        break;
      case 1:
        indiceTareaABorrar = (siguienteIndiceDeTareaEnCola[colaDeTareaMuerta]);
        jugadores[colaNadie][indiceTareaABorrar].presente = 0;
        break;
      case 2:
        indiceTareaABorrar = (siguienteIndiceDeTareaEnCola[colaDeTareaMuerta]);
        jugadores[colaJugadorA][indiceTareaABorrar].presente = 0;
        tareasEnJuego[0] -= 1;
        break;
    }
    gdt[tareaActual.indiceGdt].p = 0;
    print_int(0, tareaActual.posicion.x, tareaActual.posicion.y, (C_BG_LIGHT_GREY | C_FG_LIGHT_GREY));
}
