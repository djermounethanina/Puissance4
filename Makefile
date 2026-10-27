# Programme à créer
PROG = puissance4

# Fichiers sources
SRC = main.c jeu.c grille.c

# Règle par défaut : compile et exécute
all: $(PROG)
	./$(PROG)

# Compilation du programme
$(PROG): $(SRC) puissance4.h
	gcc -Wall -Wextra -o $(PROG) $(SRC)

# Nettoyage
clean:
	rm -f $(PROG)

.PHONY: all clean
