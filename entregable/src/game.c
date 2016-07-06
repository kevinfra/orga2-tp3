/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"
#include "tss.h"
#include "gdt.h"
#include "sched.h"


unsigned int debugActivado;
unsigned int muestraInfo;
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
char pila[3040]; // Mi idea es usar este registro como pila de la pantalla
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
		for (i = 5; i < 43; ++i)
		{
			int j = 19;
			for (j = 19; j < 59; ++j)
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
		for (i = 5; i < 43; ++i)
		{
			int j = 19;
			for (j = 19; j < 59; ++j)
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

void habilitarDebug(){
	if(muestraInfo == 1){
		muestraInfo = 0;
		pegar();
	}
	debugActivado = 1;
}

void despintarPantallaDebug(){
	muestraInfo = 0;
}

unsigned int estaPintadoDebug(){
	return muestraInfo;
}

void limipiarPantallaDebug(){
	int fila;
	for (fila = 5; fila < 43; ++fila)
	{
		int columna;
		for (columna = 19; columna < 59; ++columna)
		{
			print("a",columna,fila,C_FG_LIGHT_GREY | C_BG_LIGHT_GREY );
		}

	}
}

void pintarRecuadroDebug(){

}


void atenderdebug(unsigned int cr0, unsigned int cr2, unsigned int cr3, unsigned int cr4, unsigned int ebx, unsigned int ecx, unsigned int edx, unsigned int esi,
	unsigned int edi, unsigned int ebp, unsigned int ds,unsigned int es, unsigned int fs, unsigned int gs,
	unsigned int ss, unsigned int esp, unsigned int eflags, unsigned int cs, unsigned int eip,unsigned int eax)
{
	//char * video = (char*) 0xB8000;
	if (debugActivado==1) // Si esta activado...
	{
		muestraInfo = 1;
		copiar();
		limipiarPantallaDebug();
		print("eax",21,8,C_FG_BLACK | C_BG_LIGHT_GREY );
		print_hex(eax,8,29,8,C_FG_WHITE | C_BG_LIGHT_GREY);
		print("ebx",21,10,C_FG_BLACK | C_BG_LIGHT_GREY );
		print_hex(ebx,8,29,10,C_FG_WHITE | C_BG_LIGHT_GREY);
		print("ecx",21,12,C_FG_BLACK | C_BG_LIGHT_GREY );
		print_hex(ecx,8,29,12,C_FG_WHITE | C_BG_LIGHT_GREY);
		print("edx",21,14,C_FG_BLACK | C_BG_LIGHT_GREY );
		print_hex(edx,8,29,14,C_FG_WHITE | C_BG_LIGHT_GREY);
		print("esi",21,16,C_FG_BLACK | C_BG_LIGHT_GREY );
		print_hex(esi,8,29,16,C_FG_WHITE | C_BG_LIGHT_GREY);
		print("edi",21,18,C_FG_BLACK | C_BG_LIGHT_GREY );
		print_hex(edi,8,29,18,C_FG_WHITE | C_BG_LIGHT_GREY);
		print("ebp",21,20,C_FG_BLACK | C_BG_LIGHT_GREY );
		print_hex(ebp,8,29,20,C_FG_WHITE | C_BG_LIGHT_GREY);
		print("esp",21,22,C_FG_BLACK | C_BG_LIGHT_GREY );
		print_hex(esp,8,29,22,C_FG_WHITE | C_BG_LIGHT_GREY);
		print("eip",21,24,C_FG_BLACK | C_BG_LIGHT_GREY );
		print_hex(eip,8,29,24,C_FG_WHITE | C_BG_LIGHT_GREY);
		print("cs",21,26,C_FG_BLACK | C_BG_LIGHT_GREY );
		print_hex(cs,4,29,26,C_FG_WHITE | C_BG_LIGHT_GREY);
		print("ds",21,28,C_FG_BLACK | C_BG_LIGHT_GREY );
		print_hex(ds,4,29,28,C_FG_WHITE | C_BG_LIGHT_GREY);
		print("es",21,30,C_FG_BLACK | C_BG_LIGHT_GREY );
		print_hex(es,4,29,30,C_FG_WHITE | C_BG_LIGHT_GREY);
		print("fs",21,32,C_FG_BLACK | C_BG_LIGHT_GREY );
		print_hex(fs,4,29,32,C_FG_WHITE | C_BG_LIGHT_GREY);
		print("gs",21,34,C_FG_BLACK | C_BG_LIGHT_GREY );
		print_hex(gs,4,29,34,C_FG_WHITE | C_BG_LIGHT_GREY);
		print("ss",21,36,C_FG_BLACK | C_BG_LIGHT_GREY );
		print_hex(ss,4,29,36,C_FG_WHITE | C_BG_LIGHT_GREY);
		print("eflags",21,38,C_FG_BLACK | C_BG_LIGHT_GREY );
		print_hex(eflags,8,29,38,C_FG_WHITE | C_BG_LIGHT_GREY);
		print("cr0",40,8,C_FG_BLACK | C_BG_LIGHT_GREY );
		print_hex(cr0,8,48,8,C_FG_WHITE | C_BG_LIGHT_GREY);
		print("cr2",40,10,C_FG_BLACK | C_BG_LIGHT_GREY );
		print_hex(cr2,8,48,10,C_FG_WHITE | C_BG_LIGHT_GREY);
		print("cr3",40,12,C_FG_BLACK | C_BG_LIGHT_GREY );
		print_hex(cr3,8,48,12,C_FG_WHITE | C_BG_LIGHT_GREY);
		print("cr4",40,14,C_FG_BLACK | C_BG_LIGHT_GREY );
		print_hex(cr4,8,48,14,C_FG_WHITE | C_BG_LIGHT_GREY);
		print("stack",40,24,C_FG_BLACK | C_BG_LIGHT_GREY);
		unsigned int* stack_element = (unsigned int *)esp;
		print_hex(*stack_element,8,48,24,C_FG_WHITE | C_BG_LIGHT_GREY);
		stack_element += 4;
		print_hex(*stack_element,8,48,26,C_FG_WHITE | C_BG_LIGHT_GREY);
		stack_element += 4;
		print_hex(*stack_element,8,48,28,C_FG_WHITE | C_BG_LIGHT_GREY);
		stack_element += 4;
		print_hex(*stack_element,8,48,30,C_FG_WHITE | C_BG_LIGHT_GREY);
		stack_element += 4;
		print_hex(*stack_element,8,48,32,C_FG_WHITE | C_BG_LIGHT_GREY);
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
	muestraInfo = 0;
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
