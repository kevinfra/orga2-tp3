/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCHED_H__
#define __SCHED_H__

#include "screen.h"
#include "tss.h"
#include "gdt.h"

typedef struct str_tupla{
  unsigned short x;
  unsigned short y;
} tupla;

typedef struct str_tarea{
  tupla posicion;
  unsigned short indiceGdt;
  char presente;
  unsigned int cr3Actual;
} tarea;

#define colaJugadorA 1
#define colaJugadorB 2
#define colaNadie 0
tarea jugadores[3][15];
int proximoColaA;
int proximoColaB;
int proximoColaNadie;
short colaActual;
tarea tareaActual;
int siguienteIndiceDeTareaEnCola[3];


unsigned short sched_proximo_indice();
void cargarTareaEnCola(unsigned int dirTareaFisicaTareaOriginal, unsigned int x, unsigned int y, unsigned int posTss, unsigned int cr3);
tupla* posTareaActual();
char esMismaTarea(tarea t1, tarea t2);




#endif	/* !__SCHED_H__ */
