#Aluno: Mateus Oliveira Santos
#Matrícula: 20251045050330
#Avaliação 04: Trabalho final
#04.505.23 - 2025.2 - Prof.Daniel Ferreira
#Compilador: gcc (MinGW.org GCC-6.3.0.1) 6.3.0

CC = gcc

CFLAGS = -I./bib -Wall

TARGET = file_encoder

OBJS = lib/main.o \
       lib/compressionfactor.o \
       lib/decoder.o \
       lib/encoder_manager.o \
       lib/encoder.o \
       lib/pgm.o \
       lib/quadtree.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

lib/%.o: lib/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
#del /Q $(OBJS) $(TARGET)
	rm -f $(OBJS) $(TARGET) 