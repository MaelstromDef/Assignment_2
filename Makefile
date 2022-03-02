# Compiler
CC=g++

# File Directories
CODEDIRS=. ./SourceFiles/
HEADDIRS=. ./HeaderFiles/

OPT=-O0
DEPFLAGS=-MP -MD

# Compiler Specifications
CFLAGS=-Wall -Wextra -g $(foreach D,$(HEADDIRS), -I$(D)) $(OPT) $(DEPFLAGS)

# FILES AND OBJECTS
CFILES=$(foreach C, $(CODEDIRS), $(wildcard $(C)/*.cc))
HFILES=$(foreach H, $(HEADDIRS), $(wildcard $(H)/*.h))

OBJECTS=$(patsubst %.c, %.o,$(CFILES))
DEPFILES=$(patsubst %.c, %.d, $(CFILES))

# Name of the binary executable
BINARY=earnings

# Makes everything the program needs
all: $(BINARY)

# Creates the binary executable
$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^

# CREATE .o FILES
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

# Removes all makefile-created files
clean:
	rm -rf $(BINARY) $(OBJECTS) $(DEPFILES)

-include $(DEPFILES)