CC = $(shell which gcc || which clang || which cc)
CFLAGS = -Wall -Wextra -O3
INCLUDES = -I../include
LIBS = -L../lib/linux/gcc -lcsvg -lm

EXAMPLES = $(wildcard *.c)

ifeq ($(OS),Windows_NT)
  EXECUTABLES = $(EXAMPLES:.c=.exe)
else
  EXECUTABLES = $(EXAMPLES:.c=)
endif

all: $(EXECUTABLES)

ifeq ($(OS),Windows_NT)
  %.exe: %.c
	  $(CC) $(CFLAGS) $(INCLUDES) $< -o $@ $(LIBS)
else
  %: %.c
	  $(CC) $(CFLAGS) $(INCLUDES) $< -o $@ $(LIBS)
endif

clean:
ifeq ($(OS),Windows_NT)
	rm -f *.exe
else
	rm -f $(EXECUTABLES)
endif

run: $(EXECUTABLES)
	@for exe in $(EXECUTABLES); do \
		echo "Uruchamianie $$exe..."; \
		./$$exe; \
	done
