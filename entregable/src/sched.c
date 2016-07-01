/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "sched.h"
#include "i386.h"
#define idle 0x48 //pos en gdt de idle. Esto sale de inicializar tss

unsigned short sched_proximo_indice() {
  unsigned short res = 0;
  int i;
  switch (colaActual) {
    case 0:
      for(i = 0; i < 15; i++){
        if(colaNadie[proximoColaNadie].presente){
          res = colaNadie[proximoColaNadie].indiceGdt;
          colaActual++;
          tareaActual = colaNadie[proximoColaNadie];
          proximoColaNadie = (proximoColaNadie + 1) % 15;
          break;
        }
        proximoColaNadie = (proximoColaNadie + 1) % 15;
      }
      if(i == 15){
        colaActual++;
        res = sched_proximo_indice();
      }
      break;
    case 1:
      for(i = 0; i < 5; i++){
        if(colaJugadorA[proximoColaA].presente){
          res = colaJugadorA[proximoColaA].indiceGdt;
          colaActual++;
          tareaActual = colaJugadorA[proximoColaA];
          proximoColaA = (proximoColaA + 1) % 5;
          break;
        }
        proximoColaA = (proximoColaA + 1) % 5;
      }
      if(i == 5){
        colaActual++;
        res = sched_proximo_indice();
      }
      break;
    case 2:
      for(i = 0; i < 5; i++){
        if(colaJugadorB[proximoColaB].presente){
          res = colaJugadorB[proximoColaB].indiceGdt;
          colaActual = 0;
          tareaActual = colaJugadorB[proximoColaB];
          proximoColaB = (proximoColaB + 1) % 5;
          break;
        }
        proximoColaB = (proximoColaB + 1) % 5;
      }
      if(i == 5){
        colaActual = 0;
        res = sched_proximo_indice();
      }
      break;
  }
  return res;
}

char esMismaTarea(tarea t1, tarea t2){
  return ((t1.posicion.x == t2.posicion.x) && (t1.posicion.y == t2.posicion.y) && (t1.indiceGdt == t2.indiceGdt));
}

tupla* posTareaActual(){
  return &(tareaActual.posicion);
}

void cargarTareaEnCola(unsigned int dirTareaFisicaTareaOriginal, unsigned int x, unsigned int y, unsigned int posTss, unsigned int cr3){
  switch (dirTareaFisicaTareaOriginal) {
    case 0x11000:
      colaJugadorA[proximoColaA].posicion.x = x;
      colaJugadorA[proximoColaA].posicion.y = y;
      colaJugadorA[proximoColaA].indiceGdt = posTss;
      colaJugadorA[proximoColaA].presente = 1;
      colaJugadorA[proximoColaA].cr3Actual = cr3;
      proximoColaA++;
      break;
    case 0x12000:
      colaJugadorB[proximoColaB].posicion.x = x;
      colaJugadorB[proximoColaB].posicion.y = y;
      colaJugadorB[proximoColaB].indiceGdt = posTss;
      colaJugadorB[proximoColaB].presente = 1;
      colaJugadorB[proximoColaB].cr3Actual = cr3;
      proximoColaB++;
      break;
    case 0x13000:
      colaNadie[proximoColaNadie].posicion.x = x;
      colaNadie[proximoColaNadie].posicion.y = y;
      colaNadie[proximoColaNadie].indiceGdt = posTss;
      colaNadie[proximoColaNadie].presente = 1;
      colaNadie[proximoColaNadie].cr3Actual = cr3;
      proximoColaNadie++;
      break;
    }
}

void inicializar_scheduler(){
  proximoColaA = 0;
  proximoColaB = 0;
  proximoColaNadie = 0;
  colaActual = 0;
  short x = 0;
  short y = 0;
  unsigned short posGdtIdle = 0x48;
  tarea tareaIdle;
  tareaIdle.posicion.x = x;
  tareaIdle.posicion.y = y;
  tareaIdle.indiceGdt = posGdtIdle;
  tareaIdle.presente = 1;
  tareaActual= tareaIdle; //idle
}
