
#Variable

CFLAGS = -Wall -c

#
# Liens
#

tp3: tp3.o
			   gcc -g -o tp3 tp3.o 

nettoie: nettoie.o
			   gcc -g -o nettoie nettoie.o 

sem: sem.o
			   gcc -g -o sem sem.o 

#
# Objets
#

tp3.o: tp3.c 
			gcc $(CFLAGS) tp3.c -o tp3.o

nettoie.o: nettoie.c 
				 gcc $(CFLAGS) nettoie.c -o nettoie.o

sem.o: sem.c 
				 gcc $(CFLAGS) sem.c -o sem.o


#
# supprimer les fichiers
#

clean : 
		rm -rf *.o
		

#
# Tester les chichiers
#

test_tp3 : tp3.o
	   ./tp3

test_nettoie : nettoie.o
	   ./nettoie

test_sem : sem.o
	   ./sem


#
#compiler tous les fichiers
#
all : 
		make tp3  sem nettoie

