CC := gcc
CFLAGS := -Wall -Wextra -Werror -std=c99
AR := ar
ARFLAGS := rcs
LDFLAGS := -shared

LIB_DIR := .
OUT_DIR := ../out

LIB_SRC := $(LIB_DIR)/fsm.c
LIB_OBJ := $(patsubst $(LIB_DIR)/%.c, $(OUT_DIR)/%.o, $(LIB_SRC))

LIB_SO := $(OUT_DIR)/libfsm.so
LIB_A  := $(OUT_DIR)/libfsm.a

all: $(OUT_DIR) $(LIB_SO) $(LIB_A)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

$(LIB_SO): $(LIB_OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

$(LIB_A): $(LIB_OBJ)
	$(AR) $(ARFLAGS) $@ $^

$(OUT_DIR)/%.o: $(LIB_DIR)/%.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

clean:
	rm -rf $(LIB_SO) $(LIB_A) $(OUT_DIR)/*.o

.PHONY: all clean
