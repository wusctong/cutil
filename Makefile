UNAME := $(shell uname -s)

ifeq ($(UNAME),Darwin)
    SHELL    := /bin/bash
    # DEV_PATH := $(abspath ../dev)
	DEV_PATH := /opt/homebrew
	CFLAGS_EXTRA := -I$(DEV_PATH)/include
    LDFLAGS  := -L$(DEV_PATH)/lib -Wl,-rpath,$(DEV_PATH)/lib
else
    SHELL    := /usr/sbin/bash
    LDFLAGS  :=
    CFLAGS_EXTRA :=
endif

CC      := clang
CFLAGS  := -D_POSIX_C_SOURCE=200809L -Wall -Wextra -pedantic -std=c11 -O2 $(CFLAGS_EXTRA)
LIBS    := -lraylib -lm
OUTPUT  := cutil

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
	@echo " [+] Successfully built"
