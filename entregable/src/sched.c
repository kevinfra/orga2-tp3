/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "sched.h"
#define idle 0x48 //pos en gdt de idle. Esto sale de inicializar tss

tarea colaJugadorA[5];
tarea colaJugadorB[5];
tarea colaNadie[15];
int proximoColaA;
int finColaA;
int proximoColaB;
int finColaB;
int proximoColaNadie;
int finColaNadie;
short colaActual;
tarea tareaActual;

unsigned short sched_proximo_indice() {
  unsigned short res = 0;
  switch (colaActual) {
    case 0:
      res = colaNadie[proximoColaNadie].indiceGdt;
      colaActual++;
      tareaActual = colaNadie[proximoColaNadie];
      break;
    case 1:
      res = colaJugadorA[proximoColaA].indiceGdt;
      colaActual++;
      tareaActual = colaNadie[proximoColaNadie];
      break;
    case 2:
      res = colaJugadorB[proximoColaB].indiceGdt;
      colaActual = 0;
      tareaActual = colaNadie[proximoColaNadie];
      break;
  }
  if (res == 0) {
    res = idle;
  }
  return (res << 3);
}

tupla* posTareaActual(){
  return &(tareaActual.posicion);
}

void cargarTareaEnCola(unsigned int dirTareaFisicaTareaOriginal, unsigned int x, unsigned int y, unsigned int posTss){
  switch (dirTareaFisicaTareaOriginal) {
    case 0x11000:
      colaJugadorA[proximoColaA].posicion.x = x;
      colaJugadorA[proximoColaA].posicion.y = y;
      colaJugadorA[proximoColaA].indiceGdt = posTss;
      break;
    case 0x12000:
      colaJugadorB[proximoColaB].posicion.x = x;
      colaJugadorB[proximoColaB].posicion.y = y;
      colaJugadorB[proximoColaB].indiceGdt = posTss;
      break;
    case 0x13000:
      colaNadie[proximoColaNadie].posicion.x = x;
      colaNadie[proximoColaNadie].posicion.y = y;
      colaNadie[proximoColaNadie].indiceGdt = posTss;
      break;
    }
}

void inicializar_scheduler(){
  proximoColaA = 0;
  finColaA = 0;
  proximoColaB = 0;
  finColaB = 0;
  proximoColaNadie = 0;
  colaActual = 0;
  short x = 0;
  short y = 0;
  unsigned short posGdtIdle = 0x48;
  tarea tareaIdle;
  tareaIdle.posicion.x = x;
  tareaIdle.posicion.y = y;
  tareaIdle.indiceGdt = posGdtIdle;

  tareaActual= tareaIdle; //idle
}
