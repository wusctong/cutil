UNAME := $(shell uname -s)
ifeq ($(UNAME),Darwin)
	SHELL := /bin/bash
	LDFLAGS := -I/opt/homebrew/include -L/opt/homebrew/lib
else
	SHELL := /usr/sbin/bash
	LDFLAGS :=
endif

CC     := clang
CFLAGS := -D_POSIX_C_SOURCE=200809L -Wall -Wextra -pedantic -std=c11 -O2
LIBS   := -lraylib -lm
OUTPUT := cutil

clean:
	@rm -rf build/*
	@echo " [-] Removed all build files"

build: clean
	@if [ ! -d "build" ]; then \
		mkdir -p build; \
		echo " [+] Created build dir"; \
	fi
	@$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) -o build/$(OUTPUT) \
		src/main.c
	@echo " [+] Successfully build"

