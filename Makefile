TARGET = dictionaryapp
TARGETDIR = bin/
CC = gcc
CFLAGS = -std=c99 -Wall -I
SRCDIR=./src/
OBJDIR=./obj
SOURCES = $(wildcard $(SRCDIR)*.c)
INCLUDEDIR = ./include/
INCLUDE=$(-I$(INCLUDEDIR))
OBJECTS=$(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
$(TARGET) : $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(INCLUDE) -o $(TARGETDIR)/$@
.c.o:
	$(CC) $(SOURCES) $(CFLAGS) $< -o $@
