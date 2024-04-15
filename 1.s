.section .text
.global _start

.code32  # Etykieta .code32 na starcie programu (pozwala na operacje na słowach 32-bitowych)

_start:
    # Dodawanie
    movl $0, %ecx         # Ustawiamy licznik na zero
    clc                   # Czyścimy flagę przeniesienia

dodawanie_loop:

    movl liczba1(,%ecx,4), %eax    # Wczytujemy kolejne słowa z liczba1
    adcl liczba2(,%ecx,4), %eax    # Dodajemy kolejne słowa z liczba2 z uwzględnieniem flagi przeniesienia
    pushl %eax                      # Wynik dodawania na stos

    incl %ecx           # Inkrementujemy licznik

    cmpl $4, %ecx       # Sprawdzamy, czy wykonaliśmy już dodawanie na wszystkich słowach
    jl dodawanie_loop   # Jeśli nie, to wracamy do góry pętli

    jc overflow         # Jeśli flaga przeniesienia jest ustawiona, to skaczemy do etykiety overflow

    # Odejmowanie
    movl $3, %ecx         # Ustawiamy licznik na trzy (bo mamy cztery słowa)
    clc                   # Czyścimy flagę przeniesienia

odejmowanie_loop:

    movl liczba1(,%ecx,4), %eax    # Wczytujemy kolejne słowa z liczba1
    sbbl liczba2(,%ecx,4), %eax    # Odejmujemy kolejne słowa z liczba2 z uwzględnieniem flagi przeniesienia
    pushl %eax                      # Wynik odejmowania na stos

    decl %ecx           # Dekrementujemy licznik

    cmpl $0, %ecx       # Sprawdzamy, czy wykonaliśmy już odejmowanie na wszystkich słowach
    jge odejmowanie_loop   # Jeśli tak, to wracamy do góry pętli

    jc overflow         # Jeśli flaga przeniesienia jest ustawiona, to skaczemy do etykiety overflow

    # Wyświetlenie wyników na stosie
    movl $0, %ebx       # Ustawiamy licznik dla wyświetlania stosu

print_loop:
    popl %eax           # Wyciągamy wartość ze stosu do eax
    movl $1, %edx       # Wartość 1 dla sys_write
    movl $1, %ecx       # Wartość 1 dla sys_write
    movl %eax, %ebx     # Wartość do wyświetlenia
    movl $4, %eax       # Syscall sys_write
    int $0x80           # Wywołanie syscalla

    incl %ebx           # Inkrementujemy licznik
    cmpl $8, %ebx       # Sprawdzamy, czy wyświetliliśmy już wszystkie wyniki
    jne print_loop      # Jeśli nie, to wracamy do góry pętli

exit:
    movl $1, %eax       # Syscall sys_exit
    xorl %ebx, %ebx     # Wartość zwracana z programu
    int $0x80           # Wywołanie syscalla

overflow:
    movl $1, %edx       # Wartość 1 dla sys_write
    movl $1, %ecx       # Wartość 1 dla sys_write
    movl $overflow_message, %ebx   # Adres komunikatu przepełnienia
    movl $4, %eax       # Syscall sys_write
    int $0x80           # Wywołanie syscalla
    jmp exit            # Skok do końca programu w przypadku przepełnienia

.section .rodata
overflow_message:
    .ascii "Przepełnienie!\n"

.section .data
liczba1:
    .long 0x11111111, 0x22222222, 0x33333333, 0x44444444
liczba2:
    .long 0x55555555, 0x66666666, 0x77777777, 0x88888888
