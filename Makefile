TARGET	= dictionaryapp
TARGETDIR = bin
CC	= gcc
LINKER	= gcc
CFLAGS	= -std=c99 -Wall -g
SRCDIR	= src
OBJDIR	= obj
#INCLUDEDIR = ./include/
#INCLUDE=$(-I$(INCLUDEDIR))
SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

$(TARGET) : $(OBJECTS)
	echo $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(TARGETDIR)/$@

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm $(OBJDIR)/*
	rm $(TARGETDIR)/*
