CC ?= gcc
CFLAGS ?= -std=c11 -O2 -Wall -Wextra -Wpedantic
SRC := src/main.c src/cli.c src/lru.c

BINDIR := bin

ifeq ($(OS),Windows_NT)
  EXE := lru.exe
  RM := del /Q /F
  MKDIR_P = if not exist "$(BINDIR)" mkdir "$(BINDIR)"
  SEP := \\
else
  EXE := lru
  RM := rm -f
  MKDIR_P = mkdir -p $(BINDIR)
  SEP := /
endif

BIN := $(BINDIR)/$(EXE)

.PHONY: all clean run test

all: $(BIN)

$(BIN): $(SRC)
	$(MKDIR_P)
	$(CC) $(CFLAGS) -o $(BIN) $(SRC)

clean:
	-$(RM) $(BIN) 2>nul
	-$(RM) src$(SEP)*.o 2>nul

run: $(BIN)
	$(BIN)

test: $(BIN)
ifeq ($(OS),Windows_NT)
	@tests\\test.bat
else
	@bash tests/test.sh
endif
