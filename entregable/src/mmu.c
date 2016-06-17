/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"
#include "i386.h"
//extern tlbflush();
#define PDE_INDEX(virtual) (virtual >> 22)
#define PTE_INDEX(virtual) ((virtual & 0x003FF000) >> 12)
#define ALIGN(dir) ???
#define PG_SET_READ_WRITE_AND_PRESENT 0x00000003
#define PG_SET_ATTRIB_0 0xFFFFFF03
#define PG_USER ???
#define PG_PRESENT 0x00000001
#define PG_DELETE_PRESENT 0xFFFFFFFE

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
    int PDEindex = PDE_INDEX(virtual);
    int PTEindex = PTE_INDEX(virtual);

//    2 Obtener el PDE correspondiente al esquema de
//          paginaci´on cr3 y el Indice de Directorio, si no es valido,
//          inicializar una nueva tabla de paginas.
    int* PDE = &((int *)cr3)[PDEindex];
    unsigned int nuevaPagina;
    if(!((*PDE) & PG_PRESENT)){
      nuevaPagina = mmu_proxima_pagina_fisica_libre();
      *PDE = (nuevaPagina | PG_SET_READ_WRITE_AND_PRESENT);
      //Seteamos en 0 la nueva pagina
      int i;
      for(i = 0; i < 1024; i++){
        int * punteroANuevaPagina = (int *) nuevaPagina;
        punteroANuevaPagina[i] = 0;
      }

    }

//    3 Obtener el PTE correspondiente al esquema de paginaci´on
//          cr3 y el Indice de Tabla.

    int dir_page_table = (unsigned int) *PDE & 0xFFFFF000;
    int* PTE = &(((int*)(dir_page_table))[PTEindex]);


//    4 Completar la PTE seg´un corresponda para mapear la
//          direccion fisica.

    *PTE = fisica | PG_SET_READ_WRITE_AND_PRESENT;

}

void mmu_unmapear_pagina(unsigned int virtual, unsigned int cr3){
    int PDEindex = PDE_INDEX(virtual);
    int PTEindex = PTE_INDEX(virtual);
    int* PDE = &((int *)cr3)[PDEindex];
    int dir_page_table = (unsigned int) *PDE & 0xFFFFF000;
    int* PTE = &(((int*)(dir_page_table))[PTEindex]);
    *PTE = (*PTE) & PG_DELETE_PRESENT;
    tlbflush();
}




void mmu_inicializar_dir_kernel(){
  unsigned int * pageTable = (unsigned int *) 0x28000;
  unsigned int * tableDeDirecciones = (unsigned int *) 0x27000;
  *tableDeDirecciones = (unsigned int) pageTable | 3;
  tableDeDirecciones++;
  int i = 1 ;
  for(i = 1; i < 1024; i++){
    *tableDeDirecciones = 0;
    tableDeDirecciones++;
  }
  int j = 0 ;
  for(j = 0; j < 1024; j++){
    *pageTable = j*4096 | 3;
    pageTable++;
  }
}


unsigned int mmu_inicializar_dir_tarea( unsigned int cr3, unsigned int dirFisicaTarea, int x, int y){
//  breakpoint();
  unsigned int* pageDirectory = (unsigned int*) mmu_proxima_pagina_fisica_libre();
  unsigned int* paginacionTareas = pageDirectory;
  unsigned int* pageTable = (unsigned int*) mmu_proxima_pagina_fisica_libre();
  *pageDirectory = ((unsigned int)(pageTable) | 3);
  pageDirectory++;
  int i = 1 ;
  for(i = 1; i < 1024; i++){
    *pageDirectory = 0;
    pageDirectory++;
  }
  
  int j = 0 ;
  for(j = 0; j < 1024; j++){
    *pageTable = j*4096 | 3;
    pageTable++;
  }


  int * dirEnMapa = (int*) ((x + y*80)*4096 + 0x400000); //transforma de (x,y) a direccion de memoria
  mmu_mapear_pagina(0x08000000, (unsigned int) paginacionTareas, (unsigned int) dirEnMapa);
  mmu_mapear_pagina((unsigned int) dirEnMapa, cr3, (unsigned int) dirEnMapa);


  int k = 0;
  for(k = 0; k < 1024; k++){
    *(dirEnMapa + k) = *((int *) dirFisicaTarea + k);
  }



  mmu_unmapear_pagina((unsigned int) dirEnMapa, cr3);

  return (unsigned int) paginacionTareas;

}
