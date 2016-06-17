; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

%include "imprimir.mac"
global start

extern IDT_DESC
extern GDT_DESC
extern idt_inicializar
extern mmu_inicializar_dir_kernel
extern mmu_inicializar
extern mmu_mapear_pagina
extern mmu_unmapear_pagina
extern mmu_inicializar_dir_tarea
extern tss_inicializar_idle
extern tss_inicializar_tareas_h
extern resetear_pic
extern habilitar_pic
extern deshabilitar_pic
extern inicializar_scheduler

;; Saltear seccion de datos
jmp start

;;
;; Seccion de datos.
;; -------------------------------------------------------------------------- ;;
iniciando_mr_msg db     'Iniciando kernel (Modo Real)...'
iniciando_mr_len equ    $ - iniciando_mr_msg

iniciando_mp_msg db     'Iniciando kernel (Modo Protegido)...'
iniciando_mp_len equ    $ - iniciando_mp_msg

;;
;; Seccion de código.
;; -------------------------------------------------------------------------- ;;

;; Punto de entrada del kernel.
BITS 16
start:
    ; Deshabilitar interrupciones
    cli

    ; Cambiar modo de video a 80 X 50
    mov ax, 0003h
    int 10h ; set mode 03h
    xor bx, bx
    mov ax, 1112h
    int 10h ; load 8x8 font

    ; Imprimir mensaje de bienvenida
    imprimir_texto_mr iniciando_mr_msg, iniciando_mr_len, 0x07, 0, 0

    ;De Aca en Adelante se fue modificando el codigo
    ; Habilitar A20
  ;  xchg bx , bx
    call habilitar_A20
    ; Cargar la GDT
    lgdt [GDT_DESC]

    ; Setear el bit PE del registro CR0
    mov eax , cr0
    or eax , 1
    mov cr0 , eax ; Luego de esta instruccion el bit de PE de CR0 esta prendido

    ; Saltar a modo protegido
    jmp 0x20:mp
    ;0x20 Selector , para calcular el selector se busco el indice de datos de nivel 0 de la GDT
    ;Y se lo shifteo 3 lugares a la izquierda (osea se lo multiplico por 8)

 BITS 32 ; Esto es para decirle al ensamblador que a partir de ahora las instrucciones son de 32 bits
    ; Establecer selectores de segmentos
    ; xchg bx , xchang en la realidad es un swap pero para bochs es un Magic Breakpoint
    mp:
  ;  xchg bx , bx
    xor eax , eax
    mov ax , 0x30 ; 48 en Hexa
    mov ds , ax ; AX tiene el indice de datos de nivel 0 shifteado 3 indices a la izquierda
    mov es , ax ;   MIAMII
    mov gs , ax ;
    mov fs , ax ; Segmento de Video ; C
  ;  xchg bx , bx ; Magic Breakpoints
    ; Establecer la base y tope de la pila de la pila
    mov esp , 0x27000 ;  MIAMIII
    mov ebp , 0x27000 ; MIAMIII
    mov ss , ax ; Segmento de pila

    ; Inicializar la IDT

    ; Cargar IDT

    ; Configurar controlador de interrupciones
    call idt_inicializar
    lidt [IDT_DESC]
    ; sti
    ; Imprimir mensaje de bienvenida
    ;xchg bx , bx
    imprimir_texto_mp iniciando_mp_msg, iniciando_mp_len, 0x07, 2, 0
    ; nop
    ; nop
    ; xchg bx , bx

    ; Inicializar pantalla

    ; ;SLIDE FURFI - 1° Clase . PP 80
    ;pintarPantalla
    pintarPantallaBaja

    ; xor ebx , ebx
    ; xor eax , eax
    ; div eax


    ; Inicializar el manejador de memoria




    ; Inicializar el directorio de paginas
    ; Cargar directorio de paginas Ejercicio 3 B
    call mmu_inicializar_dir_kernel

    ; Habilitar paginacion Ejercicio 3 C
    mov eax, 0x27000
    mov cr3 , eax
    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax
    call mmu_inicializar
;//TESTEO
;    push 5
;    push 5
;    push 'A'
;    mov eax, cr3
;    push eax
;    xchg bx, bx
;    call mmu_inicializar_dir_tarea
;    mov cr3, eax
;    xchg bx, bx
;//FIN TEST INICIALIZAR DIR TAREA


    ; Inicializar tss
    call tss_inicializar_idle
    ; Inicializar tss de la tarea Idle
    ltr ax
    add eax, 8
    push eax
    call tss_inicializar_tareas_h

    ; Inicializar el scheduler
    call inicializar_scheduler
    ; Cargar tarea inicial

    ; Habilitar interrupciones
    call resetear_pic
    call deshabilitar_pic
    call habilitar_pic
    sti
    int 0x66


    ; Saltar a la primera tarea: Idle

    xchg bx, bx
    pop eax
    mov [selector], ax
    jmp far [offset] ;dir_tarea_idle

    ; Ciclar infinitamente (por si algo sale mal...)
    xchg bx , bx
    nop
    mov eax, 0xFFFF
    ;LALALALALA BRASIL QUEDO ELIMINADO MUAJAJAJA
    mov ebx, 0xFFFF
    mov ecx, 0xFFFF
    mov edx, 0xFFFF
    jmp $
    jmp $

;; -------------------------------------------------------------------------- ;;

%include "a20.asm"
offset: dd 0
selector: dw 0
