SRC_DIR=./src
SRC=$(wildcard $(SRC_DIR)/*.c)

OBJ_DIR=./obj
OBJ=$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

LD=ld
GCC=gcc
CFLAGS=-static -nostdlib -ffreestanding -g
# CFLAGS=-g
EXE=main

$(info $$SRC = $(SRC))
$(info $$OBJ = $(OBJ))
$(info $$CFLAGS = $(CFLAGS))


ifneq ($(wildcard $(OBJ_DIR)/*.o), "")
	FLAG_OBJ = 1
else
	FLAG_OBJ = 0
endif

.PHONY: all clean debug

debug: $(EXE)
	@gdb -q $(EXE)

clean:
	@if [ "$(FLAG_OBJ)" = "1" ]; then rm -f $(OBJ) ; fi
	@if [ -f "$(EXE)" ]; then rm "$(EXE)" ; fi

all: $(EXE)

$(EXE): $(OBJ)
	$(GCC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p "$(OBJ_DIR)"
	$(GCC) $(CFLAGS) -c $< -o $@
