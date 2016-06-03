; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
; definicion de rutinas de atencion de interrupciones

%include "imprimir.mac"

msj0: db'Divide Error!'
msj0_len equ $ - msj0

msj1: db'RESERVED'
msj1_len equ $ - msj1

msj2: db'NMI interrupt'
msj2_len equ $ - msj2

msj3: db'Breakpoint'
msj3_len equ $ - msj3

msj4: db'Overflow'
msj4_len equ $ - msj4

msj5: db'BOUND Range Exceeded'
msj5_len equ $ - msj5

msj6: db'Invalid Opcode(Undefined Opcode)'
msj6_len equ $ - msj6

msj7: db'Device Not Available(No Math Coprocessor)'
msj7_len equ $ - msj7

msj8: db'Double Fault'
msj8_len equ $ - msj8

msj9: db'Coprocessor Segment Overrun(reserved)'
msj9_len equ $ - msj9

msj10: db'Invalid TSS'
msj10_len equ $ - msj10

msj11: db'Segment Not Present'
msj11_len equ $ - msj11

msj12: db'Stack-Segment Fault'
msj12_len equ $ - msj12

msj13: db'General Protection'
msj13_len equ $ - msj13

msj14: db'Page Fault'
msj14_len equ $ - msj14

msj15: db'Intel Reserved. Do not use'
msj15_len equ $ - msj15

msj16: db'x87 FPU Floating-Point Error(Math Fault)'
msj16_len equ $ - msj16

msj17: db'Alignment Check'
msj17_len equ $ - msj17

msj18: db'Machine Check'
msj18_len equ $ - msj18

msj19: db'SIMD Floating-Point Exception'
msj19_len equ $ - msj19


BITS 32

sched_tarea_offset:     dd 0x00
sched_tarea_selector:   dw 0x00

;; PIC
extern fin_intr_pic1

;; Sched
extern sched_proximo_indice

;;
;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;
global _isr32
global _isr33
global _isr66
%macro ISR 1
global _isr%1

_isr%1:
    mov eax, %1
    imprimir_texto_mp msj%1, msj%1_len, 0x0f, 0, 0
    jmp $

%endmacro

%macro convertir_scanCode_Letra 1
;;;;;;;;;;;;COMPLETAAAAAAAAAAAAAAAAAAAAAARRRRRRRR MAIAME
    imprimir_texto_mp eax, 1, 0x0f, 0, 79

%endmacro

;;
;; Datos
;; -------------------------------------------------------------------------- ;;
; Scheduler
isrnumero:           dd 0x00000000
isrClock:            db '|/-\'

;;
;; Rutina de atención de las EXCEPCIONES
;; -------------------------------------------------------------------------- ;;
ISR 0
ISR 1
ISR 2
ISR 3
ISR 4
ISR 5
ISR 6
ISR 7
ISR 8
ISR 9
ISR 10
ISR 11
ISR 12
ISR 13
ISR 14
ISR 15
ISR 16
ISR 17
ISR 18
ISR 19

;;
;; Rutina de atención del RELOJ
;; -------------------------------------------------------------------------- ;;
_isr32:
    pushfd
    call fin_intr_pic1
    call proximo_reloj
    popfd
    iret
;;
;; Rutina de atención del TECLADO
;; -------------------------------------------------------------------------- ;;
_isr33:
    pushfd
    call fin_intr_pic1
    push eax
    xor eax, eax
    in al, 0x60
  ;  convertir_scanCode_Letra_Imprimir eax
    pop eax
    popfd
    iret
;;
;; Rutinas de atención de las SYSCALLS
;; -------------------------------------------------------------------------- ;;
_isr66:
    mov eax, 0x42
    iret





%define DONDE  0x124
%define SOY    0xA6A
%define MAPEAR 0xFF3

%define VIRUS_ROJO 0x841
%define VIRUS_AZUL 0x325


;; Funciones Auxiliares
;; -------------------------------------------------------------------------- ;;
proximo_reloj:
        pushad
        inc DWORD [isrnumero]
        mov ebx, [isrnumero]
        cmp ebx, 0x4
        jl .ok
                mov DWORD [isrnumero], 0x0
                mov ebx, 0
        .ok:
                add ebx, isrClock
                imprimir_texto_mp ebx, 1, 0x0f, 49, 79
                popad
        ret
