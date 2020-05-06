all: binary common name principals title

binary: main.o binary.o principals.o name.o binary.o title.o
	gcc -c main.c -o main.o -Iinclude

common: main.o common.o binary.o title.o principals.o name.o
	gcc -c main.c -o main.o -Iinclude

name: main.o name.o binary.o 
	gcc -c main.c -o main.o -Iinclude

principals: main.o principals.o binary.o 
	gcc -c main.c -o main.o -Iinclude

title: main.o title.o binary.o 
	gcc -c main.c -o main.o -Iinclude

main.o: main.c
	gcc -c main.c -o main.o -Iinclude

clean:
	rm -f *.o run