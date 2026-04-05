SHELL  := /usr/sbin/bash

CC     := clang
CFLAGS := -Wall -Wextra -pedantic -std=c11 -O2
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
	@$(CC) $(CFLAGS) $(LIBS) -o build/$(OUTPUT) \
		src/main.c
	@echo " [+] Successfully build"

