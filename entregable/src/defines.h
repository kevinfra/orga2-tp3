/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

    Definiciones globales del sistema.
*/

#ifndef __DEFINES_H__
#define __DEFINES_H__

/* Bool */
/* -------------------------------------------------------------------------- */
#define TRUE                    0x00000001
#define FALSE                   0x00000000
#define ERROR                   1


/* Misc */
/* -------------------------------------------------------------------------- */
#define CANT_H                 15
#define CANT                    5
#define SIZE_W                  80
#define SIZE_H                  44


/* Indices en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_COUNT 66						/*Determina el tamano de la GDT */

#define GDT_IDX_NULL_DESC       0
#define GDT_IDX_DESC_CODE0			4
#define GDT_IDX_DESC_CODE3			5
#define GDT_IDX_DESC_DATA0			6
#define GDT_IDX_DESC_DATA3			7
#define GDT_IDX_VIDEO_KERNEL    8

/* Offsets en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_OFF_NULL_DESC           (GDT_IDX_NULL_DESC      << 3)
     // Hace falta esto ? MIAMIIII
#define GDT_OFF_IDX_DESC_CODE0		(GDT_IDX_DESC_CODE0     << 3)
#define GDT_OFF_IDX_DESC_CODE3		(GDT_IDX_DESC_CODE3     << 3)
#define GDT_OFF_IDX_DESC_DATA0		(GDT_IDX_DESC_DATA0     << 3)
#define GDT_OFF_IDX_DESC_DATA3    	(GDT_IDX_DESC_DATA3     << 3)

/* Direcciones de memoria */
/* -------------------------------------------------------------------------- */
#define VIDEO_SCREEN            0x000B8000 /* direccion fisica del buffer de video */


/* inicializar paginacion */
#define INICIO_PAGINAS_LIBRES    0x100000
#define PAGE_SIZE                4096



#endif  /* !__DEFINES_H__ */
