; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
; definicion de rutinas de atencion de interrupciones

%include "imprimir.mac"
extern dameTarea
extern tareaActual
<<<<<<< HEAD
extern sched_proximo_indice
extern posTareaActual
extern game_mapear
=======
extern game_mover_cursor
extern game_lanzar
>>>>>>> 92f924aaa4eb8f1c44716b04655470209daca75a

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

;Definicion para la interupcion de teclado
%define W 0x11
%define A 0x1E
%define S 0x1F
%define D 0x20
%define lShift 0x2A
%define rShift 0x36
%define I 0x17
%define K 0x25
%define J 0x24
%define L 0x26

;Numeritos obtenidos de http://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html

;;
;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;
global _isr32
global _isr33
global _isr102
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
    pushad
    pushfd
    call fin_intr_pic1
    call proximo_reloj
    call sched_proximo_indice
    xchg bx, bx
    mov dword [offset], 0
    mov [selector], ax
    jmp far [offset]

    popfd
    popad
    iret
;;
;; Rutina de atención del TECLADO
;; -------------------------------------------------------------------------- ;;
_isr33:
    pushad
    pushfd
    call fin_intr_pic1
    xor eax, eax
    xor ebx, ebx
    in al, 0x60 ; en AL tengo el caracter pulsado
  ;  convertir_scanCode_Letra_Imprimir eax
    ;ACA EMPIEZA EL PLAYER A
    mov ebx, "w"
    cmp al,   W
    je .ArbA
              .ArbA:
              imprimir_texto_mp ebx, 1, 0x0F, 0, 79
              push 0xA33 ; 0xA33 = ARB del game.h
              push 0  ; El 1 D es fruta por ahora, quiero que sea el jugador A
              call game_mover_cursor ; En 32 bits, los parametros se pasan por la pila
              pop ebx
              pop ebx
              jmp .fin

    mov ebx,"a"
    cmp al, A
    je .IzqA
            .IzqA:
            imprimir_texto_mp ebx, 1, 0x0F, 0, 79
            push 0xAAA ; 0xAAA = IZQ del game.h
            push 0
            call game_mover_cursor
            pop ebx
            pop ebx
            jmp .fin

    mov ebx, "s"
    cmp al, S
    je .AbaA
              .AbaA:
              imprimir_texto_mp ebx, 1, 0x0F, 0, 79
              push 0x883 ; 0x883 = ABA del game.h
              push 0
              call game_mover_cursor
              pop ebx
              pop ebx
              jmp .fin
    mov ebx, "d"
    cmp al, D
    je .DerA
              .DerA:
              imprimir_texto_mp ebx, 1, 0x0F, 0, 79
              push 0x441 ; 0x441 = DER del game.h
              push 0
              call game_mover_cursor
              pop ebx
              pop ebx
              jmp .fin

    cmp al , lShift
    mov ebx ,"L"
    je .LanzarA
                .LanzarA:
                imprimir_texto_mp ebx, 1, 0x0F, 0, 79
                push 0
                call game_lanzar
                pop ebx
                jmp .fin

    ;A PARTIR DE AHORA ES EL PLAYER B
    cmp al , I
    mov ebx, "i"
    je .ArbB
                .ArbB:
                imprimir_texto_mp ebx, 1, 0x0F, 0, 79
                push 0xA33 ; 0xA33 = ARB del game.h
                push 1  ; El 1 D es fruta por ahora, quiero que sea el jugador A
                call game_mover_cursor ; En 32 bits, los parametros se pasan por la pila
                pop ebx
                pop ebx
                jmp .fin

    cmp al , K
    mov ebx, "k"
    je .AbaB
                .AbaB:
                imprimir_texto_mp ebx, 1, 0x0F, 0, 79
                push 0x883 ; 0x883 = ABA del game.h
                push 1
                call game_mover_cursor
                pop ebx
                pop ebx
                jmp .fin

    cmp al , J
    mov ebx, "j"
    je .IzqB
              .IzqB:
              imprimir_texto_mp ebx, 1, 0x0F, 0, 79
              push 0xAAA ; 0xAAA = IZQ del game.h
              push 1
              call game_mover_cursor
              pop ebx
              pop ebx
              jmp .fin
    cmp al, L
    mov ebx, "l"
    je .DerB
              .DerB:
              imprimir_texto_mp ebx, 1, 0x0F, 0, 79
              push 0x441 ; 0x441 = DER del game.h
              push 1
              call game_mover_cursor
              pop ebx
              pop ebx
              jmp .fin

    cmp al, rShift
    mov ebx ,"R"
    je .LanzarB
              .LanzarB:
              imprimir_texto_mp ebx, 1, 0x0F, 0, 79
              push 1
              call game_lanzar
              pop ebx
              jmp .fin
    ;Me queda hacer la interrupcion de la y, el modo debug mencionado en la sec 3.4
    jmp .fin ; Si llego aca es que se apreto alguna tecla no valida
    .fin:
    popfd
    popad
    iret
;;
;; Rutinas de atención de las SYSCALLS
;; -------------------------------------------------------------------------- ;;
_isr102:
    pushad
    cmp eax, 0x124
    je .donde
    cmp eax, 0xA6A
    je .soy
    cmp eax, 0xFF3
    je .mapear
    jmp .fin

    .donde:
      push ebx
      call posTareaActual
      pop ebx
      mov edx, [eax] ;accedo a tupla.x
      mov ecx, [eax + 2] ;son 2 unsigned short, así que accedo a la variable .y
      mov [ebx], edx
      mov [ebx + 2], ecx
      jmp .fin

    .soy:
      cmp ebx, 0x841
      je .rojo
      cmp ebx, 0x325
      je .azul
      mov eax, 0
      jmp .fin
      .rojo:
        mov eax, 1
        jmp .fin
      .azul:
        mov eax, 2
        jmp .fin

    .mapear:
      push ecx
      push ebx
      call game_mapear

    .fin:
    mov eax, 0x48 ;0x48 es la dir a tarea IDLE. Believme, i'm Fort. Ricky Fort.
    mov [selector], ax
    jmp far [offset]
    popad
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


offset: dd 0
selector: dw 0
