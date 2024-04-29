all: calc 

calc: calc.o
	ld -g -m elf_i386 calc.o -o calc

calc.o: calc.s
	as -g -gstabs --32 calc.s -o calc.o

clean:
	rm  calc.o calc
