/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "sched.h"
#define idle 0x48 //pos en gdt de idle. Esto sale de inicializar tss

unsigned short sched_proximo_indice() {
  int res = 0;
  switch (colaActual) {
    case 0:
      res = colaNadie[proximoColaNadie];
      colaActual++;
      break;
    case 1:
      res = colaJugadorA[proximoColaA];
      colaActual++;
      break;
    case 2:
      res = colaJugadorB[proximoColaB];
      colaActual = 0;
      break;
  }
  if (res == 0) {
    res = idle;
  }
  return res;
}

int quantum;
unsigned short[5] colaJugadorA;
unsigned short[5] colaJugadorB;
unsigned short[15] colaNadie;
int proximoColaA;
int finColaA;
int proximoColaB;
int finColaB;
int proximoColaNadie;
int finColaNadie;
short colaActual;
int tareaActual;

typedef struct str_tupla{
  unsigned short x;
  unsigned short y;
} tupla;

tupla posicionesTareas[25];
unsigned short tareaActual(posTarea){
  return posicionesTareas[posTarea-10];
}


void inicializar_scheduler(){
  proximoColaA = 0;
  finColaA = 0;
  proximoColaB = 0;
  finColaB = 0;
  proximoColaNadie = 0;
  colaActual = 0;
  tareaActual= 0x48; //idle
}
