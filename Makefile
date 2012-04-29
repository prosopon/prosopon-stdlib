SHELL=/bin/bash

prefix = /usr/local
exec_prefix = $(prefix)
libdir = $(exec_prefix)/lib
includedir = $(prefix)/include

SRC_INCLUDE_DIR  = include/prosopon

LIBTOOL = glibtool --tag="junk"
CC = gcc
DOC = doxygen

CFLAGS = -std=c99 -I$(SRC_INCLUDE_DIR) -Iprosopon
DOC_FLAGS = 

SRC_DIR = src
TEST_DIR = test
OUT_DIR = build

LIBPROSOPON_STDLIB = libprosopon-stdlib.la
PROSOPON_HEADER_DIR = $(includedir)/prosopon

OBJS = prosopon_stdlib pro_number pro_string pro_stdio prosopon_macros pro_matching pro_future pro_forward
OUT_OBJS = $(addprefix $(OUT_DIR)/,$(OBJS))




HEADERS = prosopon_stdlib.h prosopon_macros.h
OUT_HEADERS = $(addprefix $(SRC_INCLUDE_DIR)/,$(HEADERS))


all : $(LIBPROSOPON_STDLIB)
	
$(LIBPROSOPON_STDLIB) : $(addsuffix .lo,$(OUT_OBJS))
	$(LIBTOOL) --mode=link gcc $(CFLAGS) -O -o $@  $^ -rpath $(libdir) -lprosopon

$(OUT_DIR)/%.lo : $(SRC_DIR)/%.c
	$(LIBTOOL) --mode=compile gcc $(CFLAGS) -fPIC -c $^ -o $@


install: $(LIBPROSOPON_STDLIB) copy_headers	
	$(LIBTOOL) --mode=install cp $< $(libdir)/$<

copy_headers: 
	if [ ! -d $(PROSOPON_HEADER_DIR) ]; then mkdir $(PROSOPON_HEADER_DIR); fi
	cp $(OUT_HEADERS) $(PROSOPON_HEADER_DIR)


.PHONY : doc
doc :
	doxygen Doxyfile


.PHONY : clean
clean :
	rm -f $(OUT_DIR)/*
	if [ -f libprosopon-stdlib.so.* ]; then rm libprosopon-stdlib.so.*; fi