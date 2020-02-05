
#Variable

CFLAGS = -Wall -c

#
# Liens
#

bin/shell1: obj/shell1.o
			   gcc -g -o bin/shell1 obj/shell1.o 

bin/shell2: obj/shell2.o
			   gcc -g -o bin/shell2 obj/shell2.o 

bin/shell3: obj/shell3.o
			   gcc -g -o bin/shell3 obj/shell3.o 

#
# Objets
#

obj/shell1.o: shell1.c 
			gcc $(CFLAGS) shell1.c -o obj/shell1.o

obj/shell2.o: shell2.c 
				 gcc $(CFLAGS) shell2.c -o obj/shell2.o

obj/shell3.o: shell3.c 
				 gcc $(CFLAGS) shell3.c -o obj/shell3.o

#
# supprimer les fichiers
#

clean : 
		rm -rf *.o
		

#
# Tester les chichiers
#

test_shell1 : obj/shell1.o
	   ./bin/shell1

test_shell2 : obj/shell2.o
	   ./bin/shell2

test_shell3 : obj/shell3.o
	   ./bin/shell3

#
#executer tous les makefiles
#
all : 
		make bin/shell1 bin/shell2 bin/shell3
