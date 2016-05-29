/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"
#define PDE_INDEX(virtual) (virtual >> 22)
#define PTE_INDEX(virtual) ((virtual & 0x003FF000) >> 12)
#define ALIGN(dir) ???
#define PG_READ_WRITE ???
#define PG_USER ???
#define PG_PRESENT 0x00000001

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
//    1 Descomponer la direcci´on virtual en Indice de
//          Directorio e Indice de Tabla.
    unsigned int directoryIndex = virtual; //PdE
    unsigned int tableIndex = virtual; //PtE
    unsigned int directoryOffset = PDE_INDEX(directoryIndex);
    unsigned int tableOffset = PTE_INDEX(tableIndex);
//    2 Obtener el PDE correspondiente al esquema de
//          paginaci´on cr3 y el Indice de Directorio, si no es valido,
//          inicializar una nueva tabla de paginas.
    unsigned int direccion_directorio_paginas = cr3 >> 12;
    directoryIndex = directoryOffset + direccion_directorio_paginas * 4;
    if(!( *directoryIndex) & 1){
      *directoryIndex = mmu_proxima_pagina_fisica_libre() & 0xFFFFF003;
    }
    unsigned int pde = (*directoryIndex) & 0xFFFFF000;

//    3 Obtener el PTE correspondiente al esquema de paginaci´on
//          cr3 y el Indice de Tabla.
//    4 Completar la PTE seg´un corresponda para mapear la
//          direccion fisica.
    unsigned int pte = (*(pde + tableOffset * 4)) & 0xFFFFF003;

//    5 Ejecutar tlbflush() para invalidar la cache de
//          traducciones.
    tlbflush();
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
