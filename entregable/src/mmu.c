/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"
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
      *PDE = (nuevaPagina | PG_SET_READ_WRITE_AND_PRESENT) & PG_SET_ATTRIB_0;
      //Seteamos en 0 la nueva pagina
      int i;
      for(i = 0; i < 1024; i++){
        int * punteroANuevaPagina = (int *) nuevaPagina;
        punteroANuevaPagina[i] = 0;
      }

    }

//    3 Obtener el PTE correspondiente al esquema de paginaci´on
//          cr3 y el Indice de Tabla.

    int dir_page_table = (unsigned int) *PDE & 0xFFFFF800; //MIAMEEE
    int* PTE = &(((int*)(dir_page_table))[PTEindex]);


//    4 Completar la PTE seg´un corresponda para mapear la
//          direccion fisica.

    *PTE = ((fisica >> 12) | PG_SET_READ_WRITE_AND_PRESENT) & PG_SET_ATTRIB_0;

//    5 Ejecutar tlbflush() para invalidar la cache de
//          traducciones.
    tlbflush();
}

void mmu_unmapear_pagina(unsigned int virtual, unsigned int cr3){
    int PDEindex = PDE_INDEX(virtual);
    int* PDE = &((int *)cr3)[PDEindex];
    *PDE = (*PDE) & PG_DELETE_PRESENT;
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


void mmu_inicializar_dir_tarea( unsigned int cr3,  unsigned int tipoDeTarea, int x, int y){
  unsigned int* pageDirectory = (unsigned int*) mmu_proxima_pagina_fisica_libre();
  unsigned int* paginacionTareas = pageDirectory;
  unsigned int* pageTable = (unsigned int*) mmu_proxima_pagina_fisica_libre();
  *pageDirectory = ((unsigned int)(pageTable) | 3);
  pageDirectory++;
  for(int i = 1; i < 1024; i++){
    *pageDirectory = 0;
    pageDirectory++;
  }

  for(int j = 0; j < 1024; j++){
    *pageTable =  0;
    pageTable++;
  }
  unsigned int dirFisicaTarea;
  switch(tipoDeTarea) {
      case 'I' :
          dirFisicaTarea = 0x10000;
          break;
      case 'A' :
          dirFisicaTarea = 0x11000;
          break;
      case 'B' :
         dirFisicaTarea = 0x12000;
         break;
      case 'H' :
         dirFisicaTarea = 0x13000;
         break;
      default :
         dirFisicaTarea = 0xFFFFFFFF;
   }

  mmu_mapear_pagina(0x08000000, (unsigned int) paginacionTareas, dirFisicaTarea);
  mmu_mapear_pagina(dirFisicaTarea, cr3, dirFisicaTarea);
  int * dirEnMapa = (int*) ((x + y*80)*4096 + 400000); //transforma de (x,y) a direccion de memoria
  int k = 0;
  for(k = 0; k < 1024; k++){
    dirEnMapa = (int *) dirFisicaTarea + k;
    dirEnMapa++;
  }
  mmu_unmapear_pagina(dirFisicaTarea, cr3);

}
