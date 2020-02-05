
#Variable

CFLAGS = -Wall -c

#
# Liens
#

shell1: shell1.o
			   gcc -g -o shell1 shell1.o 

shell2: shell2.o
			   gcc -g -o shell2 shell2.o 

shell3: shell3.o
			   gcc -g -o shell3 shell3.o 

#
# Objets
#

shell1.o: shell1.c 
			gcc $(CFLAGS) shell1.c -o shell1.o

shell2.o: shell2.c 
				 gcc $(CFLAGS) shell2.c -o shell2.o

shell3.o: shell3.c 
				 gcc $(CFLAGS) shell3.c -o shell3.o

#
# supprimer les fichiers
#

clean : 
		rm -rf *.o
		

#
# Tester les chichiers
#

test_shell1 : shell1.o
	   ./shell1

test_shell2 : shell2.o
	   ./shell2

test_shell3 : shell3.o
	   ./shell3

#
#compiler tous les fichiers
#
all : 
		make shell1 shell2 shell3
