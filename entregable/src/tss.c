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

void tss_inicializar() {
    //aca se inicializa la tarea idle
    tss_idle.esp0 = 0x27000;
    tss_idle.ss0 = 0x30;
    tss_idle.cr3 = rcr3(); //MAIAMEE
    tss_idle.eip = 0x00010000;
    tss_idle.eflags = 0x202;
    tss_idle.esp = 0x27000;
    tss_idle.ebp = 0x27000;
    tss_idle.es = 0x30;
    tss_idle.cs = 0x30;
    tss_idle.ss = 0x30;
    tss_idle.ds = 0x30;
    tss_idle.fs = 0x30;
    tss_idle.gs = 0x30;

//la tarea inicial no se levanta porque empieza todo en 0.

    inicializar_proximoSlotLibre();
    unsigned int slot_libre = proximoSlotLibre();
    gdt[slot_libre].limit_0_15 = 832; //tamano tss
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
    gdt[slot_libre].limit_0_15 = 832; //tamano tss
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

}

void completar_tss(char tipoDeTarea){
    unsigned int nueva_tss = proximoSlotLibre();
    gdt[nueva_tss].limit_0_15 = 832; //tamano tss
    gdt[nueva_tss].base_0_15 = (unsigned short) ((unsigned int) (&tss_idle) & 0x0000ffff);
    gdt[nueva_tss].base_23_16 = (unsigned short) ((unsigned int) (&tss_idle)) >> 16;
    gdt[nueva_tss].type = 9; // 1001 en binario --not busy
    gdt[nueva_tss].s = 0;
    gdt[nueva_tss].dpl = 0;
    gdt[nueva_tss].p = 1;
    gdt[nueva_tss].limit_16_19 = 0;
    gdt[nueva_tss].avl = 0;
    gdt[nueva_tss].l = 0;
    gdt[nueva_tss].db = 0;
    gdt[nueva_tss].g = 0;
    gdt[nueva_tss].base_31_24 = (unsigned char) ((unsigned int) (&tss_idle)) >> 24;

}
