/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/

#include "tss.h"
#include "gdt.h"
#include "i386.h"

tss tss_inicial;
tss tss_idle;
tss tss_h1:
tss tss_h2:
tss tss_h3:
tss tss_h4:
tss tss_h5:
tss tss_h6:
tss tss_h7:
tss tss_h8:
tss tss_h9:
tss tss_h10:
tss tss_h11:
tss tss_h12:
tss tss_h13:
tss tss_h14:
tss tss_h15:
tss tss_a1;
tss tss_a2;
tss tss_a3;
tss tss_a4;
tss tss_a5;
tss tss_b1;
tss tss_b2;
tss tss_b3;
tss tss_b4;
tss tss_b5;

unsigned int tss_inicializar_idle() {
    //aca se inicializa la tarea idle
    tss_idle.esp0 = 0x27000;
    tss_idle.ss0 = 0x30;
    tss_idle.cr3 = rcr3();
    tss_idle.eip = 0x00010000;
    tss_idle.eflags = 0x202;
    tss_idle.esp = 0x27000;
    tss_idle.ebp = 0x27000;
    tss_idle.es = 0x30;
    tss_idle.cs = 0x20;
    tss_idle.ss = 0x30;
    tss_idle.ds = 0x30;
    tss_idle.fs = 0x30;
    tss_idle.gs = 0x30;

//la tarea inicial no se levanta porque empieza todo en 0.

    inicializar_proximoSlotLibre();
    unsigned int slot_libre = proximoSlotLibre();
    unsigned int res = slot_libre;
    gdt[slot_libre].limit_0_15 = sizeof(tss_inicial)-1; //tamano tss
    gdt[slot_libre].base_0_15 =  (unsigned short) ((unsigned int)(&tss_inicial) & 0x0000ffff);
    gdt[slot_libre].base_23_16 = (unsigned int) (&tss_inicial) >> 16;
    gdt[slot_libre].type = 9; // 1001 en binario --not busy
    gdt[slot_libre].s = 0;
    gdt[slot_libre].dpl = 0;
    gdt[slot_libre].p = 1;
    gdt[slot_libre].limit_16_19 = 0;
    gdt[slot_libre].avl = 0;
    gdt[slot_libre].l = 0;
    gdt[slot_libre].db = 0;
    gdt[slot_libre].g = 0;
    gdt[slot_libre].base_31_24 = (unsigned char) ((unsigned int) (&tss_inicial)) >> 24;

    slot_libre = proximoSlotLibre();
    gdt[slot_libre].limit_0_15 = sizeof(tss_idle)-1; //tamano tss
    gdt[slot_libre].base_0_15 = (unsigned short) ((unsigned int) (&tss_idle) & 0x0000ffff);
    gdt[slot_libre].base_23_16 = (unsigned short) ((unsigned int) (&tss_idle)) >> 16;
    gdt[slot_libre].type = 9; // 1001 en binario --not busy
    gdt[slot_libre].s = 0;
    gdt[slot_libre].dpl = 0;
    gdt[slot_libre].p = 1;
    gdt[slot_libre].limit_16_19 = 0;
    gdt[slot_libre].avl = 0;
    gdt[slot_libre].l = 0;
    gdt[slot_libre].db = 0;
    gdt[slot_libre].g = 0;
    gdt[slot_libre].base_31_24 = (unsigned char) ((unsigned int) (&tss_idle)) >> 24;

    return res*8;
}

unsigned int inicializat_tss(unsigned int dirTareaFisicaTareaOriginal, unsigned int x, unsigned int y){ //PREGUNTAR SOBRE COMO SE MANEJAN LAS DISTINTAS TAREAS, ES DECIR, SI PUEDE HABER REPARTIDAS ENTRE 0X11000 Y 0X26000.
  //ADEMAS, HAY QUE PREGUNTAR COMO SE DÓNDE VA A ESTAR CADA TAREA

  unsigned int dirFisicaACopiar = (x + y*80)*4096 + 400000;
  unsigned int nueva_tss = proximoSlotLibre();
  unsigned int res = nueva_tss;
  switch (dirTareaFisicaTareaOriginal) {
    case 0x11000:
      break;
    case 0x12000:
      nueva_tss += 5;
      break;
    case 0x12000:
      nueva_tss += 10;
      break;
  }
    gdt[nueva_tss].limit_0_15 = sizeof(tss_h1)-1; //tamano tss
    gdt[nueva_tss].base_0_15 = (unsigned short) ((unsigned int) (&posTarea) & 0x0000ffff);
    gdt[nueva_tss].base_23_16 = (unsigned short) ((unsigned int) (&posTarea)) >> 16;
    gdt[nueva_tss].type = 9; // 1001 en binario --not busy
    gdt[nueva_tss].s = 1;
    gdt[nueva_tss].dpl = 0;
    gdt[nueva_tss].p = 1;
    gdt[nueva_tss].limit_16_19 = (unsigned char) ((unsigned int) (posTarea + 4095) >> 16);
    gdt[nueva_tss].avl = 0;
    gdt[nueva_tss].l = 0;
    gdt[nueva_tss].db = 0;
    gdt[nueva_tss].g = 0;
    gdt[nueva_tss].base_31_24 = (unsigned char) ((unsigned int) (&posTarea)) >> 24;



    return res;
}
