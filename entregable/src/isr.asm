; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
; definicion de rutinas de atencion de interrupciones


%include "imprimir.mac"
%define DONDE  0x124
%define SOY    0xA6A
%define MAPEAR 0xFF3
%define VIRUS_ROJO 0x841
%define VIRUS_AZUL 0x325

extern dameack
extern habilitarDebug
extern atenderdebug
extern volverDeExcepcion
extern iniciarGame
extern juegoIniciado
extern dameTarea
extern tareaActual
extern sched_proximo_indice
extern game_donde
extern game_mapear
extern game_mover_cursor
extern game_lanzar
extern pintarPuntajeAzul
extern pintarPuntajeRojo
extern print_hex
extern pintarTareaActual
extern actualizarReloj
extern estaPintadoDebug
extern estaDebugActivado
extern bastaChicos

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
%define Y 0x15
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

    call estaDebugActivado
    cmp eax, 0
    je .noPushear
    push eax ; eax lo vamos a usar para pushear la informacion que hay actualmente en la pila
    mov eax, [esp + 8] ; en esp + 8 esta el eip
    push eax ; se pushea el eip
    mov eax, [esp + 16] ; en esp + 16 esta el cs
    push eax ; se pushea el cs
    mov eax, [esp + 24] ; en esp + 24 esta el eflags
    push eax ; se pushea el eflags
    mov eax, [esp + 32] ;en esp + 32 esta el esp original
    push eax ; se pushea el esp original
    mov eax, [esp + 40] ; en esp + 40 esta el ss
    push eax ; se pushea el ss
    push gs
    push fs
    push es
    push ds
    push ebp
    push edi
    push esi
    push edx
    push ecx
    push ebx
    mov eax, cr4
    push eax
    mov eax, cr3
    push eax
    mov eax, cr2
    push eax
    mov eax, cr0
    push eax
    call atenderdebug
    pop eax
    pop eax
    pop eax
    pop eax
    pop eax
    pop ebx
    pop ecx
    pop edx
    pop esi
    pop edi
    pop ebp
    pop ds
    pop es
    pop fs
    pop gs
    .noPushear:
    mov eax, %1
    call volverDeExcepcion
    mov eax, 0x50
    mov [selector], eax
    jmp far [offset]
    call bastaChicos
    jmp -4

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

salvarRegs:
push eax ; Como lo voy a pisar , primero lo guardo
call dameack ; Ahora EAX tiene donde arranca el array ; Esta en Game.c
;Dejo 4 para poner EAX al principio, esto lo voy a hacer al final
mov dword [eax+4] , ebx
add eax ,4
mov dword [EAX],ECX
add eax , 4
mov dword [EAX] , EDX
add eax , 4
mov dword [EAX], ESI
add eax , 4
mov dword [EAX] , EDI
add eax , 4
mov dword [EAX] , EBP
add eax , 4
mov dword [EAX] , ESP
add eax , 4
mov dword [EAX] , EBX ; Aca iria EIP pero ni idea como hacerlo
add eax , 4
mov [EAX] , CS
add eax , 4
mov [EAX] , DS
add eax , 4
mov [EAX] , FS
add eax , 4
mov [EAX] , GS
add eax , 4
mov [EAX] , SS
add eax , 4
;pushfd ; Pusheo EFlags
;pop ebx ; Levanto EFLAGS em EBX ; Las Flags se pushean ?
mov dword [EAX] , EBX ; Aca iria EFLAGS ,
add eax , 4 ; Faltan los CR
mov ebx , CR0
mov dword [EAX] , EBX ; CR0
add eax , 4
mov ebx , CR1
mov dword [EAX] , ebx ; CR1
add eax ,4
mov ebx , CR2
mov dword [EAX] , EBX ; CR2
add eax , 4
mov ebx , CR3
mov dword [EAX] , EBX ; CR3
add eax , 4
mov EBX , CR4
mov [EAX] , EBX ; CR4
add eax , 4
mov ebx , eax ; Ahora ebx tiene el puntero
sub ebx , 76d ; 19 * 4 ; Hice 19 add si no manquee al contar
pop eax
mov [EBX] , EAX
;Queda EIP de la tarea cuando exploto , creo que eso se pushea a la pila , sera [EBP+X]
ret

_isr32:
    pushad
    pushfd

    call fin_intr_pic1
    call proximo_reloj
    call estaPintadoDebug
    cmp eax, 1
    je .salirDeReloj

    call sched_proximo_indice
    ;xchg bx, bx
    shl eax, 3

    mov [selector], ax
    jmp far [offset]

    .salirDeReloj:
    call actualizarReloj
    popfd
    popad
    iret
;;
;; Rutina de atención del TECLADO
;; -------------------------------------------------------------------------- ;;
_isr33:
  pushad
    pushfd
    call fin_intr_pic1                  ; El int 0 corresponde al jugador A
    xor eax, eax                        ; El int 1 corresponde al jugador B
    xor ebx, ebx                        ;
    in al, 0x60 ; en AL tengo el caracter pulsado
    push eax
    call juegoIniciado
    cmp eax, 0
    pop eax
    je .Space
    push eax
    call estaPintadoDebug
    cmp eax, 1
    pop eax
    je .teclaY
    ;Convertir_scanCode_Letra_Imprimir eax
    ;ACA EMPIEZA EL PLAYER A
    .ArbA:
    cmp al,W
    jne .IzqA
              mov ebx, "w"
              Palpatine ebx, 0x4
              push 0xA33 ; 0xA33 = ARB del game.h
              push 0  ;
              call game_mover_cursor ; En 32 bits, los parametros se pasan por la pila
              pop ebx
              pop ebx
              jmp .fin
    .IzqA:
    cmp al, A
    jne .AbaA
            mov ebx,"a"
            Palpatine ebx, 0x4
            push 0xAAA ; 0xAAA = IZQ del game.h
            push 0
            call game_mover_cursor
            pop ebx
            pop ebx
            jmp .fin
    .AbaA:
    cmp al, S
    jne .DerA
              mov ebx, "s"
              Palpatine ebx, 0x4
              push 0x883 ; 0x883 = ABA del game.h
              push 0
              call game_mover_cursor
              pop ebx
              pop ebx
              jmp .fin
    .DerA:
    cmp al, D
    jne .LanzarA
              mov ebx, "d"
              Palpatine ebx, 0x4
              push 0x441 ; 0x441 = DER del game.h
              push 0
              call game_mover_cursor
              pop ebx
              pop ebx
              jmp .fin
    .LanzarA:
    cmp al , lShift
    jne .PlayerB
                mov ebx ,"L"
                Palpatine ebx, 0x4
                push 0
                call game_lanzar
                pop ebx
                jmp .fin

    ;A PARTIR DE AHORA ES EL PLAYER B
    .PlayerB:
    .ArbB:
    cmp al , I
    jne .AbaB

                mov ebx, "i"
                Palpatine ebx, 0x9
                push 0xA33 ; 0xA33 = ARB del game.h
                push 1  ;
                call game_mover_cursor ; En 32 bits, los parametros se pasan por la pila
                pop ebx
                pop ebx
                jmp .fin
    .AbaB:
    cmp al , K
    jne .IzqB

                mov ebx, "k"
                Palpatine ebx, 0x9
                push 0x883 ; 0x883 = ABA del game.h
                push 1
                call game_mover_cursor
                pop ebx
                pop ebx
                jmp .fin

    .IzqB:
    cmp al , J
    jne .DerB
              mov ebx, "j"
              Palpatine ebx, 0x9
              push 0xAAA ; 0xAAA = IZQ del game.h
              push 1
              call game_mover_cursor
              pop ebx
              pop ebx
              jmp .fin
    .DerB:
    cmp al, L
    jne .LanzarB
              mov ebx, "l"
              Palpatine ebx, 0x9
              push 0x441 ; 0x441 = DER del game.h
              push 1
              call game_mover_cursor
              pop ebx
              pop ebx
              jmp .fin

    .LanzarB:
    cmp al, rShift
    jne .teclaY
              mov ebx ,"R"
              Palpatine ebx, 0x9
              push 1
            ;  xchg bx, bx
              call game_lanzar
              pop ebx
              jmp .fin
    ; Me queda hacer la interrupcion de la y, el modo debug mencionado en la sec 3.4
    ; Si llego aca es que se apreto alguna tecla no valida
    .teclaY:
    cmp al , Y
    jne .Space
    call habilitarDebug
    jmp .fin
    .Space:
    cmp al, 0x39
    jne .fin
    call juegoIniciado
    cmp eax, 1
    je .fin
    call iniciarGame

    .fin:
    popfd
    popad
    iret

;;
;; Rutinas de atención de las SYSCALLS
;; -------------------------------------------------------------------------- ;;
_isr102:
    pushad
    ;xchg bx, bx
    cmp eax, 0x124
    je .donde
    cmp eax, 0xA6A
    je .soy
    cmp eax, 0xFF3
    je .mapear
    jmp .maiamee

    .donde:
    ;xchg bx, bx
      push ebx
      call game_donde
      pop ebx
      jmp .maiamee

    .soy:
    ;xchg bx, bx
      cmp ebx, 0x841
      je .rojo
      cmp ebx, 0x325
      je .azul
      mov eax, 0
      jmp .maiamee
      .rojo:
        call pintarPuntajeRojo
        mov eax, VIRUS_ROJO
        jmp .maiamee
      .azul:
        call pintarPuntajeAzul
        mov eax, VIRUS_AZUL
        jmp .maiamee

    .mapear:
    ;xchg bx, bx
      push ecx
      push ebx
      call game_mapear
      pop ebx
      pop ecx

    .maiamee:
    mov eax, 0x50 ;0x50 es la dir a tarea IDLE. Believme, i'm Fort. Ricky Fort.
    mov [selector], ax
    jmp far [offset]
    popad
    iret






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

proximo_reloj_tarea: ;;;SIN TERMINAR
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
message1: db '|' ;;;ESTO ES PARA RELOJ DE TAREAS
message2: db '/'
message3: db '-'
message4: db '\'
