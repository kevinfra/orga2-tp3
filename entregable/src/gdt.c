/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de la tabla de descriptores globales
*/

#include "gdt.h"

unsigned int proximo_Slot_Libre;

void inicializar_proximoSlotLibre(){
  proximo_Slot_Libre = 9;
}
unsigned int proximoSlotLibre(){
  unsigned int slot_libre = proximo_Slot_Libre;
  proximo_Slot_Libre++;
  return slot_libre;
}

gdt_entry gdt[GDT_COUNT] = {
    /* Descriptor nulo*/
    /* Offset = 0x00 */
    [GDT_IDX_NULL_DESC] = (gdt_entry) {
        (unsigned short)    0x0000,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x00,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x00,           /* dpl          */
        (unsigned char)     0x00,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */



    },

    [GDT_IDX_DESC_CODE0] = (gdt_entry) {
        (unsigned short)    0x6DFF,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     8,              /* type         */
        (unsigned char)     1,              /* s            */
        (unsigned char)     0,              /* dpl          */
        (unsigned char)     1,              /* p            */
        (unsigned char)     3,              /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     1,              /* db           */
        (unsigned char)     1,              /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */




    },
/* Para calcular el limite:

La cuenta para calcular el limite es la siguiente           (**=Elevado a )              (2**12)
Calculamos cuanto es 878 MB , para eso multiplicamos 878 * (2**20) y a eso lo dividimos por 4k
Creo que se dividia debido a la grannularidad , luego  al resultado luego se le resta 1
Eso da 224767 , en hexa es 36DFF

Para completar este archivo , se utilizo las paginas 11 y 12 del pdf "A modo protegido y mas alla"
Ademas, se modifico el archivo defines.h


*/




    [GDT_IDX_DESC_CODE3] = (gdt_entry) {
        (unsigned short)    0x6DFF,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     8,              /* type         */
        (unsigned char)     1,              /* s            */
        (unsigned char)     3,              /* dpl          */
        (unsigned char)     1,              /* p            */
        (unsigned char)     3,           	/* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     1,              /* db           */
        (unsigned char)     1,              /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */



    },



    [GDT_IDX_DESC_DATA0] = (gdt_entry) {
        (unsigned short)    0x6DFF,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     2,              /* type         */
        (unsigned char)     1,              /* s            */
        (unsigned char)     0,              /* dpl          */
        (unsigned char)     1,              /* p            */
        (unsigned char)     3,            	/* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     1,              /* db           */
        (unsigned char)     1,              /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */



    },


    [GDT_IDX_DESC_DATA3] = (gdt_entry) {
        (unsigned short)    0x6DFF,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     2,              /* type         */
        (unsigned char)     1,              /* s            */
        (unsigned char)     3,              /* dpl          */
        (unsigned char)     1,              /* p            */
        (unsigned char)     3,            	/* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     1,              /* db           */
        (unsigned char)     1,              /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */



    },



    [GDT_IDX_VIDEO_KERNEL] = (gdt_entry) {
        (unsigned short)    0x1F3F,         /* limit[0:15]  */
        (unsigned short)    0x8000,         /* base[0:15]   */
        (unsigned char)     0xB,            /* base[23:16]  */
        (unsigned char)     2,              /* type         */
        (unsigned char)     1,              /* s            */
        (unsigned char)     0,              /* dpl          */
        (unsigned char)     1,              /* p            */
        (unsigned char)     0,              /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     1,              /* db           */
        (unsigned char)     0,              /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */


    }

};

gdt_descriptor GDT_DESC = {
    sizeof(gdt) - 1,
    (unsigned int) &gdt
};
