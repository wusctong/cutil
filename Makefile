UNAME := $(shell uname -s)

UNIX-CC := clang
WIN-CC  := x86_64-w64-mingw32-gcc
OUTPUT  := cutil

RAYLIB_WIN_PATH := ../../cross_platform/raylib
RAYLIB_WIN_INC  := -I$(RAYLIB_WIN_PATH)/include
RAYLIB_WIN_LIB  := -L$(RAYLIB_WIN_PATH)/lib

CFLAGS  := -D_POSIX_C_SOURCE=200809L -Wall -Wextra -pedantic -std=c23 -O2

ifeq ($(UNAME),Darwin)
    SHELL        := /bin/bash
    DEV_PATH     := $(shell brew --prefix)
    CFLAGS_EXTRA := -I$(DEV_PATH)/include
    LDFLAGS_UNIX := -L$(DEV_PATH)/lib -Wl,-rpath,$(DEV_PATH)/lib
    LIBS_UNIX    := -lraylib -lm
else
    SHELL        := /bin/bash
    LDFLAGS_UNIX :=
    CFLAGS_EXTRA :=
    LIBS_UNIX    := -lraylib -lm
endif

WIN_LIBS := -lraylib -lopengl32 -lgdi32 -lwinmm -lpthread -lws2_32 -static

.PHONY: clean build build-win

clean:
	@rm -rf build/*
	@echo " - Removed all build files"

build: clean
	@mkdir -p build
	@echo " + Created build dir"
	@cp ../../others/NotoSansSC-Bold.ttf build/font.ttf
	@echo " + Copied CN Font"
	@$(UNIX-CC) $(CFLAGS) $(CFLAGS_EXTRA) $(LDFLAGS_UNIX) -o build/$(OUTPUT) \
		src/main.c $(LIBS_UNIX)
	@echo " + Successfully built (Unix)"

build-win: clean
	@mkdir -p build
	@echo " + Created build dir"
	@cp ../../others/NotoSansSC-Bold.ttf build/font.ttf
	@echo " + Copied CN Font"
	@$(WIN-CC) $(CFLAGS) $(RAYLIB_WIN_INC) src/main.c -o build/$(OUTPUT).exe \
		$(RAYLIB_WIN_LIB) $(WIN_LIBS)
	@echo " + Successfully built (Windows)"

build-win-release: clean
	@mkdir -p build
	@echo " + Created build dir"
	@$(WIN-CC) $(CFLAGS) $(RAYLIB_WIN_INC) src/main.c -o build/$(OUTPUT).exe \
		$(RAYLIB_WIN_LIB) $(WIN_LIBS) -mwindows
	@echo " + Successfully built (Windows Release)"
