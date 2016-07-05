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
char pila[2000]; // Mi idea es usar este registro como pila de la pantalla
unsigned int ack[25]; // Mi Idea es usar este registro como pila para los valores de debug


unsigned int dameack()
{

	return (unsigned int) &ack;
}

void copiar()
{ //Quiero que esta funcion copie el buffer del video
	char * video = (char*) 0xB8000;
	int pos = 0 ;

		//video +=1280;
		//pila[0] = *video;
		int i = 8;
		for (i = 8; i < 43; ++i)
		{
			int j = 25;
			for (j = 25; j < 55; ++j)
			{
				//*(video+(160*i)+(2*j))=pila[pos];
				pila[pos]=*(video+(160*i)+(2*j));
				pos ++;
				//*(video+(160*i)+(2*j)+1)=pila[pos];
				pila[pos]=*((video+1)+(160*i)+(2*j));
				pos++;
			}

		}

}


void pegar()
{
	char * video = (char*) 0xB8000;
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
}

void debug()
{	//Tenemos que mostrar



}


void atenderdebug()
{
	//char * video = (char*) 0xB8000;
	if (debugActivado==0) // A Activar...
	{
		copiar();
		debugActivado=1; //Activo flag debug
		print("WALLYYYYYYYYYYYYYYY",26,8,C_FG_RED);
		print("WALLYYYYYYYYYYYYYYY",26,9,C_FG_RED);
		print("WALLYYYYYYYYYYYYYYY",26,10,C_FG_RED);
		print("WALLYYYYYYYYYYYYYYY",26,11,C_FG_RED);
		print("WALLYYYYYYYYYYYYYYY",26,12,C_FG_RED);


	}


	else // Hay que desactivar
	{
		pegar();
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
	print("TAREAS", 68, 46, (C_BG_BLACK | C_FG_LIGHT_GREY));
	print("TAREAS", 34, 46, (C_BG_BLACK | C_FG_LIGHT_GREY));
	print_int(0, 48, 70, (C_BG_BLACK | C_FG_WHITE));
	print_int(0, 48, 36, (C_BG_BLACK | C_FG_WHITE));
  print_int(0, 47, 51, (C_BG_RED | C_FG_WHITE));
  print_int(0, 47, 57, (C_BG_BLUE | C_FG_WHITE));
	print("<A", 13, 46, (C_BG_BLACK | C_FG_LIGHT_GREY));
	print("B>", 20, 46, (C_BG_BLACK | C_FG_LIGHT_GREY));
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
			if(X_A==0){X_A++;}
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
			if(X_B==0){X_B++;}
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
			sumarTareaLanzada(jugador);
			print_int((tareasEnJuego[jugador]), 48, 70, (C_BG_BLACK | C_FG_WHITE));
      print_int(vidasAzul, 48, 63, (C_BG_BLACK | C_FG_WHITE));
    }else if(jugador == 0 && vidasRojas > 0){
      inicializar_tss(0x11000, X_A, Y_A);
      pintarTarea(X_A, Y_A, 0);
      vidasRojas--;
			sumarTareaLanzada(jugador);
			print_int((tareasEnJuego[jugador]), 48, 36, (C_BG_BLACK | C_FG_WHITE));
      print_int(vidasRojas, 48, 44, (C_BG_BLACK | C_FG_WHITE));
    }
  }
}

void game_soy(unsigned int yoSoy) {

}

void game_donde(unsigned int* pos) {
}

char validarXY(int x, int y){
	int k = (x >= 0 && x < 80 && y > 0 && y < 40);
	return k;
}

void game_mapear(int x, int y) {
	print_int(0, tareaActual->posicion.y, tareaActual->posicion.x, (C_BG_LIGHT_GREY | C_FG_LIGHT_GREY));
	tareaActual->posicion.x = x;
	tareaActual->posicion.y = y;
	unsigned int cr3 = rcr3();
	unsigned int dirAMapear = (y + x*80)*4096 + 0x400000;
	if(validarXY(x,y)){
		mmu_mapear_pagina_tarea(0x08001000, cr3, dirAMapear);
		pintarTarea(y, x, tareaActual->dueno);
	}
}


void pintarTareaActual(){
	int x = tareaActual->posicion.x;
	int y = tareaActual->posicion.y;
	int player = tareaActual->dueno;
	pintarTarea(y, x, player);
}


void pintarPuntajeRojo(){
  puntajeRojo++;
	tareaActual->dueno = 0;
  print_int(puntajeRojo, 47, 51, (C_BG_RED | C_FG_WHITE));
}

void pintarPuntajeAzul(){
  puntajeAzul++;
	tareaActual->dueno = 1;
  print_int(puntajeAzul, 47, 57, (C_BG_BLUE | C_FG_WHITE));
}

void actualizarReloj(){
	char * rel;
	switch (tareaActual->posReloj) {
		case 0:
			rel = "|";
			break;
		case 1:
			rel = "/";
			break;
		case 2:
			rel = "-";
			break;
		case 3:
			rel = "\\";
	}
	if(tareaActual->dueno == 2){
		print(rel, 2*tareaActual->relojPropioX, 48, (C_BG_BLACK | C_FG_LIGHT_GREY));
	}else if(tareaActual->dueno == 1){
		print(rel, 2*(9 + tareaActual->relojPropioX), 46, (C_BG_BLACK | C_FG_LIGHT_GREY));
	}else{
		print(rel, 2*tareaActual->relojPropioX, 46, (C_BG_BLACK | C_FG_LIGHT_GREY));
	}
	tareaActual->posReloj = (tareaActual->posReloj + 1) % 4;
}

void volverDeExcepcion(){
	//breakpoint();
	int q = 0;
	int indiceTareaABorrar = 0;
	for(q = 0; q < 3; q++){
		for(indiceTareaABorrar = 0; indiceTareaABorrar < 15; indiceTareaABorrar++){
			if(esMismaTarea(&jugadores[q][indiceTareaABorrar], tareaActual)){
				break;
			}
		}
		if(esMismaTarea(&jugadores[q][indiceTareaABorrar], tareaActual)){
			break;
		}
	}
	jugadores[q][indiceTareaABorrar].presente = 0;
  switch (q) {
    case 0:
			break;
    case 1:
			tareasEnJuego[0] -= 1;
			print_int((tareasEnJuego[0]), 48, 36, (C_BG_BLACK | C_FG_WHITE));
			break;
    case 2:
			tareasEnJuego[1] -= 1;
			print_int((tareasEnJuego[1]), 48, 70, (C_BG_BLACK | C_FG_WHITE));
			break;
    }
    gdt[tareaActual->indiceGdt].p = 0;
    print_int(0, tareaActual->posicion.x, tareaActual->posicion.y, (C_BG_LIGHT_GREY | C_FG_LIGHT_GREY));
}
