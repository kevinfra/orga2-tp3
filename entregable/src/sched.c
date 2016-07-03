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
  tarea tareaVieja = tareaActual;
  int siguienteTarea;
  int siguienteTareaOriginal = siguienteTareaEnCola[colaActual];
  while (esMismaTarea(tareaVieja, tareaActual)) {
    siguienteTarea = siguienteTareaEnCola[colaActual];
    if(jugadores[colaActual][siguienteTarea].presente){
      res = jugadores[colaActual][siguienteTarea].indiceGdt;
      tareaActual = jugadores[colaActual][siguienteTarea];
      siguienteTareaEnCola[colaActual] = (siguienteTareaEnCola[colaActual] + 1) % 15;
      colaActual = (colaActual + 1) % 3;
    }else{
      siguienteTareaEnCola[colaActual] = (siguienteTareaEnCola[colaActual] + 1) % 15;
      if(siguienteTareaOriginal == siguienteTareaEnCola[colaActual]){
        colaActual = (colaActual + 1) % 3;
        siguienteTareaOriginal = siguienteTareaEnCola[colaActual];
      }
    }
  }
  // switch (colaActual) {
  //   case 0:
  //     for(i = 0; i < 15; i++){
  //       breakpoint();
  //       if(colaNadie[siguienteTareaNadie].presente && !esMismaTarea(colaNadie[siguienteTareaNadie], tareaActual)){
  //         res = colaNadie[siguienteTareaNadie].indiceGdt;
  //         colaActual++;
  //         tareaActual = colaNadie[siguienteTareaNadie];
  //         siguienteTareaNadie = (siguienteTareaNadie + 1) % 15;
  //         i = 16;
  //       }else{
  //         siguienteTareaNadie = (siguienteTareaNadie + 1) % 15;
  //       }
  //     }
  //     if(i == 15){
  //       colaActual++;
  //       short colaActualVieja = colaActual;
  //       res = sched_proximo_indice();
  //       if(colaActual != colaActualVieja){colaActual = colaActualVieja;}
  //     }
  //     break;
  //   case 1:
  //     for(i = 0; i < 5; i++){
  //       if(colaJugadorA[siguienteTareaA].presente && !esMismaTarea(colaJugadorA[siguienteTareaA], tareaActual)){
  //         res = colaJugadorA[siguienteTareaA].indiceGdt;
  //         colaActual++;
  //         tareaActual = colaJugadorA[siguienteTareaA];
  //         siguienteTareaA = (siguienteTareaA + 1) % 5;
  //         i = 6;
  //       }else{
  //         siguienteTareaA = (siguienteTareaA + 1) % 5;
  //       }
  //     }
  //     if(i == 5){
  //       colaActual++;
  //       short colaActualVieja = colaActual;
  //       res = sched_proximo_indice();
  //       if(colaActual != colaActualVieja){colaActual = colaActualVieja;}
  //     }
  //     break;
  //   case 2:
  //     for(i = 0; i < 5; i++){
  //       if(colaJugadorB[siguienteTareaB].presente && !esMismaTarea(colaJugadorB[siguienteTareaB], tareaActual)){
  //         res = colaJugadorB[siguienteTareaB].indiceGdt;
  //         colaActual = 0;
  //         tareaActual = colaJugadorB[siguienteTareaB];
  //         siguienteTareaB = (siguienteTareaB + 1) % 5;
  //         i = 6;
  //       }else{
  //         siguienteTareaB = (siguienteTareaB + 1) % 5;
  //       }
  //     }
  //     if(i == 5){
  //       colaActual = 0;
  //       short colaActualVieja = colaActual;
  //       res = sched_proximo_indice();
  //       if(colaActual != colaActualVieja){colaActual = colaActualVieja;}
  //     }
  //     break;
  // }
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

void inicializar_scheduler(){
  proximoColaA = 0;
  proximoColaB = 0;
  proximoColaNadie = 0;
  siguienteTareaA = 0;
  siguienteTareaB = 0;
  siguienteTareaNadie = 0;
  siguienteTareaEnCola[0] = 0;
  siguienteTareaEnCola[1] = 0;
  siguienteTareaEnCola[2] = 0;
  colaActual = colaNadie;
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
