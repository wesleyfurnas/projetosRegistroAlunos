main:	main.o	tree.o	
	gcc	main.o	tree.o	-o	app

main.o:	main.c
	gcc -c	main.c

tree.o:	tree.c
	gcc	-c	tree.c	tree.h

clean:
	rm	*.o
