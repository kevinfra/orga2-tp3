/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "sched.h"
#include "i386.h"
#define idle 0x50 //pos en gdt de idle. Esto sale de inicializar tss

unsigned short sched_proximo_indice() {
  unsigned short res = 0;
  tarea tareaVieja = tareaActual;
  int siguienteTarea;
  int siguienteTareaOriginal = siguienteIndiceDeTareaEnCola[colaActual];
  while (esMismaTarea(tareaVieja, tareaActual)) {
    siguienteTarea = siguienteIndiceDeTareaEnCola[colaActual]; //esto da una posicon del arreglo de colaActual
    if(jugadores[colaActual][siguienteTarea].presente){ //Me fijo si esta presente
      res = jugadores[colaActual][siguienteTarea].indiceGdt;
      tareaActual = jugadores[colaActual][siguienteTarea]; //cambio la tarea actual
      siguienteIndiceDeTareaEnCola[colaActual] = (siguienteIndiceDeTareaEnCola[colaActual] + 1) % 15; //avanzo los iteradores de arreglos
      colaActual = (colaActual + 1) % 3;
    }else{
      siguienteIndiceDeTareaEnCola[colaActual] = (siguienteIndiceDeTareaEnCola[colaActual] + 1) % 15;
      if(siguienteTareaOriginal == siguienteIndiceDeTareaEnCola[colaActual]){
        colaActual = (colaActual + 1) % 3;
        siguienteTareaOriginal = siguienteIndiceDeTareaEnCola[colaActual];
      }
    }
  }
  return res;
}

char esMismaTarea(tarea t1, tarea t2){
  return ((t1.indiceGdt == t2.indiceGdt) && (t1.cr3Actual == t2.cr3Actual));
}

tupla* posTareaActual(){
  return &(tareaActual.posicion);
}

void cargarTareaEnCola(unsigned int dirTareaFisicaTareaOriginal, unsigned int x, unsigned int y, unsigned int posTss, unsigned int cr3){
  int i;
  switch (dirTareaFisicaTareaOriginal) {
    case 0x11000:
      for(i = 0; i < 5; i++){
        if(!jugadores[colaJugadorA][proximoColaA].presente){
          jugadores[colaJugadorA][proximoColaA].posicion.x = x;
          jugadores[colaJugadorA][proximoColaA].posicion.y = y;
          jugadores[colaJugadorA][proximoColaA].indiceGdt = posTss;
          jugadores[colaJugadorA][proximoColaA].presente = 1;
          jugadores[colaJugadorA][proximoColaA].cr3Actual = cr3;
          i = 6;
        }else{
          proximoColaA = (proximoColaA + 1) % 5;
        }
      }
      break;
    case 0x12000:
      for(i = 0; i < 5; i++){
        if(!jugadores[colaJugadorB][proximoColaB].presente){
          jugadores[colaJugadorB][proximoColaB].posicion.x = x;
          jugadores[colaJugadorB][proximoColaB].posicion.y = y;
          jugadores[colaJugadorB][proximoColaB].indiceGdt = posTss;
          jugadores[colaJugadorB][proximoColaB].presente = 1;
          jugadores[colaJugadorB][proximoColaB].cr3Actual = cr3;
          i = 6;
        }else{
          proximoColaB = (proximoColaB + 1) % 5;
        }
      }
      break;
    case 0x13000:
      for(i = 0; i < 15; i++){
        if(!jugadores[colaNadie][proximoColaNadie].presente){
          jugadores[colaNadie][proximoColaNadie].posicion.x = x;
          jugadores[colaNadie][proximoColaNadie].posicion.y = y;
          jugadores[colaNadie][proximoColaNadie].indiceGdt = posTss;
          jugadores[colaNadie][proximoColaNadie].presente = 1;
          jugadores[colaNadie][proximoColaNadie].cr3Actual = cr3;
          i = 15;
        }else{
          proximoColaNadie = (proximoColaNadie + 1) % 15;
        }
      }
      break;
    }
}

tarea tareaIdle;
void inicializar_scheduler(){
  proximoColaA = 0;
  proximoColaB = 0;
  proximoColaNadie = 0;
  siguienteIndiceDeTareaEnCola[0] = 0;
  siguienteIndiceDeTareaEnCola[1] = 0;
  siguienteIndiceDeTareaEnCola[2] = 0;
  colaActual = colaNadie;
  short x = 0;
  short y = 0;
  unsigned short posGdtIdle = idle;
  tareaIdle.posicion.x = x;
  tareaIdle.posicion.y = y;
  tareaIdle.indiceGdt = posGdtIdle;
  tareaIdle.presente = 1;
  tareaActual= tareaIdle; //idle
}
