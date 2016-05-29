/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#ifndef __MMU_H__
#define __MMU_H__

#include "defines.h"
#include "i386.h"
#include "tss.h"
#include "game.h"

void mmu_inicializar();
unsigned int mmu_proxima_pagina_fisica_libre();
void mmu_mapear_pagina(unsigned int virtual, unsigned int cr3, unsigned int fisica);
void mmu_inicializar_dir_kernel();
#endif	/* !__MMU_H__ */
