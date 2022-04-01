# Personal Variables

SYS=linux
CC=gcc
DEBUG=no
SRCDIR=src/
OBJDIR=obj/
HEADDIR=include/
EXECDIR=bin/
OUTPUT=tokenring
OUTPUT2=ringstat

# Do NOT modify these variables

EXEC=$(EXECDIR)$(OUTPUT)
EXEC2=$(EXECDIR)$(OUTPUT2)
SRC=$(wildcard $(SRCDIR)*.c)
OBJ=$(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(SRC))
HEAD=$(wildcard $(HEADDIR)*.h)
ifeq ($(DEBUG), yes)
	CFLAGS=-W -Wall -pedantic -g
	LDFLAGS=
else
	CFLAGS=-W -Wall -pedantic
	LDFLAGS=
endif
define execute
	@echo Generating $(1)...
	$(CC) -c $(2) -o $(1) -I$(HEADDIR) $(CFLAGS)
endef
vpath %.c $(SRCDIR)
vpath %.o $(OBJDIR)
vpath %.h $(HEADDIR)

# Rules

all: $(EXEC) $(EXEC2)
ifeq ($(DEBUG), yes)
	@echo Debug mode.
else
	@echo Release mode.
endif

$(EXEC): $(OBJDIR)system.o $(OBJDIR)TubeManager.o $(OBJDIR)FileManager.o $(OBJDIR)main.o
	@echo Compiling $^...
	$(CC) $^ -o $@ $(LDFLAGS)

$(EXEC2): $(OBJDIR)system.o $(OBJDIR)FileManager.o $(OBJDIR)RingStat.o
	@echo Compiling $^...
	$(CC) $^ -o $@ $(LDFLAGS)

# Personal Rules

$(OBJDIR)RingStat.o: RingStat.c system.h FileManager.h
	$(call execute,$@,$<)

$(OBJDIR)FileManager.o: FileManager.c FileManager.h system.h
	$(call execute,$@,$<)

$(OBJDIR)TubeManager.o: TubeManager.c TubeManager.h system.h
	$(call execute,$@,$<)
	
$(OBJDIR)system.o: system.c system.h
	$(call execute,$@,$<)
	
$(OBJDIR)main.o: main.c $(HEAD)
	$(call execute,$@,$<)

# Do NOT modify these rules

.PHONY: mrproper

clean: 
ifeq ($(SYS), windows)
	@erase /F /S *.o
else
	@rm -rf *.o
endif

mrproper: clean
ifeq ($(SYS), windows)
	@erase /F /S $(OUTPUT)
else
	@rm -rf $(OUTPUT)
endif
