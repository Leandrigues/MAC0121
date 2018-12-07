DEPS = estruturas.h
OBJ = ep4.o vetorDesord.o arvore.o vetorOrd.c listaLigOrd.c listaLigDesord.c
%.o: %.c %(DEPS)
	gcc -Wall -c -o $@ $<
ep4: ep4.c vetorDesord.c arvore.c vetorOrd.c listaLigOrd.c listaLigDesord.c
	gcc -Ofast -o ep4 ep4.c vetorDesord.c arvore.c vetorOrd.c listaLigOrd.c listaLigDesord.c
