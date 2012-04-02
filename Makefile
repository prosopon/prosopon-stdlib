SHELL=/bin/bash

CC = gcc
LINK = gcc
DOC = doxygen

CFLAGS = -std=c99 -I./include -I../prosopon/include -Isrc
LINK_FLAGS = -lprosopon -shared -lc
DOC_FLAGS = 

SRC_DIR = src
TEST_DIR = test
OUT_DIR = build

OBJS = pro_number.o pro_string.o prosopon-libcore.o
OUT_OBJS = $(addprefix $(OUT_DIR)/,$(OBJS))


all : libprosopon-core.so.1
	

libprosopon-core.so.1: $(OUT_OBJS) 
	$(LINK) $(LINK_FLAGS) $^ -Wl,-install_name,libprosopon-core.so.1 -o $@


$(OUT_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -fPIC -c $^ -o $@


install:
	cp libprosopon-core.so.1 /usr/local/lib/


.PHONY : doc
doc :
	doxygen Doxyfile


.PHONY : clean
clean :
	rm -f $(OUT_DIR)/*
	if [ -f libprosopon-core.so.* ]; then rm libprosopon-core.so.*; fi