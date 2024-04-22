all : dodawanie odejmowanie

dodawanie : dodawanie.o
	ld -o dodawanie dodawanie.o
dodawanie.o : dodawanie.s
	as --gstabs -o dodawanie.o dodawanie.s

odejmowanie : odejmowanie.o
	ld -o odejmowanie odejmowanie.o
odejmowanie.o : odejmowanie.s
	as --gstabs -o odejmowanie.o odejmowanie.s


clean :
	rm *.o 
