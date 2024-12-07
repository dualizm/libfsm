CC := gcc
CFLAGS := -Wall -Wextra -Werror -std=c99
LDFLAGS := -L../out
INC_DIR := -I../lib

SRC_DIR := .
HEADERS_DIR := ../lib
BIN_DIR := ../bin

BINCODE_SRC := $(SRC_DIR)/bincode.c
BINCODE_OBJ := $(BINCODE_SRC:.c=.o)
EXEC_BINCODE := $(BIN_DIR)/bincode.out

PASSWORD_SRC := $(SRC_DIR)/password.c
PASSWORD_OBJ := $(PASSWORD_SRC:.c=.o)
EXEC_PASSWORD := $(BIN_DIR)/password.out

all: $(EXEC_BINCODE) $(EXEC_PASSWORD)

$(EXEC_BINCODE): $(BINCODE_OBJ) ../out/libfsm.a
	$(CC) $(CFLAGS) $(INC_DIR) $(LDFLAGS) -o $@ $^

$(BINCODE_OBJ): $(SRC_DIR)/%.o : $(SRC_DIR)/%.c $(HEADERS_DIR)/fsm.h
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

$(EXEC_PASSWORD): $(PASSWORD_OBJ) ../out/libfsm.a
	$(CC) $(CFLAGS) $(INC_DIR) $(LDFLAGS) -o $@ $^

$(PASSWORD_OBJ): $(SRC_DIR)/%.o : $(SRC_DIR)/%.c $(HEADERS_DIR)/fsm.h
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC_BINCODE) $(EXEC_PASSWORD)

.PHONY: all clean
