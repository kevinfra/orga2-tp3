/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/

#include "tss.h"
#include "gdt.h"
#include "i386.h"
#include "mmu.h"
#include "sched.h"
#include "game.h"

tss tss_inicial;
tss tss_idle;
tss tss_h1;
tss tss_h2;
tss tss_h3;
tss tss_h4;
tss tss_h5;
tss tss_h6;
tss tss_h7;
tss tss_h8;
tss tss_h9;
tss tss_h10;
tss tss_h11;
tss tss_h12;
tss tss_h13;
tss tss_h14;
tss tss_h15;
tss tss_a1;
tss tss_a2;
tss tss_a3;
tss tss_a4;
tss tss_a5;
tss tss_a6;
tss tss_a7;
tss tss_a8;
tss tss_a9;
tss tss_a10;
tss tss_a11;
tss tss_a12;
tss tss_a13;
tss tss_a14;
tss tss_a15;
tss tss_a16;
tss tss_a17;
tss tss_a18;
tss tss_a19;
tss tss_a20;
tss tss_b1;
tss tss_b2;
tss tss_b3;
tss tss_b4;
tss tss_b5;
tss tss_b6;
tss tss_b7;
tss tss_b8;
tss tss_b9;
tss tss_b10;
tss tss_b11;
tss tss_b12;
tss tss_b13;
tss tss_b14;
tss tss_b15;
tss tss_b16;
tss tss_b17;
tss tss_b18;
tss tss_b19;
tss tss_b20;

tss* todasLasTss[55] = { &tss_a1, &tss_a2, &tss_a3, &tss_a4, &tss_a5,
   &tss_a6, &tss_a7, &tss_a8, &tss_a9, &tss_a10,
   &tss_a11, &tss_a12, &tss_a13, &tss_a14, &tss_a15,
   &tss_a16, &tss_a17, &tss_a18, &tss_a19, &tss_a20,
   &tss_b1, &tss_b2, &tss_b3, &tss_b4, &tss_b5,
   &tss_b6, &tss_b7, &tss_b8, &tss_b9, &tss_b10,
   &tss_b11, &tss_b12, &tss_b13, &tss_b14, &tss_b15,
   &tss_b16, &tss_b17, &tss_b18, &tss_b19, &tss_b20,
   &tss_h1, &tss_h2, &tss_h3, &tss_h4, &tss_h5, &tss_h6, &tss_h7, &tss_h8, &tss_h9,
   &tss_h10, &tss_h11, &tss_h12, &tss_h13, &tss_h14, &tss_h15};
unsigned short proximaTss;
tss* dameTss(){
  tss* res = todasLasTss[proximaTss];
  proximaTss++;
  return res;
}

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
    gdt[slot_libre].limit_16_19 = (unsigned char) ((unsigned int) (sizeof(tss_idle)-1) >> 16);
    gdt[slot_libre].avl = 0;
    gdt[slot_libre].l = 0;
    gdt[slot_libre].db = 0;
    gdt[slot_libre].g = 0;
    gdt[slot_libre].base_31_24 = (unsigned char) ((unsigned int) (&tss_idle)) >> 24;

    proximaTss = 0;

    return res*8;
}

unsigned int inicializar_tss(unsigned int dirFisicaTareaOriginal, unsigned int x, unsigned int y){ //PREGUNTAR SOBRE COMO SE MANEJAN LAS DISTINTAS TAREAS, ES DECIR, SI PUEDE HABER REPARTIDAS ENTRE 0X11000 Y 0X26000.

    unsigned int posTss = proximoSlotLibre();
    unsigned int res = posTss;
    unsigned int cr3 = rcr3();

    tss* nueva_tss = dameTss();
    gdt[posTss].limit_0_15 = sizeof(tss_h1)-1; //tamano tss
    gdt[posTss].base_0_15 = (unsigned short) ((unsigned int) (nueva_tss) & 0x0000ffff);
    gdt[posTss].base_23_16 = (unsigned short) ((unsigned int) (nueva_tss)) >> 16;
    gdt[posTss].type = 9; // 1001 en binario --not busy
    gdt[posTss].s = 0;
    gdt[posTss].dpl = 3;
    gdt[posTss].p = 1;
    gdt[posTss].limit_16_19 = (unsigned char) ((unsigned int) (sizeof(tss_h1)-1) >> 16);
    gdt[posTss].avl = 0;
    gdt[posTss].l = 0;
    gdt[posTss].db = 1;
    gdt[posTss].g = 0;
    gdt[posTss].base_31_24 = (unsigned char) ((unsigned int) (nueva_tss)) >> 24;

    nueva_tss->cs = GDT_OFF_IDX_DESC_CODE3 + 3;
    nueva_tss->es = GDT_OFF_IDX_DESC_DATA3 + 3;
    nueva_tss->ss = GDT_OFF_IDX_DESC_DATA3 + 3;
    nueva_tss->ds = GDT_OFF_IDX_DESC_DATA3 + 3;
    nueva_tss->fs = GDT_OFF_IDX_DESC_DATA3 + 3;
    nueva_tss->gs = GDT_OFF_IDX_DESC_DATA3 + 3;
    nueva_tss->esp = 0x08000000 + 0xfff;
    nueva_tss->ebp = 0x08000000 + 0xfff;
    nueva_tss->eflags = 0x202;
    nueva_tss->eip = 0x08000000;
    unsigned int nuevaCR3 = mmu_inicializar_dir_tarea(cr3, dirFisicaTareaOriginal, x, y);
    nueva_tss->cr3 = nuevaCR3;
    nueva_tss->esp0 = mmu_proxima_pagina_fisica_libre();
    nueva_tss->ss0 = GDT_OFF_IDX_DESC_DATA0;
    nueva_tss->iomap = 0xFFFF;

    cargarTareaEnCola(dirFisicaTareaOriginal, x, y, posTss, nuevaCR3);

    return res;
}

void tss_inicializar_tareas_h(){
  unsigned int i = 0;
  for(i = 0; i < 15; i++){
    inicializar_tss(0x13000, i, i);
    pintarTarea(i+i+1, i+1, 2);
  }
}
