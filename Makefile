SHELL=/bin/bash

CC = gcc
LINK = gcc
DOC = doxygen

CFLAGS = -std=c99 -I./include -I../prosopon/include -Isrc
DOC_FLAGS = 

SRC_DIR = src
TEST_DIR = test
OUT_DIR = build

OBJS = pro_number.o pro_string.o
OUT_OBJS = $(addprefix $(OUT_DIR)/,$(OBJS))


all : $(OUT_OBJS) 
	(cd ../prosopon/ ; make)
	$(LINK) ../prosopon/libprosopon.so.1.0.0 -shared $^ -lc -Wl,-install_name,libprosopon-core.so.1 -o libprosopon-core.so.1

$(OUT_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -fPIC -c $^ -o $@


.PHONY : doc
doc :
	doxygen Doxyfile


.PHONY : clean
clean :
	rm -f $(OUT_DIR)/*
	if [ -f libprosopon-core.so.* ]; then rm libprosopon-core.so.*; fi