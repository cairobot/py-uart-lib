CC := gcc
CFLAGS := -g -Wall -fpic
CLFLAGS := -shared

D_SRC := src/
D_OBJ := obj/
D_LIB := ./lib/

name := uart
testname := uart-test
libname := libuart.dylib
target_archive := uart.tar.xz
C_SRCS := $(filter-out $(D_SRC)test.c, $(filter-out $(D_SRC)main.c, $(wildcard $(D_SRC)*.c)))

C_TEST := $(D_SRC)test.c
C_MAIN := $(D_SRC)main.c
O_LIB  := $(patsubst $(D_SRC)%, $(D_OBJ)%, $(patsubst %.c, %.o, $(C_SRCS)))
O_TEST := $(patsubst $(D_SRC)%, $(D_OBJ)%, $(patsubst %.c, %.o, $(C_TEST)))
O_MAIN := $(patsubst $(D_SRC)%, $(D_OBJ)%, $(patsubst %.c, %.o, $(C_MAIN)))

INC_DS := 
LIB_DS := $(D_LIB)
LIBS   := uart

INFLAGS += $(foreach includedir,$(INC_DS),-I$(includedir))
LDFLAGS += $(foreach librarydir,$(LIB_DS),-L$(librarydir))
LIFLAGS += $(foreach library,$(LIBS),-l$(library))

all: $(name)
main: $(name)
test: $(testname)
lib: $(libname)

init:
	mkdir -p $(D_SRC)
	mkdir -p $(D_OBJ)
	mkdir -p $(D_LIB)

$(D_OBJ)%.o: $(D_SRC)%.c
	$(CC) $(CFLAGS) $(INFLAGS) -c $< $(LDFLAGS) $(LIFLAGS) -o $@

$(name): $(O_MAIN) $(libname)
	$(CC) $(INFLAGS) $(LDFLAGS) $(CFLAGS) -o $@ $(O_MAIN) $(LIFLAGS)

$(testname): $(O_TEST) $(libname)
	$(CC) $(INFLAGS) $(LDFLAGS) $(CFLAGS) -o $@ $(O_TEST) $(LIFLAGS)

$(libname): $(O_LIB)
	$(CC) $(CFLAGS) $(CLFLAGS) -o $(D_LIB)$@ $(O_LIB)

rename:
	$(shell cat $(D_SRC)$(name).py_src | sed "s:___PLACEHOLDER___:"$(D_LIB)$(libname)":" > $(D_SRC)$(name).py)


deploy: $(libname) rename
	tar -vcf $(target_archive) $(D_LIB)$(libname) -C $(D_SRC) uart.py
	rm -f $(D_SRC)$(name).py
clean:
	rm -f $(name)
	rm -f $(testname)
	rm -f $(D_LIB)$(libname)
	rm -f $(wildcard $(D_OBJ)*.o)
