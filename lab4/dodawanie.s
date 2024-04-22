SYS_EXIT = 1
EXIT_SUCCESS = 0
.code32

.data
liczba1:
    .long 0x00011110, 0x33333333, 0x2222222A, 0x11111111
liczba2:
    .long 0x000FFFF0, 0x00000000, 0x00000005, 0x00000000

bytes = . - liczba1

.text
.global start

start:

    clc #czyscimy flage
    mov $4, %ecx            #iterator petli
loop:
    movl liczba1(, %ecx, 4), %eax
    movl liczba2(, %ecx, 4), %ebx
    adcl %ebx, %eax         #odejmowanie
        setc %dl
    pushl %eax              # wynik odejmowania w eax na stos    

    cmp $0, %ecx
    je is_carry
    sbb $1, %ecx
    jmp loop #wracamy do petli

is_carry:
    jc carry_exists
    jnc no_carry

carry_exists:
    pushl %edx
    jmp end

no_carry:
    pushl %edx
    jmp end

end:
    mov $SYS_EXIT, %eax
    mov $EXIT_SUCCESS, %ebx
    int $0x80
