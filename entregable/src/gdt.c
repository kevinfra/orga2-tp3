/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de la tabla de descriptores globales
*/

#include "gdt.h"

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
        (unsigned char)     8,           /* type         */
        (unsigned char)     1,           /* s            */
        (unsigned char)     0,           /* dpl          */
        (unsigned char)     1,              /* p            */
        (unsigned char)     3,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     1,           /* db           */
        (unsigned char)     1,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */

//36DFF
        

    },

//  878 se pasa a MB , multiplicando 2**20 , a eso lo divido por 4k y luego le resto 1

    [GDT_IDX_DESC_CODE3] = (gdt_entry) {
        (unsigned short)    0x6DFF,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     8,           /* type         */
        (unsigned char)     1,           /* s            */
        (unsigned char)     3,           /* dpl          */
        (unsigned char)     1,           /* p            */
        (unsigned char)     0x01,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     1,           /* db           */
        (unsigned char)     1,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */

        

    },


    [GDT_IDX_DESC_DATA0] = (gdt_entry) {
        (unsigned short)    0x6DFF,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     2,           /* type         */
        (unsigned char)     1,           /* s            */
        (unsigned char)     0,           /* dpl          */
        (unsigned char)     1,           /* p            */
        (unsigned char)     0x1,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     1,           /* db           */
        (unsigned char)     1,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */

        

    },


    [GDT_IDX_DESC_DATA3] = (gdt_entry) {
        (unsigned short)    0x6DFF,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     2,           /* type         */
        (unsigned char)     1,           /* s            */
        (unsigned char)     3,           /* dpl          */
        (unsigned char)     1,           /* p            */
        (unsigned char)     0x1,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     1,           /* db           */
        (unsigned char)     1,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */

        

    },


  
    
};

gdt_descriptor GDT_DESC = {
    sizeof(gdt) - 1,
    (unsigned int) &gdt
};



