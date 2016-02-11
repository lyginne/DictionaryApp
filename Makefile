TARGET	= dictionaryapp
TARGETDIR = bin
CC	= gcc
LINKER	= gcc
CFLAGS	= -std=c99 -Wall
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
$(OBJECTS): | $(OBJDIR)
$(TARGET): | $(TARGETDIR)
$(OBJDIR):
	mkdir -p $(OBJDIR)
$(TARGETDIR):
	mkdir -p $(TARGETDIR)
clean:
	rm $(OBJDIR)/*
	rm $(TARGETDIR)/*
