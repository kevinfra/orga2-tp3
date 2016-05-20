; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

%include "imprimir.mac"

global start

extern GDT_DESC

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
    

    ; Habilitar A20
    call habilitar_A20
    ; Cargar la GDT
    lgdt [GDT_DESC]

    ;xchg bx , bx ; Magic Breakpoints
    ; Setear el bit PE del registro CR0
    ; cli Desahibilita interrupciones , esta hecho al inicio del start
    mov eax , cr0
    or eax , 1
    mov cr0 , eax ; Luego de esta instruccion el bit de PE de CR0 esta prendido

    ; Saltar a modo protegido
    jmp 0x20:mp
    ;0x20 Selector , para calcular el selector se busco el indice de datos de nivel 0 de la GDT 
    ;Y se lo shifteo 3 lugares a la izquierda (osea se lo multiplico por 8)

 BITS 32 ; Esto es para decirle al ensamblador que a partir de ahora las instrucciones son de 32 bits
    ; Establecer selectores de segmentos
    mp:
    xor eax , eax
    ; xchg bx , xchang en la realidad es un swap pero para bochs es un Magic Breakpoint 
    mov ax , 0x30 ; 48 en Hexa
    mov ds , ax
    mov es , ax
    mov gs , ax
    mov ax , 0xB800
    mov fs , ax ; Segmento de Video
    ; Establecer la base de la pila
    mov ax , 0x27000
    mov ss , ax ; Segmento de pila
    ; Imprimir mensaje de bienvenida
    
    ; Inicializar pantalla
    
    
    ; Inicializar el manejador de memoria
 
    ; Inicializar el directorio de paginas
    
    ; Cargar directorio de paginas

    ; Habilitar paginacion
    
    ; Inicializar tss

    ; Inicializar tss de la tarea Idle

    ; Inicializar el scheduler

    ; Inicializar la IDT
    
    ; Cargar IDT
 
    ; Configurar controlador de interrupciones

    ; Cargar tarea inicial

    ; Habilitar interrupciones

    ; Saltar a la primera tarea: Idle

    ; Ciclar infinitamente (por si algo sale mal...)
    mov eax, 0xFFFF
    mov ebx, 0xFFFF
    mov ecx, 0xFFFF
    mov edx, 0xFFFF
    jmp $
    jmp $

;; -------------------------------------------------------------------------- ;;

%include "a20.asm"
