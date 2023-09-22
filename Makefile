CC = $(shell which gcc || which clang || which cc)
CFLAGS = -Wall -Wextra -O3
AR = ar
ARFLAGS = rcs
LIBNAME = libcsvg.a

ifeq ($(OS),Windows_NT)
    DESTDIR = lib/win/mingw64
else
    DESTDIR = lib/linux/gcc
endif

INCLUDE_DIR = include
SRC_DIR = src
OBJ_DIR = obj
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: directories $(DESTDIR)/$(LIBNAME)
	rm -rf $(OBJ_DIR)

directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(DESTDIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(DESTDIR)/$(LIBNAME): $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $^
	ranlib $@

clean:
	@rm -rf $(OBJ_DIR) $(DESTDIR)/$(LIBNAME)

install: $(DESTDIR)/$(LIBNAME)
	# Here you can add codes to install the library if needed

.PHONY: all clean install directories
