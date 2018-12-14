INCDIR = inc/
CC = gcc
CFLAGS = -I $(INCDIR) `sdl2-config --cflags` #-std=c11 #-Wall -pedantic -ansi
LFLAGS = `sdl2-config --libs` -no-pie -lSDL2 -lSDL2_image
EXE = Snake

OBJDIR = obj/
LIBDIR = lib/
SRCDIR = src/

LIBS = -lm

_DEPS = main.h game.h draw.h
DEPS = $(patsubst %, $(INCDIR)%, $(_DEPS))

_OBJ = main.o game.o draw.o
OBJ = $(patsubst %, $(OBJDIR)%, $(_OBJ))

$(OBJDIR)%.o: $(SRCDIR)%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(LIBS) $(LFLAGS)

clean:
	rm -f $(OBJDIR)*.o $(EXE)
