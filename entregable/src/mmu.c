/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"

unsigned int proxima_pagina_libre;

void mmu_inicializar() {
  proxima_pagina_libre = INICIO_PAGINAS_LIBRES;
}

unsigned int mmu_proxima_pagina_fisica_libre() {
  unsigned int pagina_libre = proxima_pagina_libre;
  proxima_pagina_libre += PAGE_SIZE;
  return pagina_libre;
}

void mmu_mapear_pagina(unsigned int virtual, unsigned int cr3, unsigned int fisica){
  
}


void mmu_inicializar_dir_kernel(){
  unsigned int * pageTable = (unsigned int *) 0x28000;
  unsigned int * tableDeDirecciones = (unsigned int *) 0x27000;
  *tableDeDirecciones = (unsigned int) pageTable | 3;
  tableDeDirecciones++;
  for(int i = 1; i < 1024; i++){
    *tableDeDirecciones = 0;
    tableDeDirecciones++;
  }

  for(int j = 0; j < 1024; j++){
    *pageTable = j*4096 | 3;
    pageTable++;
  }
}
