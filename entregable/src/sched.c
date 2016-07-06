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
  tarea * tareaVieja = tareaActual;
  int siguienteTarea;
  int siguienteTareaOriginal = siguienteIndiceDeTareaEnCola[colaActual];
  int i = 0;
  while (esMismaTarea(tareaVieja, tareaActual)) {
    if(i < 46){ //ASSERT NO DA LA VUELTA
      siguienteTarea = siguienteIndiceDeTareaEnCola[colaActual]; //esto da una posicon del arreglo de colaActual
      if(jugadores[colaActual][siguienteTarea].presente){ //Me fijo si esta presente
        res = jugadores[colaActual][siguienteTarea].indiceGdt;
        tareaActual = &jugadores[colaActual][siguienteTarea]; //cambio la tarea actual
        siguienteIndiceDeTareaEnCola[colaActual] = (siguienteIndiceDeTareaEnCola[colaActual] + 1) % 15; //avanzo los iteradores de arreglos
        colaActual = (colaActual + 1) % 3;
      }else{
        siguienteIndiceDeTareaEnCola[colaActual] = (siguienteIndiceDeTareaEnCola[colaActual] + 1) % 15;
        if(siguienteTareaOriginal == siguienteIndiceDeTareaEnCola[colaActual]){
          colaActual = (colaActual + 1) % 3;
          siguienteTareaOriginal = siguienteIndiceDeTareaEnCola[colaActual];
        }
      }
      i++;
    }else{
      while(1){ print("JUEGO TERMINADO", 20, 20, (C_BG_RED | C_FG_LIGHT_GREY)); }
    }
  }
  return res;
}

char esMismaTarea(tarea* t1, tarea* t2){
  return ((t1->indiceGdt == t2->indiceGdt) && (t1->cr3Actual == t2->cr3Actual));
}

tupla* posTareaActual(){
  return &(tareaActual->posicion);
}


int proximoALibre(){
  int res = (proximoColaA + 1) % 5;
  int q = 0;
  while(jugadores[colaJugadorA][res].presente){
    if(q < 16){
      int k = 0;
      for(k = 0; k < 5; k++){
        if(!jugadores[colaJugadorA][k].presente){
          res = k;
          k = 6;
        }
      }
      q++;
    }else{
      print("dio la vuelta en proximo libre cola A", 20, 20, (C_BG_RED | C_FG_LIGHT_GREY));
    }
  }
  return res;
}

int proximoBLibre(){
  int k = 0;
  int res = (proximoColaB + 1) % 5;
  for(k=0; k < 5; k++){
    if(!jugadores[colaJugadorB][k].presente){ res = k; k = 5;}
  }
  return res;
}

int proximoHLibre(){
  int k = 0;
  int res = (proximoColaNadie + 1) % 15;
  for(k=0; k < 15; k++){
    if(!jugadores[colaNadie][k].presente){ res = k; k = 16;}
  }
  return res;
}

void cargarTareaEnCola(unsigned int dirTareaFisicaTareaOriginal, unsigned int x, unsigned int y, unsigned int posTss, unsigned int cr3){
  switch (dirTareaFisicaTareaOriginal) {
    case 0x11000:
      proximoColaA = proximoALibre();
      if(!jugadores[colaJugadorA][proximoColaA].presente){
        jugadores[colaJugadorA][proximoColaA].posicion.x = x;
        jugadores[colaJugadorA][proximoColaA].posicion.y = y;
        jugadores[colaJugadorA][proximoColaA].posicionOriginal.x = x;
        jugadores[colaJugadorA][proximoColaA].posicionOriginal.y = y;
        jugadores[colaJugadorA][proximoColaA].indiceGdt = posTss;
        jugadores[colaJugadorA][proximoColaA].presente = 1;
        jugadores[colaJugadorA][proximoColaA].cr3Actual = cr3;
        jugadores[colaJugadorA][proximoColaA].dueno = 0;
        jugadores[colaJugadorA][proximoColaA].duenoOriginal = 0;
        jugadores[colaJugadorA][proximoColaA].posReloj = 3;
        jugadores[colaJugadorA][proximoColaA].relojPropioX = (proximoColaA + 2);
        proximoColaA = proximoALibre();
      }else{
        while(1){ print("proximoColaA no valido en cargarTarea", 20, 20, (C_BG_RED | C_FG_LIGHT_GREY)); }
      }
      break;
    case 0x12000:
      proximoColaB = proximoBLibre();
      if(!jugadores[colaJugadorB][proximoColaB].presente){
        jugadores[colaJugadorB][proximoColaB].posicion.x = x;
        jugadores[colaJugadorB][proximoColaB].posicion.y = y;
        jugadores[colaJugadorB][proximoColaB].posicionOriginal.x = x;
        jugadores[colaJugadorB][proximoColaB].posicionOriginal.y = y;
        jugadores[colaJugadorB][proximoColaB].indiceGdt = posTss;
        jugadores[colaJugadorB][proximoColaB].presente = 1;
        jugadores[colaJugadorB][proximoColaB].cr3Actual = cr3;
        jugadores[colaJugadorB][proximoColaB].dueno = 1;
        jugadores[colaJugadorB][proximoColaB].duenoOriginal = 1;
        jugadores[colaJugadorB][proximoColaB].posReloj = 3;
        proximoColaB = proximoBLibre();
        jugadores[colaJugadorB][proximoColaB].relojPropioX = (proximoColaB + 2);
      }else{
        while(1){ print("proximoColaB no valido en cargarTarea", 20, 20, (C_BG_RED | C_FG_LIGHT_GREY)); }
      }
      break;
    case 0x13000:
      proximoColaNadie = proximoHLibre();
      if(!jugadores[colaNadie][proximoColaNadie].presente){
        jugadores[colaNadie][proximoColaNadie].posicion.x = x;
        jugadores[colaNadie][proximoColaNadie].posicion.y = y;
        jugadores[colaNadie][proximoColaNadie].posicionOriginal.x = x;
        jugadores[colaNadie][proximoColaNadie].posicionOriginal.y = y;
        jugadores[colaNadie][proximoColaNadie].indiceGdt = posTss;
        jugadores[colaNadie][proximoColaNadie].presente = 1;
        jugadores[colaNadie][proximoColaNadie].cr3Actual = cr3;
        jugadores[colaNadie][proximoColaNadie].dueno = 2;
        jugadores[colaNadie][proximoColaNadie].duenoOriginal = 2;
        jugadores[colaNadie][proximoColaNadie].posReloj = 3;
        proximoColaNadie = proximoHLibre();
        jugadores[colaNadie][proximoColaNadie].relojPropioX = (proximoColaNadie + 2);
      }else{
        while(1){ print("proximoColaNadie no valido en cargarTarea", 20, 20, (C_BG_RED | C_FG_LIGHT_GREY)); }
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
  tareaActual = &tareaIdle; //idle
  breakpoint();
}
